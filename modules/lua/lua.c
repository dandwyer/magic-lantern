/*
 * Copyright (C) 2014 David Milligan
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include <module.h>
#include <dryos.h>
#include <string.h>
#include <math.h>
#include <raw.h>
#include <lens.h>
#include <property.h>
#include <console.h>
#include <beep.h>
#include <fio-ml.h>
#include <shoot.h>
#include <zebra.h>
#include <focus.h>
#include <config.h>
#include <bmp.h>
#include "lua_common.h"

struct script_event_entry
{
    struct script_event_entry * next;
    int function_ref;
    lua_State * L;
    int mask;
};

struct script_semaphore
{
    struct script_semaphore * next;
    lua_State * L;
    struct semaphore * semaphore;
};

static int lua_loaded = 0;
int last_keypress = 0;

static struct script_semaphore * script_semaphores = NULL;

int lua_take_semaphore(lua_State * L, int timeout, struct semaphore ** assoc_semaphore)
{
    struct script_semaphore * current;
    for(current = script_semaphores; current; current = current->next)
    {
        if(current->L == L)
        {
            if(assoc_semaphore) *assoc_semaphore = current->semaphore;
            return take_semaphore(current->semaphore, timeout);
        }
    }
    fprintf(stderr, "error: could not find semaphore for lua state\n");
    return -1;
}

int lua_give_semaphore(lua_State * L, struct semaphore ** assoc_semaphore)
{
    struct script_semaphore * current;
    for(current = script_semaphores; current; current = current->next)
    {
        if(current->L == L)
        {
            if(assoc_semaphore) *assoc_semaphore = current->semaphore;
            return give_semaphore(current->semaphore);
        }
    }
    fprintf(stderr, "error: could not find semaphore for lua state\n");
    return -1;
}

static struct semaphore * new_script_semaphore(lua_State * L, const char * filename)
{
    struct script_semaphore * new_semaphore = calloc(1, sizeof(struct script_semaphore));
    if (new_semaphore)
    {
        new_semaphore->next = script_semaphores;
        script_semaphores = new_semaphore;
        new_semaphore->L = L;
        new_semaphore->semaphore = create_named_semaphore(filename, 0);
        return new_semaphore->semaphore;
    }
    return NULL;
}

/*
 Determines if a string ends in some string
 */
static int string_ends_with(const char *source, const char *ending)
{
    if(source == NULL || ending == NULL) return 0;
    if(strlen(source) <= 0) return 0;
    if(strlen(source) < strlen(ending)) return 0;
    return !strcmp(source + strlen(source) - strlen(ending), ending);
}

char * copy_string(const char * str)
{
    size_t len = strlen(str) + 1;
    char * copy = malloc(sizeof(char) * len);
    if(copy) strncpy(copy,str,len);
    return copy;
}

/***
 Event Handlers.
 
 Scripts can repsond to events by setting the functions in the 'event' table.
 Event handler functions can take one integer parameter, and must return a boolean
 that specifies whether or not the backend should continue executing event handlers
 for this particular event.
 
 Event handlers will not run if there's already a script or another event handler
 actively executing at the same time.
 
 @author Magic Lantern Team
 @copyright 2014
 @license GPL
 @module event
 @usage
 event.keypress = function(key)
 print("You pressed a key: "..key)
 return false
 end
 */


static unsigned int lua_do_cbr(unsigned int ctx, struct script_event_entry * event_entries, const char * event_name, int timeout, int sucess, int failure)
{
    //no events registered by lua scripts
    if(!event_entries || !lua_loaded) return sucess;
    
    unsigned int result = sucess;
    struct script_event_entry * current;
    for(current = event_entries; current; current = current->next)
    {
        lua_State * L = current->L;
        if(current->function_ref != LUA_NOREF)
        {
            struct semaphore * sem = NULL;
            if(!lua_take_semaphore(L, timeout, &sem) && sem)
            {
                if(lua_rawgeti(L, LUA_REGISTRYINDEX, current->function_ref) == LUA_TFUNCTION)
                {
                    lua_pushinteger(L, ctx);
                    if(docall(L, 1, 1))
                    {
                        fprintf(stderr, "lua cbr error:\n %s\n", lua_tostring(L, -1));
                        result = CBR_RET_ERROR;
                        give_semaphore(sem);
                        break;
                    }
                    else
                    {
                        if(lua_isboolean(L, -1) && !lua_toboolean(L, -1))
                        {
                            lua_pop(L, 1);
                            result = failure;
                            give_semaphore(sem);
                            break;
                        }
                        
                    }
                }
                lua_pop(L,1);
                give_semaphore(sem);
            }
            else
            {
                printf("lua semaphore timeout: %s (%dms)\n", event_name, timeout);
            }
        }
    }
    return result;
}

#define LUA_CBR_FUNC(name, arg, timeout)\
static struct script_event_entry * name##_cbr_scripts = NULL;\
static unsigned int lua_##name##_cbr(unsigned int ctx) {\
return lua_do_cbr(arg, name##_cbr_scripts, #name, timeout, CBR_RET_CONTINUE, CBR_RET_STOP);\
}\

LUA_CBR_FUNC(pre_shoot, ctx, 500)
LUA_CBR_FUNC(post_shoot, ctx, 500)
LUA_CBR_FUNC(shoot_task, ctx, 500)
LUA_CBR_FUNC(seconds_clock, ctx, 100)
LUA_CBR_FUNC(custom_picture_taking, ctx, 1000)
LUA_CBR_FUNC(intervalometer, get_interval_count(), 1000)
LUA_CBR_FUNC(config_save, ctx, 1000)

#ifdef CONFIG_VSYNC_EVENTS
LUA_CBR_FUNC(vsync)
LUA_CBR_FUNC(display_filter)
LUA_CBR_FUNC(vsync_setparam)
#endif

static struct script_event_entry * keypress_cbr_scripts = NULL;
static unsigned int lua_keypress_cbr(unsigned int ctx)
{
    last_keypress = ctx;
    //keypress cbr interprets things backwards from other CBRs
    return lua_do_cbr(ctx, keypress_cbr_scripts, "keypress", 500, CBR_RET_KEYPRESS_NOTHANDLED, CBR_RET_KEYPRESS_HANDLED);
}

#define SCRIPT_CBR_SET(event) \
if(!strcmp(key, #event))\
{\
lua_pushvalue(L, 3);\
set_event_script_entry(&event##_cbr_scripts, L, lua_isfunction(L, -1) ? luaL_ref(L, LUA_REGISTRYINDEX) : LUA_NOREF); \
return 0;\
}\



static void update_event_cant_unload(struct script_event_entry ** root, lua_State * L)
{
    //are there any event handlers for this script left?
    int any_active_handlers = 0;
    struct script_event_entry * current;
    for(current = *root; current; current = current->next)
    {
        if(current->L == L && current->function_ref != LUA_NOREF)
        {
            any_active_handlers = 1;
            break;
        }
    }
    if(*root) lua_set_cant_unload(L, any_active_handlers, (*root)->mask);
}

static void set_event_script_entry(struct script_event_entry ** root, lua_State * L, int function_ref)
{
    struct script_event_entry * current;
    for(current = *root; current; current = current->next)
    {
        if(current->L == L)
        {
            if(current->function_ref != LUA_NOREF)
            {
                luaL_unref(L, LUA_REGISTRYINDEX, current->function_ref);
            }
            current->function_ref = function_ref;
            update_event_cant_unload(root, L);
            return;
        }
    }
    if(function_ref != LUA_NOREF)
    {
        struct script_event_entry * new_entry = calloc(1, sizeof(struct script_event_entry));
        if(new_entry)
        {
            static int event_masks = LUA_EVENT_UNLOAD_MASK;
            new_entry->mask = *root == NULL ? event_masks++ : (*root)->mask;
            new_entry->next = *root;
            new_entry->L = L;
            new_entry->function_ref = function_ref;
            *root = new_entry;
        }
        else
        {
            luaL_error(L, "malloc error creating script event");
        }
    }
    update_event_cant_unload(root, L);
}

static int luaCB_event_index(lua_State * L)
{
    //LUA_PARAM_STRING_OPTIONAL(key, 2, "");
    lua_rawget(L, 1);
    return 1;
}

static int luaCB_event_newindex(lua_State * L)
{
    LUA_PARAM_STRING_OPTIONAL(key, 2, "");
    
    /// Called before a picture is taken
    // @param arg unused
    // @treturn bool whether or not to continue executing CBRs for this event
    // @function pre_shoot
    SCRIPT_CBR_SET(pre_shoot);
    /// Called after a picture is taken
    // @param arg unused
    // @treturn bool whether or not to continue executing CBRs for this event
    // @function post_shoot
    SCRIPT_CBR_SET(post_shoot);
    /// Called periodicaly from shoot_task
    // @param arg unused
    // @treturn bool whether or not to continue executing CBRs for this event
    // @function shoot_task
    SCRIPT_CBR_SET(shoot_task);
    /// Called each second
    // @param arg unused
    // @treturn bool whether or not to continue executing CBRs for this event
    // @function seconds_clock
    SCRIPT_CBR_SET(seconds_clock);
    /// Called when a key is pressed
    // @tparam int key the key that was pressed, see @{constants.KEY}
    // @treturn bool whether or not to continue executing CBRs for this event
    // @function keypress
    SCRIPT_CBR_SET(keypress);
    /// Special types of picture taking (e.g. silent pics); so intervalometer and other photo taking routines should use that instead of regular pics
    // @param arg unused
    // @treturn bool whether or not to continue executing CBRs for this event
    // @function custom_picture_taking
    SCRIPT_CBR_SET(custom_picture_taking);
    /// Called after a picture is taken with the intervalometer
    // @tparam int interval_count the current interval count
    // @treturn bool whether or not to continue executing CBRs for this event
    // @function intervalometer
    SCRIPT_CBR_SET(intervalometer);
    /// Called when configs are being saved; save any config data for your script here
    // @param arg unused
    // @treturn bool whether or not to continue executing CBRs for this event
    // @function config_save
    SCRIPT_CBR_SET(config_save);
#ifdef CONFIG_VSYNC_EVENTS
    SCRIPT_CBR_SET(display_filter);
    SCRIPT_CBR_SET(vsync);
    SCRIPT_CBR_SET(vsync_setparam);
#endif
    
    lua_rawset(L, 1);
    return 0;
}

static const char * lua_event_fields[] =
{
    "pre_shoot",
    "post_shoot",
    "shoot_task",
    "seconds_clock",
    "keypress",
    "custom_picture_taking",
    "intervalometer",
    "config_save",
    NULL
};

static const luaL_Reg eventlib[] =
{
    { NULL, NULL }
};

LUA_LIB(event)

static const luaL_Reg alllibs[] =
{
    {LUA_COLIBNAME, luaopen_coroutine},
    {LUA_TABLIBNAME, luaopen_table},
    {LUA_IOLIBNAME, luaopen_io},
    {LUA_STRLIBNAME, luaopen_string},
    {LUA_MATHLIBNAME, luaopen_math},
    {LUA_UTF8LIBNAME, luaopen_utf8},
    {LUA_DBLIBNAME, luaopen_debug},
    {"console", luaopen_console},
    {"camera", luaopen_camera},
    {"lv", luaopen_lv},
    {"lens", luaopen_lens},
    {"movie", luaopen_movie},
    {"display", luaopen_display},
    {"key", luaopen_key},
    {"menu", luaopen_menu},
    {"event", luaopen_event},
    {"dryos", luaopen_dryos},
    {"interval", luaopen_interval},
    {"battery", luaopen_battery},
    {"task", luaopen_task},
    {"property", luaopen_property},
    {"constants", luaopen_constants},
    {"MODE", luaopen_MODE},
    {"ICON_TYPE", luaopen_ICON_TYPE},
    {"UNIT", luaopen_UNIT},
    {"DEPENDS_ON", luaopen_DEPENDS_ON},
    {"FONT", luaopen_FONT},
    {"COLOR", luaopen_COLOR},
    {"KEY", luaopen_KEY},
    {NULL,NULL}
};

static int luaCB_global_index(lua_State * L)
{
    LUA_PARAM_STRING_OPTIONAL(key, 2, "");
    const luaL_Reg *lib;
    for (lib = alllibs; lib->func; lib++)
    {
        if(!strcmp(key, lib->name))
        {
            luaL_requiref(L, lib->name, lib->func, 1);
            return 1;
        }
    }
    return 0;
}

int do_lua_next(lua_State * L)
{
    int r = lua_type(L, 1) == LUA_TTABLE && lua_next(L, 1);
    if (!r)
    {
        lua_pushnil(L);
        lua_pushnil(L);
    }
    return 2;
}

int luaCB_next(lua_State * L)
{
    lua_getmetatable(L, 1);
    lua_getfield(L, -1, "fields");
    const char ** fields = (const char **)lua_touserdata(L, -1);
    lua_pop(L, 2);
    
    if(lua_isnil(L, 2))
    {
        if(fields && fields[0])
        {
            lua_pushstring(L, fields[0]);
        }
        else
        {
            lua_pushvalue(L, 2);
            return do_lua_next(L);
        }
    }
    else if(lua_type(L, 2) == LUA_TSTRING)
    {
        LUA_PARAM_STRING(key, 2);
        int found = 0;
        for(int i = 0; fields[i]; i++)
        {
            if(!strcmp(key, fields[i]))
            {
                if(fields && fields[i+1])
                {
                    lua_pushstring(L, fields[i+1]);
                    found = true;
                    break;
                }
                else
                {
                    lua_pushnil(L);
                    return do_lua_next(L);
                }
            }
        }
        if(!found)
        {
            lua_pushvalue(L, 2);
            return do_lua_next(L);
        }
    }
    else
    {
        lua_pushvalue(L, 2);
        return do_lua_next(L);
    }
    lua_pushvalue(L, -1);
    lua_gettable(L, 1);
    return 2;
}

int luaCB_pairs(lua_State * L)
{
    lua_pushcfunction(L, luaCB_next);
    lua_pushvalue(L, 1);
    lua_pushnil(L);
    return 3;
}

static lua_State * load_lua_state()
{
    lua_State* L = luaL_newstate();
    luaL_requiref(L, "_G", luaopen_base, 1);
    luaL_requiref(L, LUA_LOADLIBNAME, luaopen_package, 1);
    luaL_requiref(L, "globals", luaopen_globals, 0);
    luaL_requiref(L, LUA_STRLIBNAME, luaopen_string, 0);
    
    luaL_getsubtable(L, LUA_REGISTRYINDEX, "_PRELOAD");
    const luaL_Reg *lib;
    for (lib = alllibs; lib->func; lib++)
    {
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 1);
    
    lua_getglobal(L, "_G");
    lua_newtable(L);
    lua_pushcfunction(L, luaCB_global_index);
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2);
    lua_pop(L, 1);
    
    /* preload strict.lua once, since it will be used in all scripts */
    int bufsize;
    static char * strict_lua = (void*) 0xFFFFFFFF;
    if (strict_lua == (void*) 0xFFFFFFFF)
    {
        strict_lua = (char*) read_entire_file(SCRIPTS_DIR "/lib/strict.lua", &bufsize);
        
        if (!strict_lua)
        {
            /* allow scripts to run without strict.lua, if not present */
            printf("Warning: strict.lua not found.\n");
        }
        
        /* note: strict_lua is never freed */
    }
    
    if (strict_lua)
    {
        if (luaL_loadstring(L, strict_lua) || docall(L, 0, LUA_MULTRET))
        {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
        }
    }
    
    return L;
}

#define SCRIPT_FLAG_AUTORUN_ENABLED "LEN"

#define SCRIPT_STATE_NOT_RUNNING 0
#define SCRIPT_STATE_LOADING     1
#define SCRIPT_STATE_RUNNING     2
#define SCRIPT_STATE_FAILED      3

struct lua_script
{
    char * filename;
    char * name;
    char * description;
    int autorun;
    int state;
    int load_time;
    int cant_unload;
    lua_State * L;
    struct menu_entry * menu_entry;
    struct lua_script * next;
};

static struct lua_script * lua_scripts = NULL;

void lua_set_cant_unload(lua_State * L, int cant_unload, int mask)
{
    struct lua_script * current;
    for (current = lua_scripts; current; current = current->next)
    {
        if(current->L == L)
        {
            if(cant_unload)
            {
                current->cant_unload |= (1 << mask);
            }
            else
            {
                current->cant_unload &= ~(1 << mask);
            }
            return;
        }
    }
    fprintf(stderr, "lua_set_cant_unload: script not found\n");
}

static int lua_get_config_flag_path(struct lua_script * script, char * full_path, const char * flag)
{
    snprintf(full_path, MAX_PATH_LEN, "%s%s", get_config_dir(), script->filename);
    int len = strlen(full_path);
    if(len > 3 && strlen(flag) >= 3)
    {
        memcpy(&(full_path[len - 3]), flag, 3);
        return 1;
    }
    return 0;
}

static void lua_set_flag(struct lua_script * script, const char * flag, int value)
{
    char full_path[MAX_PATH_LEN];
    if(lua_get_config_flag_path(script, full_path, flag))
    {
        config_flag_file_setting_save(full_path, value);
    }
}

static int lua_get_flag(struct lua_script * script, const char * flag)
{
    char full_path[MAX_PATH_LEN];
    if(lua_get_config_flag_path(script, full_path, flag))
    {
        return config_flag_file_setting_load(full_path);
    }
    return 0;
}

static void load_script(struct lua_script * script)
{
    if(script->L)
    {
        fprintf(stderr, "script is already running\n");
        return;
    }
    
    script->load_time = get_seconds_clock();
    script->state = SCRIPT_STATE_LOADING;
    lua_State* L = script->L = load_lua_state();
    script->cant_unload = 0;
    struct semaphore * sem = new_script_semaphore(L, script->filename);
    if(sem)
    {
        int error = 0;
        char full_path[MAX_PATH_LEN];
        snprintf(full_path, MAX_PATH_LEN, SCRIPTS_DIR "/%s", script->filename);
        printf("Loading script: %s\n", script->filename);
        if(luaL_loadfile(L, full_path) || docall(L, 0, LUA_MULTRET))
        {
            /* error loading script */
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            error = 1;
        }
        give_semaphore(sem);
        
        //"complex" script that keeps running after load, set autorun
        if (script->cant_unload)
        {
            script->state = SCRIPT_STATE_RUNNING;
            //if there was an error, disable autorun, otherwise turn it on
            script->menu_entry->icon_type = IT_BOOL;
            script->autorun = !error;
            lua_set_flag(script, SCRIPT_FLAG_AUTORUN_ENABLED, script->autorun);
        }
        //"simple" script didn't create a menu, start a task, or register any event handlers, so we can safely unload it
        else
        {
            lua_close(L);
            script->L = NULL;
            script->menu_entry->icon_type = IT_ACTION;
            script->state = error ? SCRIPT_STATE_FAILED : SCRIPT_STATE_NOT_RUNNING;
            script->load_time = 0;
        }
    }
    else
    {
        fprintf(stderr, "load script failed: could not create semaphore\n");
    }
}

static MENU_UPDATE_FUNC(lua_script_menu_update)
{
    struct lua_script * script = (struct lua_script *)(entry->priv);
    if(script)
    {
        MENU_SET_VALUE("");
        MENU_SET_HELP(script->description);

        if (script->autorun)
        {
            MENU_SET_WARNING(MENU_WARN_INFO, "This script will autorun on next boot.");
        }
        else
        {
            MENU_SET_WARNING(MENU_WARN_INFO, "Press SET to load/run this script.");
            
            if(!lua_loaded)
            {
                MENU_SET_WARNING(MENU_WARN_NOT_WORKING, "Please wait for Lua to finish loading...");
            }
        }
        
        /* if a script takes a long time in the LOADING state,
         * it's probably a simple script that is running for a long time */
        int script_uptime = script->load_time ? get_seconds_clock() - script->load_time : 0;
        
        int fg = script->state ? COLOR_WHITE : COLOR_GRAY(40);
        int fnt = SHADOW_FONT(FONT(FONT_MED_LARGE, fg, COLOR_BLACK));
        bmp_printf(fnt | FONT_ALIGN_RIGHT, 680, info->y+2,
            script->autorun
                ? "AUTORUN" :
            script->state == SCRIPT_STATE_NOT_RUNNING
                ? "" :
            script->state == SCRIPT_STATE_LOADING
                ? (script_uptime <= 2 ? "Loading" : "Running") :
            script->state == SCRIPT_STATE_RUNNING
                ? "Running"
                : "Error"
        );

        switch (script->state)
        {
            case SCRIPT_STATE_LOADING:
                MENU_SET_ICON(MNI_RECORD, 0);
                break;

            case SCRIPT_STATE_RUNNING:
                MENU_SET_ICON(MNI_BOOL(script->autorun), 0);
                break;
            
            case SCRIPT_STATE_FAILED:
                MENU_SET_WARNING(MENU_WARN_NOT_WORKING, "Script Failed");
                break;
        }
    }
}

static void lua_user_load_task(struct lua_script * script)
{
    load_script(script);
}

static MENU_SELECT_FUNC(lua_script_menu_select)
{
    struct lua_script * script = (struct lua_script *)priv;
    ASSERT(script); if (!script) return;
    
    /* attempt to start the script */
    if ( script->state == SCRIPT_STATE_NOT_RUNNING ||
         script->state == SCRIPT_STATE_FAILED )
    {
        if (lua_loaded)
        {
            script->state = SCRIPT_STATE_LOADING;
            task_create("lua_user_load_task", 0x1c, 0x10000, lua_user_load_task, script);
            return;
        }
    }
    
    /* if the script is already running, open the submenu */
    if (!is_submenu_or_edit_mode_active())
    {
        menu_open_submenu();
    }
}

static MENU_UPDATE_FUNC(lua_script_run_update)
{
    MENU_SET_VALUE("");

    struct lua_script * script = (struct lua_script *)entry->priv;
    ASSERT(script); if (!script) return;

    if ( script->state == SCRIPT_STATE_NOT_RUNNING ||
         script->state == SCRIPT_STATE_FAILED )
    {
        if (!lua_loaded)
        {
            MENU_SET_WARNING(MENU_WARN_NOT_WORKING, "Please wait for Lua to finish loading...");
        }
    }
    else
    {
        MENU_SET_WARNING(MENU_WARN_NOT_WORKING, "Script is running.");
    }
}


static MENU_SELECT_FUNC(lua_script_toggle_autorun)
{
    // toggle auto_run (priv = &script->autorun)
    // note: any script can be set to autorun
    struct lua_script * script = (struct lua_script *)(priv - offsetof(struct lua_script, autorun));
    script->autorun = !script->autorun;
    lua_set_flag(script, SCRIPT_FLAG_AUTORUN_ENABLED, script->autorun);
}

static MENU_SELECT_FUNC(lua_script_edit)
{
    /* not yet implemented */
    beep();
}

static MENU_UPDATE_FUNC(menu_no_value)
{
    MENU_SET_VALUE("");
}

static struct menu_entry script_menu_template = {
    .icon_type  = IT_ACTION,
    .select = lua_script_menu_select,
    .update = lua_script_menu_update,
};

static struct menu_entry script_submenu_template[] = {
    {
        .name       = "Run Script",
        .select     = lua_script_menu_select,
        .update     = lua_script_run_update,
        .icon_type  = IT_ACTION,
        .help       = "Press SET to load/run this script."
    },
    {
        .name       = "Edit Script",
        .select     = lua_script_edit,
        .update     = menu_no_value,
        .icon_type  = IT_ACTION,
        .help       = "Load this script in the text editor (EDITOR.LUA)."
    },
    {
        .name       = "Autorun",
        .select     = lua_script_toggle_autorun,
        .max        = 1,
        .help       = "Select whether this script will be loaded at camera startup."
    },
    MENU_EOL,
};

/* extract script name/description from comments */
/* (it allocates the output buffer and can optionally use a prefix) */
static char* script_extract_string_from_comments(char* buf, char** output, const char* prefix)
{
    char* c = buf;
    
    /* skip Lua comment markers and spaces */
    while (isspace(*c) || *c == '-' || *c == '[')
    {
        c++;
    }

    /* extract script title/description (the current line) */
    char* p = strchr(c, '\n');
    if (!p) return c;
    
    *p = 0;
    *output = copy_string(c);
    *p = '\n';
    
    /* strip spaces and Lua comment markers from the end of the string, if any */
    c = *output + strlen(*output) - 1;
    while (isspace(*c) || *c == '-' || *c == '[')
    {
        *c = 0;
        c--;
        if (c == *output) break; 
    }
    
    /* use a prefix, if any */
    if (prefix)
    {
        char* old = *output;
        uint32_t maxlen = strlen(old) + strlen(*output) + 2 + 1;
        *output = malloc(maxlen);
        snprintf(*output, maxlen, "%s: %s", prefix, old);
        free(old);
    }
    
    return p;
}

static void script_get_name_from_comments(const char * filename, char ** name, char ** description)
{
    *name = 0;
    *description = 0;

    char full_path[MAX_PATH_LEN];
    snprintf(full_path, MAX_PATH_LEN, SCRIPTS_DIR "/%s", filename);
    
    char buf[256];
    FILE* f = fopen(full_path, "r");
    ASSERT(f); if (!f) return;
    fread(buf, 1, sizeof(buf), f);
    buf[sizeof(buf)-1] = 0;
    fclose(f);
    
    /* extract name and description */
    char* c = script_extract_string_from_comments(buf, name, 0);
    
    /* name too long? use it as description */
    /* (todo: check string length with current font instead) */
    if (name && strlen(*name) > 25)
    {
        free(*name); *name = 0;
        script_extract_string_from_comments(buf, description, filename);
    }
    else
    {
        script_extract_string_from_comments(c, description, filename);
    }
}

static void add_script(const char * filename)
{
    struct lua_script * new_script = calloc(1, sizeof(struct lua_script));
    if(new_script)
    {
        new_script->filename = copy_string(filename);
        if(new_script->filename)
        {
            new_script->menu_entry = calloc(1, sizeof(struct menu_entry));
            new_script->L = NULL;
            new_script->next = lua_scripts;
            lua_scripts = new_script;
            if(new_script->menu_entry)
            {
                memcpy(new_script->menu_entry, &script_menu_template, sizeof(script_menu_template));
                script_get_name_from_comments(new_script->filename, &new_script->name, &new_script->description);
                new_script->menu_entry->name = new_script->name ? new_script->name : new_script->filename;
                new_script->menu_entry->priv = new_script;
                new_script->menu_entry->children = calloc(COUNT(script_submenu_template), sizeof(script_submenu_template[0]));
                if (new_script->menu_entry->children)
                {
                    memcpy(new_script->menu_entry->children, script_submenu_template, COUNT(script_submenu_template) * sizeof(script_submenu_template[0]));
                    new_script->menu_entry->children[0].priv = new_script;
                    new_script->menu_entry->children[1].priv = new_script;
                    new_script->menu_entry->children[2].priv = &new_script->autorun;
                    menu_add("Scripts", new_script->menu_entry, 1);
                    return;
                }
                free(new_script->menu_entry);
            }
            free(new_script->filename);
        }
        free(new_script);
    }
    fprintf(stderr, "add_script: malloc error\n");
}

static void lua_do_autoload()
{
    struct lua_script * current;
    for (current = lua_scripts; current; current = current->next)
    {
        if(lua_get_flag(current, SCRIPT_FLAG_AUTORUN_ENABLED))
        {
            current->autorun = 1;
            load_script(current);
            msleep(100);
        }
    }
}

static void lua_load_task(int unused)
{
    console_show();
    msleep(500);
    console_clear();
    
    struct fio_file file;
    struct fio_dirent * dirent = 0;
    
    dirent = FIO_FindFirstEx(SCRIPTS_DIR, &file);
    if(!IS_ERROR(dirent))
    {
        do
        {
            if (!(file.mode & ATTR_DIRECTORY) &&
                 (string_ends_with(file.name, ".LUA") ||
                  string_ends_with(file.name, ".lua")) &&
                 file.name[0] != '.' && file.name[0] != '_'
            )
            {
                add_script(file.name);
            }
        }
        while(FIO_FindNextEx(dirent, &file) == 0);
        FIO_FindClose(dirent);
    }
    
    lua_do_autoload();
    
    printf("All scripts loaded.\n");
    lua_loaded = 1;

    /* wait for key pressed or for 5-second timeout, whichever comes first */
    last_keypress = 0;
    for (int i = 0; i < 50 && !last_keypress; i++)
    {
        msleep(100);
    }

    console_hide();
}

static unsigned int lua_init()
{
    task_create("lua_load_task", 0x1c, 0x10000, lua_load_task, (void*) 0);
    return 0;
}

static unsigned int lua_deinit()
{
    return 0;
}

MODULE_INFO_START()
MODULE_INIT(lua_init)
MODULE_DEINIT(lua_deinit)
MODULE_INFO_END()

MODULE_CBRS_START()
MODULE_CBR(CBR_PRE_SHOOT, lua_pre_shoot_cbr, 0)
MODULE_CBR(CBR_POST_SHOOT, lua_post_shoot_cbr, 0)
MODULE_CBR(CBR_SHOOT_TASK, lua_shoot_task_cbr, 0)
MODULE_CBR(CBR_SECONDS_CLOCK, lua_seconds_clock_cbr, 0)
MODULE_CBR(CBR_KEYPRESS, lua_keypress_cbr, 0)
MODULE_CBR(CBR_CUSTOM_PICTURE_TAKING, lua_custom_picture_taking_cbr, 0)
MODULE_CBR(CBR_INTERVALOMETER, lua_intervalometer_cbr, 0)
MODULE_CBR(CBR_CONFIG_SAVE, lua_config_save_cbr, 0)

#ifdef CONFIG_VSYNC_EVENTS
MODULE_CBR(CBR_VSYNC, lua_vsync_cbr, 0)
MODULE_CBR(CBR_DISPLAY_FILTER, lua_display_filter_cbr, 0)
MODULE_CBR(CBR_VSYNC_SETPARAM, lua_vsync_setparam_cbr, 0)
#endif

MODULE_CBRS_END()


