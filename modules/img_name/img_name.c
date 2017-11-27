//TODO: save prefix config

#include <module.h>
#include <dryos.h>
#include <property.h>
#include <bmp.h>
#include <menu.h>
#include <fileprefix.h>

#include "../ime_base/ime_base.h"

static char prefix[8];
static int key = -1;

static IME_DONE_FUNC(file_prefix_enter_done)
{
    if (status == IME_OK)
    {
        /* if user entered less than 4 characters, fill with _ */
        prefix[4] = 0;
        int len = strlen(prefix);
        for (int i = len; i < 4; i++)
        {
            prefix[i] = '_';
        }

        /* any previously set prefix? */
        if (key != -1 && key != 0)
        {
            file_prefix_reset(key);
        }

        /* set the new prefix */
        key = file_prefix_set(prefix);
    }
    return IME_OK;
}

static IME_UPDATE_FUNC(file_prefix_enter_upd)
{
    return IME_OK;
}

static MENU_SELECT_FUNC(file_prefix_enter)
{
    snprintf(prefix, sizeof(prefix), "%s", get_file_prefix());

    ime_base_start(
        "Enter file prefix",
        prefix,
        5,
        IME_UTF8,
        IME_CHARSET_FILENAME,
        file_prefix_enter_upd,
        file_prefix_enter_done,
        0, 0, 0, 0
    );
}

static MENU_UPDATE_FUNC(file_prefix_upd)
{
    MENU_SET_VALUE("%s", get_file_prefix());
    
    if (key == 0)
    {
        MENU_SET_RINFO("FAILED");
    }
    else if (key != -1)
    {
        MENU_SET_ENABLED(1);
    }

    if ((void *) &ime_base_start == (void *) &ret_0)
    {
        MENU_SET_WARNING(MENU_WARN_NOT_WORKING, "Please load the IME modules (ime_base.mo and one ime_*.mo)");
    }
}

static struct menu_entry img_name_menu[] =
{
    {
        .name       = "Image file prefix",
        .select     = file_prefix_enter,
        .update     = file_prefix_upd,
        .icon_type  = IT_SUBMENU,
        .help       = "Custom image file prefix (e.g. IMG_1234.JPG -> ABCD1234.JPG).",
        .help2      = "Setting not persistent. Might conflict with Dual ISO prefixes.",
    }
};

static unsigned int img_name_init()
{
    menu_add("Shoot", img_name_menu, COUNT(img_name_menu));
    return 0;
}

static unsigned int img_name_deinit()
{
    return 0;
}
    
MODULE_INFO_START()
    MODULE_INIT(img_name_init)
    MODULE_DEINIT(img_name_deinit)
MODULE_INFO_END()
