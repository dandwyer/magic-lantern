/**
 * 50D version - includes card format and incomplete shutdown attempt
 */
static struct mpu_init_spell mpu_init_spells_50D[] = {
    { { 0x06, 0x04, 0x02, 0x00, 0x00 }, .description = "Init", .out_spells = { /* spell #1 */
        { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 },                 /* reply #1.1, PROP_CARD_EXTENSION */
        { 0x08, 0x07, 0x01, 0x33, 0x00, 0x00, 0x00, 0x00 },     /* reply #1.2, PROP_AE_MODE_CUSTOM */
        { 0x0e, 0x0c, 0x02, 0x05, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.3, PROP_CFN_1 */
        { 0x0a, 0x09, 0x02, 0x06, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.4, PROP_CFN_2 */
        { 0x14, 0x12, 0x02, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.5, PROP_CFN_3 */
        { 0x0e, 0x0d, 0x02, 0x08, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.6, PROP_CFN_4 */
        { 0x06, 0x05, 0x01, 0x20, 0x01, 0x00 },                 /* reply #1.7, PROP_CARD1_EXISTS */
        { 0x06, 0x05, 0x01, 0x21, 0x00, 0x00 },                 /* reply #1.8, PROP_CARD2_EXISTS */
        { 0x06, 0x05, 0x01, 0x22, 0x00, 0x00 },                 /* reply #1.9, PROP_CARD3_EXISTS */
        { 0x06, 0x05, 0x03, 0x0c, 0x01, 0x00 },                 /* reply #1.10, PROP_CARD1_RECORD */
        { 0x06, 0x05, 0x03, 0x0d, 0x01, 0x00 },                 /* reply #1.11, PROP_CARD2_RECORD */
        { 0x06, 0x05, 0x03, 0x0e, 0x01, 0x00 },                 /* reply #1.12, PROP_CARD3_RECORD */
        { 0x08, 0x06, 0x01, 0x23, 0x00, 0x00, 0x00 },           /* reply #1.13, PROP_CARD1_STATUS(00) */
        { 0x08, 0x06, 0x01, 0x24, 0x00, 0x00, 0x00 },           /* reply #1.14, PROP_CARD2_STATUS(00) */
        { 0x08, 0x06, 0x01, 0x25, 0x00, 0x00, 0x00 },           /* reply #1.15, PROP_CARD3_STATUS(00) */
        { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 },                 /* reply #1.16, PROP_SAVE_MODE */
        { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 },                 /* reply #1.17, PROP_CARD_EXTENSION */
        { 0x06, 0x05, 0x01, 0x2c, 0x01, 0x00 },                 /* reply #1.18, PROP_CURRENT_MEDIA */
        { 0x06, 0x05, 0x03, 0x20, 0x01, 0x00 },                 /* reply #1.19, PROP_STARTUP_CONDITION */
        { 0x06, 0x05, 0x01, 0x42, 0x00, 0x00 },                 /* reply #1.20, PROP_PHOTO_STUDIO_MODE */
        { 0x06, 0x05, 0x01, 0x43, 0x00, 0x00 },                 /* reply #1.21, PROP 80040017 */
        { 0x06, 0x05, 0x01, 0x44, 0x00, 0x00 },                 /* reply #1.22, PROP 80040018 */
        { 0x06, 0x05, 0x01, 0x46, 0x00, 0x00 },                 /* reply #1.23, PROP_PHOTO_STUDIO_ENABLE_ISOCOMP */
        { 0x06, 0x05, 0x01, 0x48, 0x02, 0x00 },                 /* reply #1.24, PROP_LIVE_VIEW_MOVIE_SELECT */
        { 0x06, 0x05, 0x01, 0x49, 0x00, 0x00 },                 /* reply #1.25, PROP_LIVE_VIEW_AF_SYSTEM */
        { 0x06, 0x05, 0x01, 0x4b, 0x00, 0x00 },                 /* reply #1.26, PROP_LIVE_VIEW_VIEWTYPE_SELECT */
        { 0x08, 0x06, 0x01, 0x47, 0x0a, 0x01, 0x00 },           /* reply #1.27, PROP_SELFTIMER_CONTINUOUS_NUM */
        { 0x06, 0x05, 0x01, 0x04, 0x00, 0x00 },                 /* reply #1.28, PROP_AF_MODE */
        { 0x06, 0x05, 0x01, 0x06, 0x30, 0x00 },                 /* reply #1.29, PROP_APERTURE */
        { 0x2c, 0x2a, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x00, 0x09, 0x13, 0x88, 0x00, 0x00, 0x00, 0x00, 0x84, 0x06, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x03, 0x06, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x3c, 0x00, 0x63, 0x30, 0x01 },/* reply #1.30, Init */
        { 0x06, 0x05, 0x03, 0x04, 0x00, 0x00 },                 /* reply #1.31, PROP_POWER_KIND */
        { 0x06, 0x05, 0x03, 0x05, 0x02, 0x00 },                 /* reply #1.32, PROP_POWER_LEVEL */
        { 0x1e, 0x1c, 0x03, 0x30, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x20, 0x20, 0x00, 0x2d, 0x00, 0x2d, 0x00, 0x2d, 0x00, 0x2d, 0x00, 0x2d, 0x00, 0x2d, 0x00, 0xe0, 0x00, 0xe0, 0x00 },/* reply #1.33, PROP 8003002A */
        { 0x06, 0x05, 0x01, 0x38, 0x00, 0x00 },                 /* reply #1.34, PROP 80040005 */
        { 0x06, 0x05, 0x01, 0x39, 0x00, 0x00 },                 /* reply #1.35, PROP 80040006 */
        { 0x08, 0x06, 0x01, 0x0a, 0x00, 0x01, 0x00 },           /* reply #1.36, PROP_AFPOINT */
        { 0x0e, 0x0c, 0x03, 0x2e, 0x00, 0x00, 0x2e, 0x13, 0x00, 0x00, 0x2e, 0xce, 0x00 },/* reply #1.37, PROP_SHUTTER_COUNTER */
        { 0x0a, 0x08, 0x03, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.38, PROP_SPECIAL_OPTION */
        { 0x06, 0x05, 0x03, 0x23, 0x16, 0x00 },                 /* reply #1.39 */
        { 0x1c, 0x1a, 0x03, 0x24, 0x45, 0x46, 0x2d, 0x53, 0x31, 0x38, 0x2d, 0x35, 0x35, 0x6d, 0x6d, 0x20, 0x66, 0x2f, 0x33, 0x2e, 0x35, 0x2d, 0x35, 0x2e, 0x36, 0x00, 0x00 },/* reply #1.40, PROP_LENS_NAME: EF-S18-55mm f/3.5-5.6 */
        { 0x06, 0x04, 0x03, 0x25, 0x00 },                       /* reply #1.41 */
        { 0x08, 0x06, 0x01, 0x45, 0x00, 0x10, 0x00 },           /* reply #1.42, PROP_METERING_TIMER_FOR_LV */
        { 0 } } },
    { { 0x08, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00 }, .description = "Complete WaitID = 0x80000001 Init", .out_spells = { /* spell #2 */
        { 0x06, 0x05, 0x01, 0x09, 0x00, 0x00 },                 /* reply #2.1, PROP_FEC */
        { 0x06, 0x05, 0x01, 0x0d, 0x09, 0x00 },                 /* reply #2.2, PROP_WB_MODE_PH */
        { 0x06, 0x05, 0x01, 0x3e, 0x00, 0x00 },                 /* reply #2.3, PROP_ELECTRIC_SHUTTER_MODE */
        { 0x06, 0x05, 0x01, 0x3f, 0x00, 0x00 },                 /* reply #2.4, PROP_FLASH_ENABLE */
        { 0x06, 0x05, 0x01, 0x40, 0x00, 0x00 },                 /* reply #2.5, PROP_STROBO_ETTLMETER */
        { 0x06, 0x05, 0x01, 0x41, 0x00, 0x00 },                 /* reply #2.6, PROP_STROBO_CURTAIN */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x0e, 0x00, 0x00 }, .description = "PROP_CARD3_RECORD", .out_spells = { /* spell #3 */
        { 0x06, 0x05, 0x03, 0x0e, 0x00, 0x00 },                 /* reply #3.1, PROP_CARD3_RECORD */
        { 0 } } },
    { { 0x06, 0x05, 0x01, 0x22, 0x00, 0x00 }, .description = "PROP_CARD3_EXISTS", .out_spells = { /* spell #4 */
        { 0x06, 0x05, 0x01, 0x22, 0x00, 0x00 },                 /* reply #4.1, PROP_CARD3_EXISTS */
        { 0 } } },
    { { 0x08, 0x06, 0x01, 0x25, 0x00, ARG0, 0x00 }, .description = "PROP_CARD3_STATUS", .out_spells = { /* spell #5 */
        { 0x08, 0x06, 0x01, 0x25, 0x00, ARG0, 0x00 },           /* reply #5.1, PROP_CARD3_STATUS(00) */
        { 0 } } },
    { { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 }, .description = "PROP_CARD_EXTENSION", .out_spells = { /* spell #6 */
        { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 },                 /* reply #6.1, PROP_CARD_EXTENSION */
        { 0x0a, 0x08, 0x01, 0x34, 0x00, 0x00, 0x06, 0x03, 0x01 },/* reply #6.2, PROP_CARD1_IMAGE_QUALITY */
        { 0 } } },
    { { 0x08, 0x06, 0x00, 0x00, 0x01, 0x34, 0x00 }, .description = "Complete WaitID = 0x8000002F PROP_CARD1_IMAGE_QUALITY", .out_spells = { /* spell #7 */
        { 0x0a, 0x08, 0x01, 0x35, 0x00, 0x00, 0x01, 0x03, 0x01 },/* reply #7.1, PROP_CARD2_IMAGE_QUALITY */
        { 0 } } },
    { { 0x08, 0x06, 0x00, 0x00, 0x01, 0x35, 0x00 }, .description = "Complete WaitID = 0x80000030 PROP_CARD2_IMAGE_QUALITY", .out_spells = { /* spell #8 */
        { 0x0a, 0x08, 0x01, 0x36, 0x00, 0x00, 0x06, 0x03, 0x01 },/* reply #8.1, PROP_CARD3_IMAGE_QUALITY */
        { 0 } } },
    { { 0x08, 0x06, 0x00, 0x00, 0x01, 0x36, 0x00 }, .description = "Complete WaitID = 0x80000031 PROP_CARD3_IMAGE_QUALITY", .out_spells = { /* spell #9 */
        { 0x08, 0x06, 0x05, 0x0d, 0x11, 0xa4, 0x00 },           /* reply #9.1 */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00 }, .description = "PROP_AVAIL_SHOT", .out_spells = { /* spell #10 */
        { 0 } } },
    { { 0x06, 0x04, 0x03, 0x10, 0x00 }, .description = "PROP 80030008", .out_spells = { /* spell #11 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0xff, 0x00 }, .description = "PROP_BURST_COUNT", .out_spells = { /* spell #12 */
        { 0x06, 0x05, 0x06, 0x13, 0x00, 0x00 },                 /* reply #12.1, bindReceiveSwitch(19, 0) */
        { 0 } } },
    { { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 }, .description = "PROP_SAVE_MODE", .out_spells = { /* spell #13 */
        { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 },                 /* reply #13.1, PROP_SAVE_MODE */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00 }, .description = "PROP 80030007", .out_spells = { /* spell #14 */
        { 0 } } },
    { { 0x06, 0x05, 0x04, 0x0e, 0x00, 0x00 }, .description = "PROP 8002000D", .out_spells = { /* spell #15 */
        { 0x06, 0x05, 0x04, 0x0e, 0x00, 0x00 },                 /* reply #15.1, PROP 8002000D */
        { 0 } } },
    { { 0x08, 0x06, 0x01, 0x25, 0x00, ARG0, 0x00 }, .description = "PROP_CARD3_STATUS", .out_spells = { /* spell #16 */
        { 0x08, 0x06, 0x01, 0x25, 0x00, ARG0, 0x00 },           /* reply #16.1, PROP_CARD3_STATUS(00) */
//      { 0x08, 0x06, 0x05, 0x0d, 0x11, 0xa4, 0x00 },           /* reply #16.2 - infinite loop sending LensBP data? */
        { 0 } } },
//  { { 0x32, 0x30, 0x05, 0x0d, 0xca, 0x38, 0xb2, 0xbd, 0x9e, 0xb7, 0xd1, 0x86, 0xc9, 0x38, 0x05, 0xd3, 0xe7, 0xca, 0xae, 0xa0, 0x39, 0xda, 0xc5, 0xc9, 0x2a, 0x07, 0xc9, 0x88, 0xa6, 0xd1, 0x28, 0x72, 0xd2, 0x60, 0xc8, 0xc7, 0x04, 0xd6, 0x62, 0x42, 0x47, 0x28, 0x29, 0xd7, 0x1a, 0xcf, 0x69, 0x09, 0x00 }, {/* spell #17 */
//      { 0x08, 0x06, 0x05, 0x0d, 0x11, 0xa4, 0x00 },           /* reply #17.1, delayed by 137 ms, likely external input */
//      { 0 } } },
//  { { 0x32, 0x30, 0x05, 0x0d, 0xca, 0x38, 0xb2, 0xbd, 0x9e, 0xb7, 0xd1, 0x86, 0xc9, 0x38, 0x05, 0xd3, 0xe7, 0xca, 0xae, 0xa0, 0x39, 0xda, 0xc5, 0xc9, 0x2a, 0x07, 0xc9, 0x88, 0xa6, 0xd1, 0x28, 0x72, 0xd2, 0x60, 0xc8, 0xc7, 0x04, 0xd6, 0x62, 0x42, 0x47, 0x28, 0x29, 0xd7, 0x1a, 0xcf, 0x69, 0x09, 0x00 }, {/* spell #18 */
//      { 0 } } },
    { { 0x08, 0x06, 0x01, 0x23, 0x00, ARG0, 0x00 }, .description = "PROP_CARD1_STATUS", .out_spells = { /* spell #19 */
        { 0x08, 0x06, 0x01, 0x23, 0x00, ARG0, 0x00 },           /* reply #19.1, PROP_CARD1_STATUS(01) */
        { 0 } } },
    { { 0x08, 0x06, 0x01, 0x26, 0x00, ARG0, 0x00 }, .description = "PROP_CARD1_FOLDER_NUMBER", .out_spells = { /* spell #20 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x10, 0x00 }, .description = "PROP_BURST_COUNT", .out_spells = { /* spell #21 */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x02, 0xcd, 0x00 }, .description = "PROP_AVAIL_SHOT", .out_spells = { /* spell #22 */
        { 0 } } },
    { { 0x08, 0x07, 0x01, 0x29, ARG0, ARG1, 0x00, ARG2 }, .description = "PROP_CARD1_FILE_NUMBER", .out_spells = { /* spell #23 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x11, 0x01, 0x00 }, .description = "PROP_ICU_AUTO_POWEROFF", .out_spells = { /* spell #24 */
        { 0 } } },
    { { 0x06, 0x05, 0x02, 0x0a, 0x00, 0x00 }, {                 /* spell #25 */
        { 0x0a, 0x08, 0x03, 0x00, 0x51, 0x00, 0x00, 0x20, 0x00 },/* reply #25.1, PROP 80030000 */
        { 0x14, 0x12, 0x03, 0x15, 0x01, 0x29, 0x54, 0x00, 0x2d, 0x00, 0x12, 0x00, 0x37, 0x91, 0x25, 0x02, 0x10, 0x00, 0x00 },/* reply #25.2, PROP_LENS */
        { 0x06, 0x05, 0x03, 0x17, 0x9b, 0x00 },                 /* reply #25.3, PROP_EFIC_TEMP */
        { 0x06, 0x05, 0x01, 0x3d, 0x00, 0x00 },                 /* reply #25.4, PROP_TEMP_STATUS */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, .description = "PROP_TFT_STATUS", .out_spells = { /* spell #26 */
        { 0 } } },
    { { 0x06, 0x05, 0x09, 0x11, 0x01, 0x00 }, {                 /* spell #27 */
        { 0 } } },
    { { 0x08, 0x06, 0x03, 0x18, 0x00, 0x00, 0x00 }, {           /* spell #28 */
        { 0 } } },
    { { 0x08, 0x06, 0x03, 0x1f, 0x00, 0x00, 0x00 }, {           /* spell #29 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x13, 0x00, 0x00 }, {                 /* spell #30 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x1e, 0x00, 0x00 }, {                 /* spell #31 */
        { 0 } } },
    { { 0x08, 0x07, 0x01, 0x3b, 0xff, 0xff, 0x00, 0x00 }, {     /* spell #32 */
        { 0 } } },
    { { 0x08, 0x07, 0x01, 0x3b, 0xff, 0x00, 0x00, 0x00 }, {     /* spell #33 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, .description = "PROP_TFT_STATUS", .out_spells = { /* spell #34 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, .description = "PROP_TFT_STATUS", .out_spells = { /* spell #35 */
        { 0 } } },
    { { 0x06, 0x05, 0x02, 0x0a, 0x01, 0x00 }, {                 /* spell #36 */
        { 0x42, 0x41, 0x0a, 0x08, 0xff, 0x1f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x4d, 0x04, 0x01, 0x02, 0xcd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #36.1, PD_NotifyOlcInfoChanged */
        { 0x06, 0x05, 0x06, 0x11, 0x01, 0x00 },                 /* reply #36.2, GUI_Control:39, bindReceiveSwitch(17, 1) */
        { 0x06, 0x05, 0x06, 0x12, 0x00, 0x00 },                 /* reply #36.3, GUI_Control:41, bindReceiveSwitch(18, 0) */
        { 0x06, 0x05, 0x06, 0x13, 0x00, 0x00 },                 /* reply #36.4, bindReceiveSwitch(19, 0) */
        { 0 } } },
 // { { 0x06, 0x05, 0x03, 0x16, 0x06, 0x00 }, .description = "PROP_BATTERY_CHECK", .out_spells = { 
     // { 0x06, 0x05, 0x03, 0x16, 0x00, 0x00 },                 /* reply #37.1, PROP_BATTERY_CHECK */
     // { 0 } } },
    { { 0x06, 0x05, 0x04, 0x0d, 0x01, 0x00 }, .description = "PROP_ACTIVE_SWEEP_STATUS", .out_spells = { /* spell #37 */
        { 0x06, 0x05, 0x04, 0x0d, 0x00, 0x00 },                 /* reply #37.1, PROP_ACTIVE_SWEEP_STATUS, disabled */
     // { 0x08, 0x06, 0x05, 0x0d, 0x11, 0xa4, 0x00 },           /* reply #37.2, delayed by 106 ms, likely external input */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, .description = "PROP_TFT_STATUS", .out_spells = { /* spell #39 */
      //{ 0x08, 0x06, 0x05, 0x0d, 0x11, 0xa4, 0x00 },           /* reply #40.1 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, .description = "PROP_TFT_STATUS", .out_spells = { /* spell #42 */
        { 0x06, 0x05, 0x03, 0x17, 0x9b, 0x00 },                 /* reply #42.1, PROP_EFIC_TEMP */
        { 0 } } },

    /* MENU->Format selected here */

    { { 0x06, 0x05, 0x03, 0x0c, ARG0, 0x00 }, .description = "PROP_CARD1_RECORD", .out_spells = { /* spell #47 */
        { 0x06, 0x05, 0x03, 0x0c, ARG0, 0x00 },                 /* reply #47.1, PROP_CARD1_RECORD */
        { 0 } } },

    #include "NotifyGUIEvent.h"
    #include "UILock.h"
    #include "CardFormat.h"
    #include "GPS.h"
    #include "Shutdown.h"
};
