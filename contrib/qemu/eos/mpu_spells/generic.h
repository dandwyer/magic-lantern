 /**
 * Minimal generic spell set based on 60D (deleted everything that did not prevent booting)
 * Boots many other models (without card support, but menu navigation works).
 * Tested on:
 * 5D2 5D3 6D 50D 60D 70D 
 * 450D 500D 550D 600D 650D 700D
 * 100D 1000D 1100D 1200D EOSM2
 * Not working: EOSM
 */

static struct mpu_init_spell mpu_init_spells_generic[] = {
    { { 0x06, 0x04, 0x02, 0x00, 0x00 }, .description = "Init", .out_spells = { /* spell #1 */
        { 0x2c, 0x2a, 0x02, 0x00, 0x03, 0x03, 0x03, 0x04, 0x03, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x14, 0x50, 0x00, 0x00, 0x00, 0x00, 0x81, 0x06, 0x00, 0x00, 0x04, 0x06, 0x00, 0x00, 0x04, 0x06, 0x00, 0x00, 0x04, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x4b, 0x01 },/* reply #1.17, Init */
        { 0 } } },

    #include "NotifyGUIEvent.h"
    #include "UILock.h"
    #include "CardFormat.h"
    #include "GPS.h"
    #include "Shutdown.h"
};
