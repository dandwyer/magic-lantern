/**
 * 550D (MENU pressed at startup)
 */
struct mpu_init_spell mpu_init_spells_550D[] = { {
    { 0x06, 0x04, 0x02, 0x00, 0x00 }, {                         /* spell #1 */
        { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 },                 /* reply #1.1 */
        { 0x08, 0x07, 0x01, 0x33, 0x00, 0x00, 0x00, 0x00 },     /* reply #1.2 */
        { 0x12, 0x11, 0x02, 0x04, 0x0c, 0x00, 0x01, 0x02, 0x00, 0x03, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00 },/* reply #1.3 */
        { 0x06, 0x05, 0x01, 0x20, 0x00, 0x00 },                 /* reply #1.4 */
        { 0x06, 0x05, 0x01, 0x21, 0x01, 0x00 },                 /* reply #1.5 */
        { 0x06, 0x05, 0x01, 0x22, 0x00, 0x00 },                 /* reply #1.6 */
        { 0x06, 0x05, 0x03, 0x0c, 0x00, 0x00 },                 /* reply #1.7 */
        { 0x06, 0x05, 0x03, 0x0d, 0x01, 0x00 },                 /* reply #1.8 */
        { 0x06, 0x05, 0x03, 0x0e, 0x01, 0x00 },                 /* reply #1.9 */
        { 0x08, 0x06, 0x01, 0x23, 0x00, 0x01, 0x00 },           /* reply #1.10 */
        { 0x08, 0x06, 0x01, 0x24, 0x00, 0x00, 0x00 },           /* reply #1.11 */
        { 0x08, 0x06, 0x01, 0x25, 0x00, 0x00, 0x00 },           /* reply #1.12 */
        { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 },                 /* reply #1.13 */
        { 0x06, 0x05, 0x01, 0x37, 0x00, 0x00 },                 /* reply #1.14 */
        { 0x06, 0x05, 0x01, 0x2c, 0x02, 0x00 },                 /* reply #1.15 */
        { 0x06, 0x05, 0x03, 0x20, 0x04, 0x00 },                 /* reply #1.16 */
        { 0x06, 0x05, 0x01, 0x42, 0x01, 0x00 },                 /* reply #1.17 */
        { 0x06, 0x05, 0x01, 0x43, 0x00, 0x00 },                 /* reply #1.18 */
        { 0x06, 0x05, 0x01, 0x44, 0x00, 0x00 },                 /* reply #1.19 */
        { 0x06, 0x05, 0x01, 0x46, 0x00, 0x00 },                 /* reply #1.20 */
        { 0x06, 0x05, 0x01, 0x48, 0x01, 0x00 },                 /* reply #1.21 */
        { 0x06, 0x05, 0x01, 0x49, 0x01, 0x00 },                 /* reply #1.22 */
        { 0x06, 0x05, 0x01, 0x4b, 0x01, 0x00 },                 /* reply #1.23 */
        { 0x16, 0x14, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0c, 0x00 },/* reply #1.24 */
        { 0x06, 0x05, 0x01, 0x50, 0x03, 0x00 },                 /* reply #1.25 */
        { 0x08, 0x06, 0x01, 0x51, 0x68, 0x50, 0x00 },           /* reply #1.26 */
        { 0x06, 0x05, 0x01, 0x52, 0x00, 0x00 },                 /* reply #1.27 */
        { 0x06, 0x05, 0x01, 0x53, 0x01, 0x00 },                 /* reply #1.28 */
        { 0x08, 0x06, 0x01, 0x47, 0x0a, 0x02, 0x00 },           /* reply #1.29 */
        { 0x06, 0x05, 0x03, 0x37, 0x00, 0x00 },                 /* reply #1.30 */
        { 0x2c, 0x2a, 0x02, 0x00, 0x03, 0x03, 0x03, 0x00, 0x03, 0x00, 0x00, 0x70, 0x01, 0x00, 0x09, 0x13, 0x88, 0x00, 0x00, 0x00, 0x00, 0x81, 0x06, 0x00, 0x00, 0x04, 0x06, 0x00, 0x00, 0x04, 0x06, 0x00, 0x00, 0x04, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x45, 0x55, 0xaa },/* reply #1.31 */
        { 0x06, 0x05, 0x03, 0x04, 0x00, 0x00 },                 /* reply #1.32 */
        { 0x06, 0x05, 0x03, 0x05, 0x01, 0x00 },                 /* reply #1.33 */
        { 0x1e, 0x1c, 0x03, 0x30, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x6e, 0xd7, 0x00, 0x1d, 0x00, 0x1d, 0x00, 0x1d, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.34 */
        { 0x0e, 0x0c, 0x03, 0x2e, 0x00, 0x00, 0xde, 0xdb, 0x00, 0x01, 0x39, 0xef, 0x00 },/* reply #1.35 */
        { 0x0a, 0x08, 0x03, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #1.36 */
        { 0 } } }, {
    { 0x08, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00 }, {             /* spell #2, Complete WaitID = 0x80000001 */
        { 0x06, 0x05, 0x01, 0x38, 0x00, 0x00 },                 /* reply #2.1 */
        { 0x06, 0x05, 0x01, 0x39, 0x00, 0x00 },                 /* reply #2.2 */
        { 0x0c, 0x0b, 0x01, 0x0a, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #2.3 */
        { 0x06, 0x05, 0x03, 0x23, 0x01, 0x00 },                 /* reply #2.4 */
        { 0x06, 0x05, 0x03, 0x24, 0x00, 0x00 },                 /* reply #2.5 */
        { 0x06, 0x04, 0x03, 0x25, 0x00 },                       /* reply #2.6 */
        { 0x08, 0x06, 0x01, 0x45, 0x00, 0x10, 0x00 },           /* reply #2.7 */
        { 0x06, 0x05, 0x01, 0x09, 0x00, 0x00 },                 /* reply #2.8 */
        { 0x06, 0x05, 0x01, 0x0d, 0x09, 0x00 },                 /* reply #2.9 */
        { 0x06, 0x05, 0x01, 0x3e, 0x00, 0x00 },                 /* reply #2.10 */
        { 0x06, 0x05, 0x01, 0x3f, 0x00, 0x00 },                 /* reply #2.11 */
        { 0x06, 0x05, 0x01, 0x40, 0x00, 0x00 },                 /* reply #2.12 */
        { 0x06, 0x05, 0x01, 0x41, 0x00, 0x00 },                 /* reply #2.13 */
        { 0 } } }, {
    { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00 }, { /* spell #3 */
        { 0 } } }, {
    { 0x06, 0x04, 0x03, 0x10, 0x00 }, {                         /* spell #4 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x07, 0xff, 0x00 }, {                   /* spell #5 */
        { 0 } } }, {
    { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 }, {                   /* spell #6 */
        { 0x06, 0x05, 0x01, 0x2e, 0x01, 0x00 },                 /* reply #6.1 */
        { 0 } } }, {
    { 0x0a, 0x08, 0x03, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00 }, { /* spell #7 */
        { 0 } } }, {
    { 0x06, 0x05, 0x04, 0x0e, 0x01, 0x00 }, {                   /* spell #8 */
        { 0 } } }, {
    { 0x08, 0x06, 0x01, 0x24, 0x00, 0x01, 0x00 }, {             /* spell #9 */
        { 0x08, 0x06, 0x01, 0x24, 0x00, 0x01, 0x00 },           /* reply #9.1 */
        { 0 } } }, {
    { 0x08, 0x06, 0x01, 0x27, 0x00, 0x65, 0x00 }, {             /* spell #10 */
        { 0 } } }, {
    { 0x08, 0x07, 0x01, 0x2a, 0x26, 0xf6, 0x00, 0x00 }, {       /* spell #11 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x07, 0x06, 0x00 }, {                   /* spell #12 */
        { 0 } } }, {
    { 0x0a, 0x08, 0x03, 0x06, 0x00, 0x00, 0x01, 0x01, 0x00 }, { /* spell #13 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x11, 0x01, 0x00 }, {                   /* spell #14 */
        { 0 } } }, {
    { 0x06, 0x05, 0x02, 0x0a, 0x00, 0x00 }, {                   /* spell #15 */
        { 0x06, 0x05, 0x06, 0x13, 0x00, 0x00 },                 /* reply #15.1 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x0d, 0x00, 0x00 }, {                   /* spell #16 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x0c, 0x00, 0x00 }, {                   /* spell #17 */
        { 0x06, 0x05, 0x03, 0x37, 0x00, 0x00 },                 /* reply #17.1 */
        { 0x0a, 0x08, 0x03, 0x00, 0x54, 0x00, 0x00, 0x01, 0x00 },/* reply #17.2 */
        { 0x14, 0x12, 0x03, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #17.3 */
        { 0x06, 0x05, 0x03, 0x17, 0x9b, 0x00 },                 /* reply #17.4 */
        { 0x06, 0x05, 0x03, 0x38, 0xa0, 0x00 },                 /* reply #17.5 */
        { 0x06, 0x05, 0x03, 0x0d, 0x00, 0x00 },                 /* reply #17.6 */
        { 0x06, 0x05, 0x03, 0x0c, 0x00, 0x00 },                 /* reply #17.7 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                   /* spell #18 */
        { 0 } } }, {
    { 0x06, 0x05, 0x09, 0x11, 0x01, 0x00 }, {                   /* spell #19 */
        { 0 } } }, {
    { 0x12, 0x11, 0x09, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #20 */
        { 0 } } }, {
    { 0x26, 0x24, 0x09, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, {/* spell #21 */
        { 0 } } }, {
    { 0x0a, 0x08, 0x09, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00 }, { /* spell #22 */
        { 0 } } }, {
    { 0x08, 0x06, 0x03, 0x18, 0x00, 0x00, 0x00 }, {             /* spell #23 */
        { 0 } } }, {
    { 0x08, 0x06, 0x03, 0x1f, 0x00, 0x00, 0x00 }, {             /* spell #24 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x13, 0x00, 0x00 }, {                   /* spell #25 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x1e, 0x00, 0x00 }, {                   /* spell #26 */
        { 0 } } }, {
    { 0x08, 0x07, 0x01, 0x2a, 0x26, 0xf6, 0x00, 0x00 }, {       /* spell #27 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x3d, 0x00, 0x00 }, {                   /* spell #28 */
        { 0 } } }, {
    { 0x16, 0x14, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0c, 0x00 }, {/* spell #29 */
        { 0x16, 0x14, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0c, 0x00 },/* reply #29.1 */
        { 0 } } }, {
    { 0x16, 0x14, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0c, 0x00 }, {/* spell #30 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                   /* spell #31 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x01, 0x00 }, {                   /* spell #32 */
        { 0 } } }, {
    { 0x06, 0x05, 0x02, 0x0a, 0x01, 0x00 }, {                   /* spell #33 */
        { 0x16, 0x14, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0c, 0x00 },/* reply #33.1 */
        { 0x16, 0x14, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0c, 0x00 },/* reply #33.2 */
        { 0x16, 0x14, 0x01, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x0c, 0x00 },/* reply #33.3 */
        { 0x42, 0x41, 0x0a, 0x08, 0xff, 0x1f, 0x01, 0x00, 0x01, 0x03, 0x98, 0x10, 0x00, 0x45, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x70, 0x04, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #33.4 */
        { 0x06, 0x05, 0x06, 0x11, 0x01, 0x00 },                 /* reply #33.5 */
        { 0x06, 0x05, 0x06, 0x12, 0x00, 0x00 },                 /* reply #33.6 */
        { 0x06, 0x05, 0x06, 0x13, 0x00, 0x00 },                 /* reply #33.7 */
        { 0x06, 0x05, 0x06, 0x1c, 0x00, 0x00 },                 /* reply #33.8 */
        { 0x06, 0x05, 0x03, 0x38, 0xa0, 0x00 },                 /* reply #33.9 */
        { 0x06, 0x05, 0x06, 0x01, 0x01, 0x00 },                 /* reply #33.10 */
        { 0 } } }, {
    { 0x06, 0x05, 0x04, 0x0e, 0x01, 0x00 }, {                   /* spell #34 */
        { 0x42, 0x41, 0x0a, 0x08, 0xff, 0x1f, 0x01, 0x00, 0x01, 0x03, 0x98, 0x10, 0x00, 0x45, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x70, 0x04, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #34.1 */
        { 0x06, 0x05, 0x04, 0x0e, 0x01, 0x00 },                 /* reply #34.2 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                   /* spell #35 */
        { 0x06, 0x05, 0x06, 0x00, 0x01, 0x00 },                 /* reply #35.1 */
        { 0 } } }, {
    { 0x06, 0x05, 0x04, 0x00, 0x01, 0x00 }, {                   /* spell #36 */
        { 0x20, 0x1e, 0x0a, 0x08, 0x57, 0x00, 0x0f, 0x00, 0x01, 0x00, 0x98, 0x10, 0x00, 0x45, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },/* reply #36.1 */
        { 0x0e, 0x0c, 0x0a, 0x08, 0x09, 0x00, 0x15, 0x00, 0x01, 0x00, 0x00, 0x70, 0x00 },/* reply #36.2 */
        { 0x06, 0x05, 0x04, 0x00, 0x01, 0xaa },                 /* reply #36.3 */
        { 0 } } }, {
    { 0x08, 0x06, 0x00, 0x00, 0x04, 0x00, 0x00 }, {             /* spell #37, Complete WaitID = 0x80020000 */
        { 0 } } }, {
    { 0x06, 0x05, 0x03, 0x19, 0x00, 0x00 }, {                   /* spell #38 */
        { 0x06, 0x05, 0x03, 0x38, 0x9f, 0x00 },                 /* reply #38.1 */
        { 0x06, 0x05, 0x01, 0x52, 0x00, 0x00 },                 /* reply #38.2 */
    { 0 } } }
};
