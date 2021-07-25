#define FEATURE_VRAM_RGBA

// Don't Click Me menu looks to be intended as a place
// for devs to put custom code in debug.c run_test(),
// and allowing triggering from a menu context.
#define FEATURE_DONT_CLICK_ME

#define FEATURE_SHOW_SHUTTER_COUNT
#define FEATURE_SHOW_TOTAL_SHOTS

// working but incomplete, some allocators don't report
// anything yet as they're faked / not yet found
#define FEATURE_SHOW_FREE_MEMORY

#undef CONFIG_CRASH_LOG
#undef CONFIG_TSKMON
#undef CONFIG_PROP_REQUEST_CHANGE
#undef CONFIG_AUTOBACKUP_ROM

//~kitor: add bootdisk menu for easier testing on foreign camera :)
#define FEATURE_BOOTFLAG_MENU
