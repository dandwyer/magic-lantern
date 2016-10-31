/**
 * 600D (MENU pressed at startup)
 */
static struct mpu_init_spell mpu_init_spells_600D[] = { {
    { 0x06, 0x04, 0x02, 0x00, 0x00 }, {                         /* spell #1 */
        { 0x06, 0x05, 0x01, 0x00, 0x03, 0x00 },                 /* reply #1.1 */
        { 0x06, 0x05, 0x01, 0x05, 0x45, 0x00 },                 /* reply #1.2 */
        { 0x06, 0x05, 0x01, 0x06, 0x5b, 0x00 },                 /* reply #1.3 */
        { 0x06, 0x05, 0x01, 0x0b, 0x00, 0x00 },                 /* reply #1.4 */
        { 0x2c, 0x2a, 0x02, 0x00, 0x03, 0x03, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x87, 0x01, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x45, 0x5b, 0x01 },/* reply #1.5 */
        { 0x08, 0x07, 0x01, 0x33, 0x09, 0x00, 0x00, 0x00 },     /* reply #1.6 */
        { 0x06, 0x05, 0x01, 0x20, 0x00, 0x00 },                 /* reply #1.7 */
        { 0x06, 0x05, 0x01, 0x21, 0x01, 0x00 },                 /* reply #1.8 */
        { 0x06, 0x05, 0x01, 0x22, 0x00, 0x00 },                 /* reply #1.9 */
        { 0x06, 0x05, 0x03, 0x0c, 0x01, 0x00 },                 /* reply #1.10 */
        { 0x06, 0x05, 0x03, 0x0d, 0x01, 0x00 },                 /* reply #1.11 */
        { 0x06, 0x05, 0x03, 0x0e, 0x01, 0x00 },                 /* reply #1.12 */
        { 0x08, 0x06, 0x01, 0x23, 0x00, 0x01, 0x00 },           /* reply #1.13 */
        { 0x08, 0x06, 0x01, 0x24, 0x00, 0x00, 0x00 },           /* reply #1.14 */
        { 0x08, 0x06, 0x01, 0x25, 0x00, 0x01, 0x00 },           /* reply #1.15 */
        { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 },                 /* reply #1.16 */
        { 0x06, 0x05, 0x01, 0x2c, 0x02, 0x00 },                 /* reply #1.17 */
        { 0x06, 0x05, 0x03, 0x20, 0x01, 0x00 },                 /* reply #1.18 */
        { 0x06, 0x05, 0x01, 0x3d, 0x00, 0x00 },                 /* reply #1.19 */
        { 0x06, 0x05, 0x01, 0x42, 0x00, 0x00 },                 /* reply #1.20 */
        { 0x0c, 0x0b, 0x03, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.21 */
        { 0x0c, 0x0b, 0x01, 0x0a, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.22 */
        { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 },                 /* reply #1.23 */
        { 0x06, 0x05, 0x01, 0x49, 0x01, 0x00 },                 /* reply #1.24 */
        { 0x06, 0x05, 0x01, 0x3e, 0x00, 0x00 },                 /* reply #1.25 */
        { 0x08, 0x06, 0x01, 0x45, 0x07, 0x08, 0x00 },           /* reply #1.26 */
        { 0x06, 0x05, 0x01, 0x48, 0x01, 0x00 },                 /* reply #1.27 */
        { 0x06, 0x05, 0x01, 0x4b, 0x01, 0x00 },                 /* reply #1.28 */
        { 0x06, 0x05, 0x01, 0x40, 0x00, 0x00 },                 /* reply #1.29 */
        { 0x06, 0x05, 0x01, 0x41, 0x00, 0x00 },                 /* reply #1.30 */
        { 0x06, 0x05, 0x01, 0x3f, 0x00, 0x00 },                 /* reply #1.31 */
        { 0x08, 0x06, 0x01, 0x57, 0x00, 0x01, 0x00 },           /* reply #1.32 */
        { 0 } } }, {
    { 0x08, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00 }, {             /* spell #2, Complete WaitID = 0x80000001 */
        { 0x1a, 0x18, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #2.1 */
        { 0x06, 0x05, 0x01, 0x48, 0x01, 0x00 },                 /* reply #2.2 */
        { 0x06, 0x05, 0x01, 0x53, 0x00, 0x00 },                 /* reply #2.3 */
        { 0x06, 0x05, 0x01, 0x58, 0x00, 0x00 },                 /* reply #2.4 */
        { 0x06, 0x05, 0x01, 0x59, 0x00, 0x00 },                 /* reply #2.5 */
        { 0x06, 0x05, 0x01, 0x4a, 0x00, 0x00 },                 /* reply #2.6 */
        { 0x06, 0x05, 0x01, 0x50, 0x00, 0x00 },                 /* reply #2.7 */
        { 0x08, 0x06, 0x01, 0x51, 0x78, 0x48, 0x00 },           /* reply #2.8 */
        { 0x06, 0x05, 0x01, 0x52, 0x03, 0x00 },                 /* reply #2.9 */
        { 0x06, 0x05, 0x01, 0x54, 0x00, 0x00 },                 /* reply #2.10 */
        { 0x08, 0x06, 0x01, 0x47, 0x0a, 0x02, 0x00 },           /* reply #2.11 */
        { 0x06, 0x05, 0x03, 0x37, 0x00, 0x00 },                 /* reply #2.12 */
        { 0x12, 0x11, 0x02, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #2.13 */
        { 0x0e, 0x0c, 0x03, 0x2e, 0x00, 0x00, 0x29, 0x7e, 0x00, 0x00, 0x47, 0x49, 0x00 },/* reply #2.14 */
        { 0x08, 0x07, 0x01, 0x55, 0x00, 0x02, 0x01, 0x01 },     /* reply #2.15 */
        { 0x08, 0x07, 0x01, 0x55, 0x00, 0x02, 0x01, 0x01 },     /* reply #2.16 */
        { 0x08, 0x07, 0x01, 0x55, 0x00, 0x02, 0x01, 0x01 },     /* reply #2.17 */
        { 0x08, 0x07, 0x01, 0x55, 0x00, 0x02, 0x01, 0x01 },     /* reply #2.18 */
        { 0 } } }, {
    { 0x08, 0x06, 0x00, 0x00, 0x01, 0x55, 0x00 }, {             /* spell #3, Complete WaitID = 0x8000003F */
        { 0 } } }, {
    { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00 }, { /* spell #4 */
        { 0 } } }, {
    { 0x06, 0x04, 0x03, 0x10, 0x00 }, {                         /* spell #5 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x07, 0xff, 0x00 }, {                   /* spell #6 */
        { 0 } } }, {
    { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 }, {                   /* spell #7 */
        { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 },                 /* reply #7.1 */
        { 0 } } }, {
    { 0x0a, 0x08, 0x03, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00 }, { /* spell #8 */
        { 0 } } }, {
    { 0x06, 0x05, 0x01, 0x56, 0x00, 0x00 }, {                   /* spell #9 */
        { 0 } } }, {
    { 0x06, 0x05, 0x04, 0x0e, 0x01, 0x00 }, {                   /* spell #10 */
        { 0 } } }, {
    { 0x08, 0x06, 0x01, 0x24, 0x00, 0x01, 0x00 }, {             /* spell #11 */
        { 0x08, 0x06, 0x01, 0x24, 0x00, 0x01, 0x00 },           /* reply #11.1 */
        { 0 } } }, {
    { 0x08, 0x06, 0x01, 0x27, 0x00, 0x64, 0x00 }, {             /* spell #12 */
        { 0 } } }, {
    { 0x08, 0x07, 0x01, 0x2a, 0x24, 0xdf, 0x00, 0x00 }, {       /* spell #13 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x07, 0x0b, 0x00 }, {                   /* spell #14 */
        { 0 } } }, {
    { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x00, 0x23, 0x00 }, { /* spell #15 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x11, 0x01, 0x00 }, {                   /* spell #16 */
        { 0 } } }, {
    { 0x06, 0x05, 0x02, 0x0a, 0x00, 0x00 }, {                   /* spell #17 */
        { 0x06, 0x05, 0x01, 0x2c, 0x02, 0x00 },                 /* reply #17.1 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x0d, 0x00, 0x00 }, {                   /* spell #18 */
        { 0x06, 0x05, 0x03, 0x23, 0x19, 0x00 },                 /* reply #18.1 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x0c, 0x00, 0x00 }, {                   /* spell #19 */
        { 0x1e, 0x1d, 0x03, 0x24, 0x45, 0x46, 0x2d, 0x53, 0x31, 0x38, 0x2d, 0x35, 0x35, 0x6d, 0x6d, 0x20, 0x66, 0x2f, 0x33, 0x2e, 0x35, 0x2d, 0x35, 0x2e, 0x36, 0x20, 0x49, 0x53, 0x00, 0x00 },/* reply #19.1 */
        { 0x06, 0x04, 0x03, 0x25, 0x00 },                       /* reply #19.2 */
        { 0x06, 0x05, 0x01, 0x3d, 0x00, 0x00 },                 /* reply #19.3 */
        { 0x06, 0x05, 0x03, 0x37, 0x00, 0x00 },                 /* reply #19.4 */
        { 0x06, 0x05, 0x03, 0x0d, 0x00, 0x00 },                 /* reply #19.5 */
        { 0x06, 0x05, 0x03, 0x0c, 0x00, 0x00 },                 /* reply #19.6 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                   /* spell #20 */
        { 0x0a, 0x09, 0x03, 0x00, 0x50, 0x00, 0x00, 0x1b, 0x01, 0x00 },/* reply #20.1 */
        { 0x06, 0x05, 0x03, 0x04, 0x00, 0x00 },                 /* reply #20.2 */
        { 0x1a, 0x18, 0x03, 0x15, 0x01, 0x28, 0x53, 0x00, 0x30, 0x00, 0x12, 0x00, 0x37, 0x91, 0x75, 0x92, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 },/* reply #20.3 */
        { 0x24, 0x22, 0x03, 0x3c, 0x00, 0x00, 0x17, 0x3f, 0xbb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #20.4 */
        { 0x06, 0x05, 0x03, 0x17, 0x98, 0x00 },                 /* reply #20.5 */
        { 0x1a, 0x18, 0x03, 0x15, 0x01, 0x28, 0x53, 0x00, 0x30, 0x00, 0x12, 0x00, 0x37, 0x91, 0x75, 0x92, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 },/* reply #20.6 */
        { 0 } } }, {
    { 0x06, 0x05, 0x09, 0x11, 0x01, 0x00 }, {                   /* spell #21 */
        { 0 } } }, {
    { 0x12, 0x11, 0x09, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #22 */
        { 0 } } }, {
    { 0x08, 0x06, 0x09, 0x1f, 0x00, 0x00, 0x00 }, {             /* spell #23 */
        { 0 } } }, {
    { 0x06, 0x05, 0x01, 0x5a, 0x00, 0x00 }, {                   /* spell #24 */
        { 0 } } }, {
    { 0x06, 0x05, 0x01, 0x5a, 0x01, 0x00 }, {                   /* spell #25 */
        { 0 } } }, {
    { 0x26, 0x24, 0x09, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #26 */
        { 0 } } }, {
    { 0x0a, 0x08, 0x09, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00 }, { /* spell #27 */
        { 0 } } }, {
    { 0x08, 0x06, 0x03, 0x18, 0x00, 0x00, 0x00 }, {             /* spell #28 */
        { 0x06, 0x05, 0x01, 0x58, 0x00, 0x00 },                 /* reply #28.1 */
        { 0 } } }, {
    { 0x08, 0x06, 0x03, 0x1f, 0x00, 0x00, 0x00 }, {             /* spell #29 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x13, 0x00, 0x00 }, {                   /* spell #30 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x1e, 0x00, 0x00 }, {                   /* spell #31 */
        { 0 } } }, {
    { 0x08, 0x07, 0x01, 0x2a, 0x24, 0xdf, 0x00, 0x00 }, {       /* spell #32 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x3d, 0x00, 0x00 }, {                   /* spell #33 */
        { 0 } } }, {
    { 0x06, 0x05, 0x02, 0x0a, 0x01, 0x00 }, {                   /* spell #34 */
        { 0x06, 0x05, 0x06, 0x11, 0x01, 0x00 },                 /* reply #34.1, GUI_Control:84, bindReceiveSwitch(17, 1) */
        { 0x06, 0x05, 0x06, 0x12, 0x00, 0x00 },                 /* reply #34.2, GUI_Control:86, bindReceiveSwitch(18, 0) */
        { 0x06, 0x05, 0x06, 0x13, 0x00, 0x00 },                 /* reply #34.3, bindReceiveSwitch(19, 0) */
        { 0x06, 0x05, 0x06, 0x1c, 0x00, 0x00 },                 /* reply #34.4, bindReceiveSwitch(28, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #34.5, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x44, 0x43, 0x0a, 0x08, 0xff, 0x1f, 0x01, 0x00, 0x01, 0x03, 0x98, 0x0c, 0x00, 0x45, 0x01, 0x01, 0x53, 0x28, 0x53, 0x01, 0x01, 0x00, 0x00, 0x04, 0x01, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #34.6 */
        { 0x06, 0x05, 0x04, 0x0e, 0x01, 0x00 },                 /* reply #34.7 */
        { 0 } } }, {
    { 0x1a, 0x18, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #35 */
        { 0x1a, 0x18, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #35.1 */
        { 0x06, 0x05, 0x01, 0x53, 0x00, 0x00 },                 /* reply #35.2 */
        { 0x06, 0x05, 0x01, 0x58, 0x00, 0x00 },                 /* reply #35.3 */
        { 0x06, 0x05, 0x01, 0x59, 0x00, 0x00 },                 /* reply #35.4 */
        { 0 } } }, {
    { 0x1a, 0x18, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #36 */
        { 0x1a, 0x18, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #36.1 */
        { 0x06, 0x05, 0x01, 0x53, 0x00, 0x00 },                 /* reply #36.2 */
        { 0x06, 0x05, 0x01, 0x58, 0x00, 0x00 },                 /* reply #36.3 */
        { 0x06, 0x05, 0x01, 0x59, 0x00, 0x00 },                 /* reply #36.4 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                   /* spell #37 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                   /* spell #38 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x16, 0x06, 0x00 }, {                   /* spell #39 */
        { 0x06, 0x05, 0x03, 0x16, 0x00, 0x00 },                 /* reply #39.1 */
        { 0 } } }, {
    { 0x06, 0x05, 0x04, 0x0d, 0x01, 0x00 }, {                   /* spell #40 */
        { 0x06, 0x05, 0x04, 0x0d, 0x01, 0x00 },                 /* reply #40.1 */
        { 0 } } }, {
    { 0x06, 0x05, 0x08, 0x06, 0xff, 0x00 }, {                   /* spell #41 */
        { 0x06, 0x05, 0x08, 0x06, 0x00, 0x00 },                 /* reply #41.1 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                   /* spell #42 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                   /* spell #43 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                   /* spell #44 */
        { 0x06, 0x05, 0x03, 0x17, 0x9a, 0x00 },                 /* reply #44.1 */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #44.2, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x00, 0x01, 0x00 },                 /* reply #44.3, BGMT_MENU, GUI_Control:6, bindReceiveSwitch(0, 1) */
        { 0x06, 0x05, 0x04, 0x0d, 0x00, 0x00 },                 /* reply #44.4 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                   /* spell #45 */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #45.1, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x00, 0x01, 0x00 },                 /* reply #45.2, BGMT_MENU, GUI_Control:6, bindReceiveSwitch(0, 1) */
        { 0 } } }, {
    { 0x06, 0x05, 0x04, 0x00, 0x01, 0x00 }, {                   /* spell #46, NotifyGUIEvent(1) */
        { 0x06, 0x05, 0x06, 0x0a, 0x00, 0x00 },                 /* reply #46.1, BGMT_UNPRESS_ZOOMOUT_MAYBE, GUI_Control:17, bindReceiveSwitch(10, 0) */
        { 0x06, 0x05, 0x06, 0x09, 0x00, 0x00 },                 /* reply #46.2, BGMT_UNPRESS_ZOOMIN_MAYBE, GUI_Control:15, bindReceiveSwitch(9, 0) */
        { 0x06, 0x05, 0x04, 0x00, 0x01, 0x01 },                 /* reply #46.3 */
        { 0x0e, 0x0c, 0x0a, 0x08, 0x11, 0x00, 0x15, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 },/* reply #46.4 */
        { 0 } } }, {
    { 0x08, 0x06, 0x00, 0x00, 0x04, 0x00, 0x00 }, {             /* spell #47, Complete WaitID = 0x80020000 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x34, 0x00, 0x00 }, {                   /* spell #48 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                   /* spell #49 */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.1, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.2, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.3, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.4, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.5, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.6, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.7, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.8, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.9, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.10, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.11, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.12, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.13, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.14, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.15, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.16, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.17, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.18, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.19, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.20, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.21, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.22, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.23, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.24, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.25, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.26, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.27, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.28, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.29, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.30, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.31, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.32, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.33, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.34, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.35, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.36, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.37, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.38, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.39, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.40, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.41, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.42, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.43, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.44, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.45, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.46, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.47, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.48, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.49, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.50, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.51, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.52, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.53, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.54, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.55, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.56, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x00, 0x00 },                 /* reply #49.57, BGMT_UNPRESS_RIGHT, GUI_Control:36, bindReceiveSwitch(26, 0) */
        { 0x06, 0x05, 0x06, 0x26, 0x01, 0x00 },                 /* reply #49.58, GUI_Control:76, bindReceiveSwitch(38, 1) */
        { 0x06, 0x05, 0x06, 0x1a, 0x01, 0x00 },                 /* reply #49.59, BGMT_PRESS_RIGHT, GUI_Control:35, bindReceiveSwitch(26, 1) */
    { 0 } } }
};
