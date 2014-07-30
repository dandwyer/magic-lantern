/** \file
 * This is similar to boot-hack, but simplified. It only does the first-time install (bootflag setup).
 */
/*
 * Copyright (C) 2009 Trammell Hudson <hudson+ml@osresearch.net>
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

#include "dryos.h"
#include "config.h"
#include "version.h"
#include "bmp.h"
#include "menu.h"
#include "property.h"
#include "consts.h"
#include "gui.h"

#define ARM_CPSR_FLAG_FIQ_MASKED  (0x00000040)
#define ARM_CPSR_FLAG_IRQ_MASKED  (0x00000080)

/* Notes from Horshack */
/**
 * Btw I tested this in a stepwise fashion before actually implementing the code you see below.
 * First I implemented an infinite loop with IRQ/FIQ disabled while the camera was running...
 * I wanted to make sure there wasn't any watchdog timer that might execute due to the interrupts
 * being disabled for an unknown period of time. Embedded systems use non-maskable watchdog timers
 * as a way to detect when firmware is hung and to take recovery action...it usually works where at
 * SOD firmware initializes the interval for the watchdog...then afterwards firmware is responsible
 * for pinging a predefined timer register every so often to reset the watchdog, usually either in a
 * timer interrupt or idle loop...if firmware fails to ping that register within the defined interval
 * then a watchdog interrupt occurs even if IRQ/FIQ is disabled, at which time recovery action can be
 * taken...I wanted to make sure this wouldn't happen on my body since that watchdog may occur while
 * the flash is being erased/written, even though this interval is probably much longer than the time
 * it takes for DisableBootDisk to complete. When I ran with IRQ/FIQ disabled in an infinite loop
 * I confirmed that none of the UI buttons on the back were functioning...however I could see that
 * the top panel buttons would still at least trigger a response on the top LCD (WB/AF/ISO buttons).
 * I'm guessing these are handled by logic outside the main ARM processor? After a while of interacting
 * with those top buttons while FW was in the dead IRQ/FIQ disable loop the body would eventually display
 * "Error 80" on the top, which I'm guessing is some type of passive watchdog where hardware detects that
 * firmware is no longer responding. Perhaps you know more about this interaction. Anyway, it took a least
 * 10 seconds for that to occur so I was satisfied that no watchdog would occur for the short time
 * DisableBootDisk was executing.
 * 
 * Btw, another thing I noticed is that msleep() seems to enable IRQ/FIQ, because if I called it after
 * disabling IRQ/FIQ the back-buttons would start responding.
 */

static void call_bootflag_eventproc(char* eventproc)
{
    /* calling this one from LiveView will cause the routine to fail in the middle of writing to ROM */
    /* result: will leave the bootflag area erased */
    /* the visible effect is that camera will ask for a firmware update as soon as you remove the card or place a non-ML card */
    
    /* we'll try to call this routine from Canon menu only (where the sensor should be inactive) */
    if (CURRENT_DIALOG_MAYBE == DLG_MENU && DISPLAY_IS_ON)
    {
        for (int i = 0; i < 10; i++)
        {
            bmp_printf(FONT_LARGE, 0, 450, eventproc);
            info_led_blink(1, 50, 50);
        }
        if (CURRENT_DIALOG_MAYBE == DLG_MENU)
        {
            /* Horshack suggested to run the bootflag routines with IRQ/FIQ disabled */
            uint32_t old = cli();
            call( eventproc );
            sei(old);
        }
    }
}

static void
call_init_funcs()
{
    extern struct task_create _init_funcs_start[];
    extern struct task_create _init_funcs_end[];
    struct task_create * init_func = _init_funcs_start;

    for( ; init_func < _init_funcs_end ; init_func++ )
    {
        thunk entry = (thunk) init_func->entry;
        entry();
    }
}

#if defined(CONFIG_7D)
void _card_led_on()  { *(volatile uint32_t*) (CARD_LED_ADDRESS) = (LEDON); }
void _card_led_off() { *(volatile uint32_t*) (CARD_LED_ADDRESS) = 0x38400; } //TODO: Check if this is correct, because reboot.c said 0x838C00
#elif defined(CARD_LED_ADDRESS) && defined(LEDON) && defined(LEDOFF)
void _card_led_on()  { *(volatile uint32_t*) (CARD_LED_ADDRESS) = (LEDON); }
void _card_led_off() { *(volatile uint32_t*) (CARD_LED_ADDRESS) = (LEDOFF); }
#else
void _card_led_on()  { return; }
void _card_led_off() { return; }
#endif

void info_led_on()
{
#ifdef CONFIG_VXWORKS
    LEDBLUE = LEDON;
#elif defined(CONFIG_BLUE_LED)
    call("EdLedOn");
#else
    _card_led_on();
#endif
}
void info_led_off()
{
#ifdef CONFIG_VXWORKS
    LEDBLUE = LEDOFF;
#elif defined(CONFIG_BLUE_LED)
    call("EdLedOff");
#else
    _card_led_off();
#endif
}
void info_led_blink(int times, int delay_on, int delay_off)
{
    for (int i = 0; i < times; i++)
    {
        info_led_on();
        msleep(delay_on);
        info_led_off();
        msleep(delay_off);
    }
}

/** Shadow copy of the NVRAM boot flags stored at 0xF8000000 */
#define NVRAM_BOOTFLAGS     ((void*) 0xF8000000)
struct boot_flags
{
    uint32_t        firmware;   // 0x00
    uint32_t        bootdisk;   // 0x04
    uint32_t        ram_exe;    // 0x08
    uint32_t        update;     // 0x0c
    uint32_t        flag_0x10;
    uint32_t        flag_0x14;
    uint32_t        flag_0x18;
    uint32_t        flag_0x1c;
};

static struct boot_flags * const    boot_flags = NVRAM_BOOTFLAGS;

static void print_bootflags()
{
    bmp_printf( FONT_SMALL, 600, 0,
        "Firmware  %d \n"
        "Bootdisk  %d \n"
        "RAM_EXE   %d \n"
        "Update    %d \n",
        boot_flags->firmware,
        boot_flags->bootdisk,
        boot_flags->ram_exe,
        boot_flags->update
    );
}

/** These are called when new tasks are created */
int my_init_task(int a, int b, int c, int d);
void my_bzero( uint8_t * base, uint32_t size );

/** This just goes into the bss */
#define RELOCSIZE 0x10000
static uint8_t _reloc[ RELOCSIZE ];
#define RELOCADDR ((uintptr_t) _reloc)

/** Translate a firmware address into a relocated address */
#define INSTR( addr ) ( *(uint32_t*)( (addr) - ROMBASEADDR + RELOCADDR ) )

/** Fix a branch instruction in the relocated firmware image */
#define FIXUP_BRANCH( rom_addr, dest_addr ) \
    INSTR( rom_addr ) = BL_INSTR( &INSTR( rom_addr ), (dest_addr) )

/** Specified by the linker */
extern uint32_t _bss_start[], _bss_end[];

static inline void
zero_bss( void )
{
    uint32_t *bss = _bss_start;
    while( bss < _bss_end )
        *(bss++) = 0;
}

void
__attribute__((noreturn,noinline,naked))
copy_and_restart( int offset )
{
    zero_bss();

    // Copy the firmware to somewhere safe in memory
    const uint8_t * const firmware_start = (void*) ROMBASEADDR;
    const uint32_t firmware_len = RELOCSIZE;
    uint32_t * const new_image = (void*) RELOCADDR;

    blob_memcpy( new_image, firmware_start, firmware_start + firmware_len );

    /*
     * in entry2() (0xff010134) make this change to
     * return to our code before calling cstart().
     * This should be a "BL cstart" instruction.
     */
    INSTR( HIJACK_INSTR_BL_CSTART ) = RET_INSTR;

    /*
     * in cstart() (0xff010ff4) make these changes:
     * calls bzero(), then loads bs_end and calls
     * create_init_task
     */
    // Reserve memory after the BSS for our application
    INSTR( HIJACK_INSTR_BSS_END ) = (uintptr_t) _bss_end;

    // Fix the calls to bzero32() and create_init_task()
    FIXUP_BRANCH( HIJACK_FIXBR_BZERO32, bzero32 );
    FIXUP_BRANCH( HIJACK_FIXBR_CREATE_ITASK, create_init_task );

    // Set our init task to run instead of the firmware one
    INSTR( HIJACK_INSTR_MY_ITASK ) = (uint32_t) my_init_task;
    
    // Make sure that our self-modifying code clears the cache
    clean_d_cache();
    flush_caches();

    // We enter after the signature, avoiding the
    // relocation jump that is at the head of the data
    thunk reloc_entry = (thunk)( RELOCADDR + 0xC );
    reloc_entry();

    /*
    * We're back!
    * The RAM copy of the firmware startup has:
    * 1. Poked the DMA engine with what ever it does
    * 2. Copied the rw_data segment to 0x1900 through 0x20740
    * 3. Zeroed the BSS from 0x20740 through 0x47550
    * 4. Copied the interrupt handlers to 0x0
    * 5. Copied irq 4 to 0x480.
    * 6. Installed the stack pointers for CPSR mode D2 and D3
    * (we are still in D3, with a %sp of 0x1000)
    * 7. Returned to us.
    *
    * Now is our chance to fix any data segment things, or
    * install our own handlers.
    */

    // This will jump into the RAM version of the firmware,
    // but the last branch instruction at the end of this
    // has been modified to jump into the ROM version
    // instead.
    void (*ram_cstart)(void) = (void*) &INSTR( cstart );
    ram_cstart();

    // Unreachable
    while(1)
        ;
}

// check if autoexec.bin is present on the card
int check_autoexec()
{
    FILE * f = FIO_OpenFile("AUTOEXEC.BIN", 0);
    if (f)
    {
        FIO_CloseFile(f);
        return 1;
    }
    return 0;
}

static void hook_on_canon_menu()
{
    gui_uilock(UILOCK_EVERYTHING);
    SetGUIRequestMode(DLG_MENU);
    for (int i = 0; i < 10; i++)
    {
        msleep(100);
        bmp_fill(COLOR_BLACK, 0, 0, 720, 480);
        bmp_printf(FONT_LARGE, 0, 0, "Magic Lantern install");
    }
}

static void vram_update_luts();
static int install();
static int uninstall();

//~ Called from my_init_task
static void install_task();

/** Initial task setup.
 *
 * This is called instead of the task at 0xFF811DBC.
 * It does all of the stuff to bring up the debug manager,
 * the terminal drivers, stdio, stdlib and armlib.
 */
int my_init_task(int a, int b, int c, int d)
{
    // Call their init task
    int ans = init_task(a,b,c,d);
    
#if !defined(CONFIG_NO_ADDITIONAL_VERSION)
    // Re-write the version string.
    // Don't use strcpy() so that this can be done
    // before strcpy() or memcpy() are located.
    extern char additional_version[];
    additional_version[0] = '-';
    additional_version[1] = 'm';
    additional_version[2] = 'l';
    additional_version[3] = '\0';
#endif
    
    msleep(3000);
    
    task_create("install_task", 0x1b, 0x4000, install_task, 0);
    return ans;
}

static int normal_font = FONT_LARGE;
static int error_font = FONT(FONT_LARGE, COLOR_RED, COLOR_BLACK);
static int warning_font = FONT(FONT_LARGE, COLOR_YELLOW, COLOR_BLACK);

/** Perform an initial install and configuration */
/** Return 1 on success, 0 on failure */
static int install(void)
{
    int y = 0;
    bmp_printf(normal_font, 0, y, "Magic Lantern install");
    print_bootflags();

    int autoexec_ok = check_autoexec();
    if (!autoexec_ok)
    {
        bmp_printf(warning_font, 0, y+=30, "AUTOEXEC.BIN not found!");
        bmp_printf(warning_font, 0, y+=30, "Please copy all ML files.");
        msleep(5000);
        return 0;
    }

    if (boot_flags->firmware)
    {
        bmp_printf(error_font, 0, y+=30, "MAIN_FIRMWARE flag is DISABLED!");
        bmp_printf(error_font, 0, y+=30, "Please contact ML developers for a fix.");
        msleep(5000);
        return 0;
    }

    if (!boot_flags->bootdisk )
    {
        bmp_printf(FONT_LARGE, 0, y+=30, "Setting boot flag...");
        call_bootflag_eventproc( "EnableBootDisk" );
        if (!boot_flags->bootdisk )
        {
            bmp_printf(error_font, 0, y+=30, "Could not enable boot flag.");
            msleep(5000);
            return 0;
        }
    }
    else
    {
        bmp_printf(FONT_LARGE, 0, y+=30, "Boot flag is already set.");
    }

    bmp_printf(FONT_LARGE, 0, y+=30, "Making card bootable...");
    extern int bootflag_write_bootblock();
    int bootflag_written = bootflag_write_bootblock();
    if (!bootflag_written)
    {
        bmp_printf(warning_font, 0, y+=30, "Could not make the card bootable.");
        bmp_printf(warning_font, 0, y+=30, "You need to run EOSCard or MacBoot.");
        msleep(5000);
    }

    bmp_printf(FONT_LARGE, 0, y+=30, "Done!");
    bmp_fill(COLOR_BLACK, 0, 430, 720, 50);

    y += 60;
    gui_uilock(UILOCK_SHUTTER);
    
    for (int i = 30; i > 0; i--)
    {
        if (CURRENT_DIALOG_MAYBE == DLG_MENU)
        {
            print_bootflags();
            bmp_printf(FONT(FONT_CANON, COLOR_GREEN2, COLOR_BLACK), 0, y, "Please restart your camera.");
        }

        bmp_printf(FONT(FONT_MED, COLOR_GRAY(50), COLOR_BLACK), 0, 480 - font_med.height, 
            "For removing the boot flag, please wait for %d seconds.  ", i
        );
        msleep(1000);
        
        if (!DISPLAY_IS_ON)
        {
            info_led_blink(1,50,0);
        }
    }
    return 1;
}


static int uninstall(void)
{
    int y = 0;
    bmp_printf(FONT_LARGE, 0, y, "Magic Lantern uninstall");
    print_bootflags();

    if (boot_flags->firmware)
    {
        bmp_printf(error_font, 0, y+=30, "MAIN_FIRMWARE flag is DISABLED!");
        bmp_printf(error_font, 0, y+=30, "Please contact ML developers for a fix.");
        msleep(5000);
        return 0;
    }

    if (boot_flags->bootdisk )
    {
        bmp_printf(FONT_LARGE, 0, y+=30, "Disabling boot flag...");
        call_bootflag_eventproc( "DisableBootDisk" );
        if (boot_flags->bootdisk )
        {
            bmp_printf(error_font, 0, y+=30, "Could not disable boot flag.");
            msleep(5000);
            return 0;
        }
    }
    else
    {
        bmp_printf(FONT_LARGE, 0, y+=30, "Boot flag is not set.");
    }

    bmp_printf(FONT_LARGE, 0, y+=30, "Done!");
    bmp_fill(COLOR_BLACK, 0, 430, 720, 50);
    return 1;
}

void install_task()
{
    call("DisablePowerSave");
    call_init_funcs();
    vram_update_luts();
    _find_ml_card();
    _load_fonts();
    bmp_printf(FONT_LARGE, 0, 0, "Please wait...");
    
    msleep(1000);
    
    hook_on_canon_menu();
    
    /* initial install */
    int ok = install();
    
    if (ok)
    {
        /* install successful, user waited for 30 seconds => uninstall */
        info_led_on();
        hook_on_canon_menu();
        uninstall();
    }
    
    /* finish uninstalling */
    gui_uilock(UILOCK_SHUTTER);
    bmp_printf(FONT_CANON, 0, 430, "Please restart your camera.");
    print_bootflags();
}

void redraw() { clrscr(); }

void gui_uilock(int x)
{
    /* call Canon stub */
    extern void _prop_request_change(unsigned property, const void* addr, size_t len);

    int unlocked = 0x41000000;
    _prop_request_change(PROP_ICU_UILOCK, &unlocked, 4);
    msleep(200);
    _prop_request_change(PROP_ICU_UILOCK, &x, 4);
    msleep(200);
}

/** Dummies **/
void ml_assert_handler(char* msg, char* file, int line, const char* func) {};
void bvram_mirror_init(){};
int display_is_on_550D = 0;
int get_display_is_on_550D() { return display_is_on_550D; }
void config_save(){};
int get_ms_clock_value() { return 0; }
char * get_task_name_from_id(int id) { return ""; }
void beep() {} ;
uint32_t ml_used_mem = 0;
uint32_t ml_reserved_mem = 0;
void menu_redraw() {} ;
int should_run_polling_action(int period_ms, int* last_updated_time) { return 0; }
void menu_add( const char * name, struct menu_entry * new_entry, int count ) {} 
void menu_open_submenu() {} 
void redraw_after(int time) {}
uint32_t edmac_get_address(uint32_t channel) { return 0; }
void EngDrvOut(uint32_t reg, uint32_t value) {}
int hdmi_code = 0;
void update_vram_params(){};
void draw_line(int x1, int y1, int x2, int y2, int cl){}
void NotifyBox(int timeout, char* fmt, ...) {}
struct memSuite * _shoot_malloc_suite(size_t size) { return 0; }
struct memSuite * _shoot_malloc_suite_contig(size_t size) { return 0; }
void _shoot_free_suite(struct memSuite * suite) {}
struct memSuite * _srm_malloc_suite(int num) { return 0; }
void _srm_free_suite(struct memSuite * suite) {}

int y_times_BMPPITCH_cache[BMP_H_PLUS - BMP_H_MINUS];

static void vram_update_luts()
{
    for (int y = BMP_H_MINUS; y < BMP_H_PLUS; y++) 
    {
        y_times_BMPPITCH_cache[y - BMP_H_MINUS] = y * BMPPITCH;
    }
}
