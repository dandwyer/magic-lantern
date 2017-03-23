/**
 * 450D (captured one picture and enabled LiveView)
 */
static struct mpu_init_spell mpu_init_spells_450D[] = {
    { { 0x06, 0x04, 0x02, 0x00, 0x00 }, {                       /* spell #1 */
        { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 },                 /* reply #1.1 */
        { 0x08, 0x07, 0x01, 0x33, 0x00, 0x00, 0x00, 0x00 },     /* reply #1.2 */
        { 0x14, 0x12, 0x02, 0x04, 0x0d, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00 },/* reply #1.3 */
        { 0x06, 0x05, 0x01, 0x20, 0x00, 0x00 },                 /* reply #1.4 */
        { 0x06, 0x05, 0x01, 0x21, 0x01, 0x00 },                 /* reply #1.5 */
        { 0x06, 0x05, 0x01, 0x22, 0x00, 0x00 },                 /* reply #1.6 */
        { 0x06, 0x05, 0x03, 0x0c, 0x01, 0x00 },                 /* reply #1.7 */
        { 0x06, 0x05, 0x03, 0x0d, 0x01, 0x00 },                 /* reply #1.8 */
        { 0x06, 0x05, 0x03, 0x0e, 0x01, 0x00 },                 /* reply #1.9 */
        { 0x08, 0x06, 0x01, 0x23, 0x00, 0x00, 0x00 },           /* reply #1.10 */
        { 0x08, 0x06, 0x01, 0x24, 0x00, 0x00, 0x00 },           /* reply #1.11, PROP_CARD2_STATUS(0) */
        { 0x08, 0x06, 0x01, 0x25, 0x00, 0x00, 0x00 },           /* reply #1.12 */
        { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 },                 /* reply #1.13 */
        { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 },                 /* reply #1.14 */
        { 0x06, 0x05, 0x01, 0x2c, 0x02, 0x00 },                 /* reply #1.15 */
        { 0x06, 0x05, 0x03, 0x20, 0x01, 0x00 },                 /* reply #1.16 */
        { 0x06, 0x05, 0x01, 0x42, 0x00, 0x00 },                 /* reply #1.17 */
        { 0x06, 0x05, 0x01, 0x43, 0x00, 0x00 },                 /* reply #1.18 */
        { 0x06, 0x05, 0x01, 0x44, 0x00, 0x00 },                 /* reply #1.19 */
        { 0x06, 0x05, 0x01, 0x46, 0x00, 0x00 },                 /* reply #1.20 */
        { 0x06, 0x05, 0x01, 0x3a, 0x01, 0x00 },                 /* reply #1.21 */
        { 0x08, 0x06, 0x01, 0x47, 0x0a, 0x04, 0x00 },           /* reply #1.22 */
        { 0x2c, 0x2a, 0x02, 0x00, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x14, 0x50, 0x00, 0x00, 0x00, 0x00, 0x81, 0x01, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x65, 0x38, 0x01 },/* reply #1.23 */
        { 0x06, 0x05, 0x03, 0x04, 0x00, 0x00 },                 /* reply #1.24 */
        { 0x06, 0x05, 0x03, 0x05, 0x02, 0x00 },                 /* reply #1.25 */
        { 0x14, 0x13, 0x03, 0x30, 0x6c, 0x6c, 0x6c, 0x21, 0x6c, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00 },/* reply #1.26 */
        { 0x0e, 0x0c, 0x03, 0x2e, 0x00, 0x00, 0x8d, 0x44, 0x00, 0x00, 0x9e, 0x56, 0x00 },/* reply #1.27 */
        { 0x0a, 0x08, 0x03, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.28 */
        { 0x06, 0x05, 0x01, 0x38, 0x00, 0x00 },                 /* reply #1.29 */
        { 0x06, 0x05, 0x01, 0x39, 0x00, 0x00 },                 /* reply #1.30 */
        { 0x08, 0x06, 0x01, 0x0a, 0x00, 0x01, 0x00 },           /* reply #1.31 */
        { 0x06, 0x05, 0x03, 0x23, 0x19, 0x00 },                 /* reply #1.32 */
        { 0x1e, 0x1d, 0x03, 0x24, 0x45, 0x46, 0x2d, 0x53, 0x31, 0x38, 0x2d, 0x35, 0x35, 0x6d, 0x6d, 0x20, 0x66, 0x2f, 0x33, 0x2e, 0x35, 0x2d, 0x35, 0x2e, 0x36, 0x20, 0x49, 0x53, 0x00, 0x00 },/* reply #1.33 */
        { 0x06, 0x04, 0x03, 0x25, 0x00 },                       /* reply #1.34 */
        { 0x08, 0x06, 0x01, 0x45, 0x00, 0x10, 0x00 },           /* reply #1.35 */
        { 0 } } },
    { { 0x08, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00 }, {           /* spell #2, Complete WaitID = 0x80000006 */
        { 0x06, 0x05, 0x01, 0x09, 0x00, 0x00 },                 /* reply #2.1 */
        { 0x06, 0x05, 0x01, 0x0d, 0x00, 0x00 },                 /* reply #2.2 */
        { 0x06, 0x05, 0x01, 0x3e, 0x00, 0x00 },                 /* reply #2.3 */
        { 0x06, 0x05, 0x01, 0x3f, 0x00, 0x00 },                 /* reply #2.4 */
        { 0x06, 0x05, 0x01, 0x40, 0x00, 0x00 },                 /* reply #2.5 */
        { 0x06, 0x05, 0x01, 0x41, 0x00, 0x00 },                 /* reply #2.6 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x11, 0x01, 0x00 }, {                 /* spell #3 */
        { 0 } } },
    { { 0x06, 0x05, 0x04, 0x0e, 0x01, 0x00 }, {                 /* spell #4 */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #5 */
        { 0 } } },
    { { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 }, {                 /* spell #6 */
        { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 },                 /* reply #6.1 */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #7 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x63, 0x00 }, {                 /* spell #8, PROP_BURST_COUNT(99) */
        { 0x06, 0x05, 0x06, 0x13, 0x00, 0x00 },                 /* reply #8.1, bindReceiveSwitch(19, 0) */
        { 0 } } },
    { { 0x06, 0x04, 0x03, 0x10, 0x00 }, {                       /* spell #9 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x00, 0x00 }, {                 /* spell #10, PROP_BURST_COUNT(0) */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x00, 0x00 }, {                 /* spell #11, PROP_BURST_COUNT(0) */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x00, 0x00 }, {                 /* spell #12, PROP_BURST_COUNT(0) */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x00, 0x00 }, {                 /* spell #13, PROP_BURST_COUNT(0) */
        { 0 } } },
    { { 0x08, 0x06, 0x01, 0x24, 0x00, 0x01, 0x00 }, {           /* spell #14 */
        { 0x08, 0x06, 0x01, 0x24, 0x00, 0x01, 0x00 },           /* reply #14.1, PROP_CARD2_STATUS(1) */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #15 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x00, 0x00 }, {                 /* spell #16, PROP_BURST_COUNT(0) */
        { 0 } } },
    { { 0x08, 0x06, 0x01, 0x27, 0x00, 0x64, 0x00 }, {           /* spell #17, PROP_CARD1_FOLDER_NUMBER(100) */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x01, 0x32, 0x00 }, {/* spell #18 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x00, 0x00 }, {                 /* spell #19, PROP_BURST_COUNT(0) */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x0d, 0x00, 0x00 }, {                 /* spell #20 */
        { 0x06, 0x05, 0x03, 0x0d, 0x00, 0x00 },                 /* reply #20.1 */
        { 0 } } },
    { { 0x08, 0x07, 0x01, 0x2a, 0x17, 0xcd, 0x00, 0x02 }, {     /* spell #21, PROP_CARD2_FILE_NUMBER(6093) */
        { 0 } } },
    { { 0x06, 0x05, 0x02, 0x0a, 0x00, 0x00 }, {                 /* spell #22 */
        { 0x0a, 0x08, 0x03, 0x00, 0x61, 0x00, 0x00, 0x2b, 0x00 },/* reply #22.1 */
        { 0x14, 0x12, 0x03, 0x15, 0x01, 0x30, 0x5b, 0x00, 0x30, 0x00, 0x12, 0x00, 0x37, 0x91, 0x75, 0x92, 0x1f, 0x00, 0x00 },/* reply #22.2 */
        { 0x06, 0x05, 0x03, 0x17, 0x98, 0x00 },                 /* reply #22.3 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x0c, 0x00 }, {                 /* spell #23, PROP_BURST_COUNT(12) */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                 /* spell #24 */
        { 0 } } },
    { { 0x08, 0x06, 0x03, 0x18, 0x00, 0x00, 0x00 }, {           /* spell #25 */
        { 0 } } },
    { { 0x08, 0x06, 0x03, 0x1f, 0x00, 0x00, 0x00 }, {           /* spell #26 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x13, 0x00, 0x00 }, {                 /* spell #27 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x1e, 0x00, 0x00 }, {                 /* spell #28 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                 /* spell #29 */
        { 0 } } },
    { { 0x06, 0x05, 0x02, 0x0a, 0x01, 0x00 }, {                 /* spell #30 */
        { 0x42, 0x41, 0x0a, 0x08, 0xff, 0x3f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x38, 0x01, 0x01, 0x00, 0x60, 0x04, 0x01, 0x01, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #30.1, PD_NotifyOlcInfoChanged */
        { 0x06, 0x05, 0x06, 0x11, 0x01, 0x00 },                 /* reply #30.2, bindReceiveSwitch(17, 1) */
        { 0x06, 0x05, 0x06, 0x12, 0x00, 0x00 },                 /* reply #30.3, bindReceiveSwitch(18, 0) */
        { 0x06, 0x05, 0x06, 0x13, 0x00, 0x00 },                 /* reply #30.4, bindReceiveSwitch(19, 0) */
        { 0x06, 0x05, 0x06, 0x1c, 0x00, 0x00 },                 /* reply #30.5, bindReceiveSwitch(28, 0) */
        { 0 } } },
    { { 0x06, 0x05, 0x09, 0x11, 0x01, 0x00 }, {                 /* spell #31 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                 /* spell #32 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                 /* spell #33 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                 /* spell #34 */
        { 0x06, 0x04, 0x05, 0x00, 0x00 },                       /* reply #34.1 */
        { 0x0c, 0x0a, 0x0a, 0x08, 0x02, 0x00, 0x01, 0x01, 0x00, 0x60, 0x00 },/* reply #34.2, PD_NotifyOlcInfoChanged */
        { 0x0a, 0x08, 0x0a, 0x08, 0x01, 0x00, 0x02, 0x00, 0x00 },/* reply #34.3, PD_NotifyOlcInfoChanged */
        { 0x0c, 0x0b, 0x0a, 0x08, 0x00, 0x02, 0x01, 0x01, 0x00, 0x20, 0x00, 0x00 },/* reply #34.4, PD_NotifyOlcInfoChanged */
        { 0x0c, 0x0b, 0x0a, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 },/* reply #34.5, PD_NotifyOlcInfoChanged */
        { 0x0c, 0x0a, 0x0a, 0x08, 0x02, 0x00, 0x01, 0x01, 0x00, 0x63, 0x00 },/* reply #34.6, PD_NotifyOlcInfoChanged */
        { 0x06, 0x04, 0x05, 0x01, 0x00 },                       /* reply #34.7 */
        { 0x2a, 0x29, 0x05, 0x02, 0x62, 0x38, 0x63, 0x38, 0x60, 0x00, 0x72, 0x72, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x06, 0x00, 0x00, 0x99, 0x92, 0x70, 0x77, 0x00, 0x00, 0x35, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 },/* reply #34.8 */
        { 0x0a, 0x08, 0x0a, 0x08, 0x01, 0x00, 0x04, 0x00, 0x00 },/* reply #34.9, PD_NotifyOlcInfoChanged */
        { 0x12, 0x10, 0x0a, 0x08, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #34.10, PD_NotifyOlcInfoChanged */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x0b, 0x00, 0x00, 0x00, 0x01, 0x00 }, {/* spell #35 */
        { 0x0c, 0x0a, 0x0a, 0x08, 0x10, 0x00, 0x04, 0x02, 0x01, 0x32, 0x00 },/* reply #35.1, PD_NotifyOlcInfoChanged */
        { 0 } } },
    { { 0x08, 0x06, 0x01, 0x27, 0x00, 0x64, 0x00 }, {           /* spell #36, PROP_CARD1_FOLDER_NUMBER(100) */
        { 0 } } },
    { { 0x08, 0x07, 0x01, 0x2a, 0x17, 0xce, 0x00, 0x02 }, {     /* spell #37, PROP_CARD2_FILE_NUMBER(6094) */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x07, 0x0b, 0x00 }, {                 /* spell #38, PROP_BURST_COUNT(11) */
        { 0 } } },
    { { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x01, 0x31, 0x00 }, {/* spell #39 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x11, 0x02, 0x00 }, {                 /* spell #40 */
        { 0x0c, 0x0a, 0x0a, 0x08, 0x10, 0x00, 0x04, 0x02, 0x01, 0x31, 0x00 },/* reply #40.1, PD_NotifyOlcInfoChanged */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x0d, 0x01, 0x00 }, {                 /* spell #41 */
        { 0x06, 0x05, 0x03, 0x0d, 0x01, 0x00 },                 /* reply #41.1 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                 /* spell #42 */
        { 0x32, 0x30, 0x05, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0x00, 0x25, 0x00, 0x21, 0x0c, 0x23, 0x7c, 0xbc, 0x7c, 0x00, 0x00, 0x94, 0xde, 0x9d, 0x5a, 0xa4, 0x21, 0x00 },/* reply #42.1 */
        { 0x06, 0x04, 0x05, 0x04, 0x00 },                       /* reply #42.2 */
        { 0x06, 0x04, 0x05, 0x0b, 0x00 },                       /* reply #42.3 */
        { 0x0c, 0x0a, 0x0a, 0x08, 0x02, 0x00, 0x01, 0x01, 0x00, 0x60, 0x00 },/* reply #42.4, PD_NotifyOlcInfoChanged */
        { 0x0a, 0x08, 0x0a, 0x08, 0x01, 0x00, 0x03, 0x00, 0x00 },/* reply #42.5, PD_NotifyOlcInfoChanged */
        { 0x0c, 0x0b, 0x0a, 0x08, 0x00, 0x02, 0x01, 0x01, 0x00, 0x20, 0x00, 0x00 },/* reply #42.6, PD_NotifyOlcInfoChanged */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                 /* spell #43 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                 /* spell #44 */
        { 0x0c, 0x0a, 0x0a, 0x08, 0x02, 0x00, 0x01, 0x01, 0x00, 0x63, 0x00 },/* reply #44.1, PD_NotifyOlcInfoChanged */
        { 0x06, 0x04, 0x05, 0x07, 0x00 },                       /* reply #44.2 */
        { 0x0e, 0x0c, 0x0a, 0x08, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #44.3, PD_NotifyOlcInfoChanged */
        { 0x0c, 0x0b, 0x0a, 0x08, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #44.4, PD_NotifyOlcInfoChanged */
        { 0x06, 0x05, 0x06, 0x0c, 0x01, 0x00 },                 /* reply #44.5, bindReceiveSwitch(12, 1) */
        { 0 } } },
    { { 0x06, 0x04, 0x04, 0x0a, 0x00 }, {                       /* spell #45 */
        { 0 } } },
    { { 0x08, 0x06, 0x04, 0x0c, 0x03, 0x00, 0x00 }, {           /* spell #46 */
        { 0x08, 0x06, 0x04, 0x0c, 0x03, 0x00, 0x01 },           /* reply #46.1 */
        { 0 } } },
    { { 0x06, 0x04, 0x04, 0x13, 0x00 }, {                       /* spell #47 */
        { 0 } } },
    { { 0x08, 0x06, 0x00, 0x00, 0x04, 0x0c, 0x00 }, {           /* spell #48, Complete WaitID = 0x80040004 */
        { 0x08, 0x06, 0x09, 0x0a, 0x70, 0x73, 0x00 },           /* reply #48.1 */
        { 0x08, 0x06, 0x09, 0x0d, 0x00, 0x00, 0x00 },           /* reply #48.2 */
        { 0 } } },
    { { 0x06, 0x05, 0x09, 0x0b, 0x02, 0x00 }, {                 /* spell #49 */
        { 0 } } },
    { { 0x06, 0x04, 0x09, 0x00, 0x00 }, {                       /* spell #50 */
        { 0x3c, 0x3a, 0x09, 0x00, 0x3b, 0x31, 0xc0, 0x00, 0x40, 0x7a, 0xa0, 0x00, 0x3d, 0x60, 0x60, 0x00, 0xb9, 0xae, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x5d, 0x60, 0x00, 0xba, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x54, 0x0b, 0x0a, 0x31, 0x30, 0x5b, 0x59, 0x01, 0x4a, 0x77, 0x77, 0x00, 0x35, 0x00, 0x25, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #50.1 */
        { 0 } } },
    { { 0x06, 0x05, 0x09, 0x04, 0x31, 0x00 }, {                 /* spell #51 */
        { 0x0a, 0x08, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #51.1 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                 /* spell #52 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                 /* spell #53 */
        { 0 } } },
    { { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                 /* spell #54 */
        { 0 } } },
    { { 0x06, 0x05, 0x09, 0x11, 0x01, 0x00 }, {                 /* spell #55 */
        { 0 } } },
};
