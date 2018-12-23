
static int button_codes_100D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2701,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x2001,
    [BGMT_UNPRESS_Q]                    = 0x0C00,   /* actually BGMT_UNPRESS_SET (GUI events are Q, PRESS_SET, UNPRESS_SET; unsure about MPU messages) */
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [GMT_GUICMD_PRESS_BUTTON_SOMETHING] = 0x2601,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_1100D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2101,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DISP]                   = 0x2501,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x0501,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DISP]                 = 0x2500,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_1200D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2101,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DISP]                   = 0x2501,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x2001,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DISP]                 = 0x2500,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_450D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_JUMP]                         = 0x0201,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PICSTYLE]                     = 0x1701,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_DIRECT_PRINT]           = 0x0501,
    [BGMT_UNPRESS_DIRECT_PRINT]         = 0x0500,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_500D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x0501,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_550D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2101,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x0501,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_40D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_JUMP]                         = 0x0201,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PICSTYLE]                     = 0x1701,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_JOY_CENTER]                   = 0x0B01,
    [BGMT_PRESS_DIRECT_PRINT]           = 0x0501,
    [BGMT_PRESS_DOWN]                   = 0x0B09,
    [BGMT_PRESS_DOWN_LEFT]              = 0x0B08,
    [BGMT_PRESS_DOWN_RIGHT]             = 0x0B07,
    [BGMT_PRESS_HALFSHUTTER]            = 0x0900,
    [BGMT_PRESS_LEFT]                   = 0x0B06,
    [BGMT_PRESS_RIGHT]                  = 0x0B05,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x0B02,
    [BGMT_PRESS_UP_LEFT]                = 0x0B04,
    [BGMT_PRESS_UP_RIGHT]               = 0x0B03,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_DIRECT_PRINT]         = 0x0500,
    [BGMT_UNPRESS_UDLR]                 = 0x0B00,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_50D[] = {
    [BGMT_FUNC]                         = 0x1601,
    [BGMT_INFO]                         = 0x0101,
    [BGMT_JOY_CENTER]                   = 0x0B01,
    [BGMT_LV]                           = 0x0501,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PICSTYLE]                     = 0x1701,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_DOWN]                   = 0x0B09,
    [BGMT_PRESS_DOWN_LEFT]              = 0x0B08,
    [BGMT_PRESS_DOWN_RIGHT]             = 0x0B07,
    [BGMT_PRESS_LEFT]                   = 0x0B06,
    [BGMT_PRESS_RIGHT]                  = 0x0B05,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x0B02,
    [BGMT_PRESS_UP_LEFT]                = 0x0B04,
    [BGMT_PRESS_UP_RIGHT]               = 0x0B03,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UDLR]                 = 0x0B00,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_5D2[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_JOY_CENTER]                   = 0x0B01,
    [BGMT_LV]                           = 0x0501,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PICSTYLE]                     = 0x1701,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_DOWN]                   = 0x0B09,
    [BGMT_PRESS_DOWN_LEFT]              = 0x0B08,
    [BGMT_PRESS_DOWN_RIGHT]             = 0x0B07,
    [BGMT_PRESS_LEFT]                   = 0x0B06,
    [BGMT_PRESS_RIGHT]                  = 0x0B05,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x0B02,
    [BGMT_PRESS_UP_LEFT]                = 0x0B04,
    [BGMT_PRESS_UP_RIGHT]               = 0x0B03,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UDLR]                 = 0x0B00,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_5D3[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_JOY_CENTER]                   = 0x0B01,
    [BGMT_LIGHT]                        = 0x2301,
    [BGMT_LV]                           = 0x2101,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PICSTYLE]                     = 0x0800,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_DOWN]                   = 0x0B09,
    [BGMT_PRESS_DOWN_LEFT]              = 0x0B08,
    [BGMT_PRESS_DOWN_RIGHT]             = 0x0B07,
    [BGMT_PRESS_LEFT]                   = 0x0B06,
    [BGMT_PRESS_RIGHT]                  = 0x0B05,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x0B02,
    [BGMT_PRESS_UP_LEFT]                = 0x0B04,
    [BGMT_PRESS_UP_RIGHT]               = 0x0B03,
    [BGMT_PRESS_MAGNIFY_BUTTON]         = 0x0801,
    [BGMT_SILENT_DOWN]                  = 0x2809,
    [BGMT_SILENT_LEFT]                  = 0x2806,
    [BGMT_SILENT_RIGHT]                 = 0x2805,
    [BGMT_SILENT_UP]                    = 0x2802,
    [BGMT_SILENT_UNPRESS]               = 0x2800,
    [BGMT_Q]                            = 0x2001,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_INFO]                 = 0x0100,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UDLR]                 = 0x0B00,
    [BGMT_UNPRESS_MAGNIFY_BUTTON]       = 0x0800,
  //[BGMT_UNPRESS_ZOOM_IN]              = 0x0900,   /* internal, sent by MPU when changing GUI modes */
  //[BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,   /* internal, sent by MPU when changing GUI modes */
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_PRESS_BUTTON_SOMETHING] = 0x2601,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_600D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2101,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DISP]                   = 0x2501,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x0501,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DISP]                 = 0x2500,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_60D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2101,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_DOWN]                   = 0x0B09,
    [BGMT_PRESS_DOWN_LEFT]              = 0x0B08,
    [BGMT_PRESS_DOWN_RIGHT]             = 0x0B07,
    [BGMT_PRESS_LEFT]                   = 0x0B06,
    [BGMT_PRESS_RIGHT]                  = 0x0B05,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x0B02,
    [BGMT_PRESS_UP_LEFT]                = 0x0B04,
    [BGMT_PRESS_UP_RIGHT]               = 0x0B03,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x2001,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNLOCK]                       = 0x0501,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UDLR]                 = 0x0B01,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_6D[] = {
    [BGMT_AFPAT_UNPRESS]                = 0x0900,
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LIGHT]                        = 0x2301,
    [BGMT_LV]                           = 0x2701,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_DOWN]                   = 0x0B09,
    [BGMT_PRESS_DOWN_RIGHT]             = 0x0B07,
    [BGMT_PRESS_LEFT]                   = 0x0B06,
    [BGMT_PRESS_RIGHT]                  = 0x0B05,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x0B02,
    [BGMT_PRESS_UP_LEFT]                = 0x0B04,
    [BGMT_PRESS_UP_RIGHT]               = 0x0B03,
    [BGMT_PRESS_MAGNIFY_BUTTON]         = 0x0801,
    [BGMT_Q]                            = 0x2001,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UDLR]                 = 0x0B01,
    [BGMT_UNPRESS_MAGNIFY_BUTTON]       = 0x0800,
  //[BGMT_UNPRESS_ZOOM_IN]              = 0x0900,   /* internal, sent by MPU when changing GUI modes */
  //[BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,   /* internal, sent by MPU when changing GUI modes */
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_PRESS_BUTTON_SOMETHING] = 0x2601,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_650D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2701,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x2001,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_PRESS_BUTTON_SOMETHING] = 0x2601,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_700D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2701,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x2001,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_PRESS_BUTTON_SOMETHING] = 0x2601,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_70D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LIGHT]                        = 0x2301,
    [BGMT_LV]                           = 0x2701,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_DOWN]                   = 0x0B09,
    [BGMT_PRESS_DOWN_RIGHT]             = 0x0B07,
    [BGMT_PRESS_LEFT]                   = 0x0B06,
    [BGMT_PRESS_RIGHT]                  = 0x0B05,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x0B02,
    [BGMT_PRESS_UP_LEFT]                = 0x0B04,
    [BGMT_PRESS_UP_RIGHT]               = 0x0B03,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x2001,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UDLR]                 = 0x0B01,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [GMT_GUICMD_PRESS_BUTTON_SOMETHING] = 0x2601,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_7D[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_JOY_CENTER]                   = 0x0B01,
    [BGMT_LV]                           = 0x2101,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PICSTYLE]                     = 0x1701,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_DOWN]                   = 0x0B09,
    [BGMT_PRESS_DOWN_LEFT]              = 0x0B08,
    [BGMT_PRESS_DOWN_RIGHT]             = 0x0B07,
    [BGMT_PRESS_LEFT]                   = 0x0B06,
    [BGMT_PRESS_RAW_JPEG]               = 0x0501,
    [BGMT_PRESS_RIGHT]                  = 0x0B05,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x0B02,
    [BGMT_PRESS_UP_LEFT]                = 0x0B04,
    [BGMT_PRESS_UP_RIGHT]               = 0x0B03,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x2001,
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_RAW_JPEG]             = 0x0500,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UDLR]                 = 0x0B00,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_DOWN]                   = 0x0E01,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [BGMT_WHEEL_UP]                     = 0x0EFF,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_EOSM[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2701,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_Q]                            = 0x2001,   /* same as 100D */
    [BGMT_UNPRESS_Q]                    = 0x0C00,   /* actually BGMT_UNPRESS_SET (GUI events are Q, PRESS_SET, UNPRESS_SET; unsure about MPU messages) */
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_PRESS_BUTTON_SOMETHING] = 0x2601,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [BGMT_END_OF_LIST]                  = 0x0000
};

static int button_codes_EOSM2[] = {
    [BGMT_INFO]                         = 0x0101,
    [BGMT_LV]                           = 0x2701,
    [BGMT_MENU]                         = 0x0001,
    [BGMT_PLAY]                         = 0x0301,
    [BGMT_PRESS_AV]                     = 0x1C01,
    [BGMT_PRESS_DOWN]                   = 0x1901,
    [BGMT_PRESS_LEFT]                   = 0x1B01,
    [BGMT_PRESS_RIGHT]                  = 0x1A01,
    [BGMT_PRESS_SET]                    = 0x0C01,
    [BGMT_PRESS_UP]                     = 0x1801,
    [BGMT_PRESS_ZOOM_IN]                = 0x0901,
    [BGMT_PRESS_ZOOM_OUT]               = 0x0A01,
    [BGMT_Q]                            = 0x2001,
    [BGMT_UNPRESS_Q]                    = 0x0C00,   /* actually BGMT_UNPRESS_SET (GUI events are Q, PRESS_SET, UNPRESS_SET; unsure about MPU messages) */
    [BGMT_TRASH]                        = 0x0401,
    [BGMT_UNPRESS_AV]                   = 0x1C00,
    [BGMT_UNPRESS_DOWN]                 = 0x1900,
    [BGMT_UNPRESS_LEFT]                 = 0x1B00,
    [BGMT_UNPRESS_RIGHT]                = 0x1A00,
    [BGMT_UNPRESS_SET]                  = 0x0C00,
    [BGMT_UNPRESS_UP]                   = 0x1800,
    [BGMT_UNPRESS_ZOOM_IN]              = 0x0900,
    [BGMT_UNPRESS_ZOOM_OUT]             = 0x0A00,
    [BGMT_WHEEL_LEFT]                   = 0x0DFF,
    [BGMT_WHEEL_RIGHT]                  = 0x0D01,
    [GMT_GUICMD_OPEN_BATT_COVER]        = 0x1301,
    [GMT_GUICMD_OPEN_SLOT_COVER]        = 0x1201,
    [GMT_GUICMD_START_AS_CHECK]         = 0x1100,
    [GMT_GUICMD_PRESS_BUTTON_SOMETHING] = 0x2601,
    [BGMT_END_OF_LIST]                  = 0x0000
};
