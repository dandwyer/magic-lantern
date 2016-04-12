#include <module.h>
#include <dryos.h>
#include <property.h>
#include <bmp.h>
#include <menu.h>
#include <console.h>
#include <powersave.h>

#define CF_REG_B(x) (*(volatile uint8_t *)     (0xC0620000 | x))
#define CF_REG_W(x) (*(volatile uint16_t *)    (0xC0620000 | x))
#define CF_REG_D(x) (*(volatile unsigned int *)(0xC0620000 | x))

/* compact flash spec registers */
#define CF_REG_DATA_IN       0x2000
#define CF_REG_FEATURE       0x2001
#define CF_REG_SEC_COUNT     0x2002
#define CF_REG_SEC_NUM       0x2003
#define CF_REG_CYL_LO        0x2004
#define CF_REG_CYL_HI        0x2005
#define CF_REG_CDH           0x2006
#define CF_REG_COMMAND       0x2007

/* these registers change their meaning when read */
#define CF_REG_ERROR         CF_REG_FEATURE
#define CF_REG_STATUS        CF_REG_COMMAND

/* bit 1: set to zero to disable card INT */
#define CF_REG_IREQ          0x200E

/* set to zero to disable controller interrupts */
#define CF_REG_CTRL_INT_A    0x8040
#define CF_REG_CTRL_INT_B    0x8044

/* translate a string from uint16_t format */
uint8_t *cf_acc_get_string(uint8_t *buf, uint16_t *data, int chars)
{
    for(int pos = 0; pos < chars; pos++)
    {
        uint8_t character = (data[pos/2] >> (8*(1-(pos&1)))) & 0xFF;
        buf[pos] = character;
    }
    buf[chars] = 0;
    
    return buf;
}

/* read a raw sector in LBA mode */
uint32_t cf_acc_read_sector(uint32_t sector, uint8_t *data)
{
    /* disable card interrupt. not sure if needed. */
    uint8_t control = CF_REG_B(CF_REG_IREQ);
    CF_REG_B(CF_REG_IREQ) = (control & ~2);
    
    /* disable controller interrupts for this command */
    CF_REG_D(CF_REG_CTRL_INT_B) = 0;
    CF_REG_D(CF_REG_CTRL_INT_A) = 0;
    
    /* issue READ_SECTOR command */
    CF_REG_B(CF_REG_CDH) = 0xE0 | ((sector >> 24) & 0x0F);
    CF_REG_B(CF_REG_CYL_HI) = (sector >> 16) & 0xFF;
    CF_REG_B(CF_REG_CYL_LO) = (sector >> 8) & 0xFF;
    CF_REG_B(CF_REG_SEC_NUM) = sector & 0xFF;
    CF_REG_B(CF_REG_SEC_COUNT) = 1;
    CF_REG_B(CF_REG_COMMAND) = 0x20;
    
    /* wait until card is ready again */
    while((CF_REG_B(CF_REG_STATUS) ^ 0x40) & 0xC0)
    {
        msleep(20);
    }
    
    uint16_t *word_buf = (uint16_t *)data;
    
    /* read received data */
    for(int word_num = 0; word_num < 256; word_num++)
    {
        word_buf[word_num] = CF_REG_W(CF_REG_DATA_IN);
    }
    
    /* reenable card interrupts */
    CF_REG_B(CF_REG_IREQ) = control;
    
    return 0;
}

/* write a raw sector in LBA mode */
uint32_t cf_acc_write_sector(uint32_t sector, uint8_t *data)
{
    /* disable card interrupt. not sure if needed. */
    uint8_t control = CF_REG_B(CF_REG_IREQ);
    CF_REG_B(CF_REG_IREQ) = (control & ~2);
    
    /* disable controller interrupts for this command */
    CF_REG_D(CF_REG_CTRL_INT_B) = 0;
    CF_REG_D(CF_REG_CTRL_INT_A) = 0;
    
    /* issue WRITE_SECTOR command */
    CF_REG_B(CF_REG_CDH) = 0xE0 | ((sector >> 24) & 0x0F);
    CF_REG_B(CF_REG_CYL_HI) = (sector >> 16) & 0xFF;
    CF_REG_B(CF_REG_CYL_LO) = (sector >> 8) & 0xFF;
    CF_REG_B(CF_REG_SEC_NUM) = sector & 0xFF;
    CF_REG_B(CF_REG_SEC_COUNT) = 1;
    CF_REG_B(CF_REG_COMMAND) = 0x30;
    
    /* wait until card is ready */
    while(CF_REG_B(CF_REG_COMMAND) != 0x58)
    {
        msleep(20);
    }
    
    /* write data */
    uint16_t *word_buf = (uint16_t *)data;
    
    for(int word_num = 0; word_num < 256; word_num++)
    {
        CF_REG_W(CF_REG_DATA_IN) = word_buf[word_num];
    }
    
    /* wait until card is ready again */
    while((CF_REG_B(CF_REG_STATUS) ^ 0x40) & 0xC0)
    {
        msleep(20);
    }
    
    /* reenable card interrupts */
    CF_REG_B(CF_REG_IREQ) = control;
    
    return 0;
}

void cf_acc_read_task()
{
    int y = 1;
    uint8_t str_buf[64];
    uint16_t data_buf[256];
    msleep(1000);
    
    canon_gui_disable_front_buffer();
    clrscr();
    
    /* disable card interrupt. not sure if needed. */
    uint8_t control = CF_REG_B(CF_REG_IREQ);
    CF_REG_B(CF_REG_IREQ) = (control & ~2);
    
    /* disable controller interrupts for this command */
    CF_REG_D(CF_REG_CTRL_INT_B) = 0;
    CF_REG_D(CF_REG_CTRL_INT_A) = 0;
    
    /* issue IDENTIFY_DRIVE command */
    CF_REG_B(CF_REG_CDH) = 0;
    CF_REG_B(CF_REG_COMMAND) = 0xEC;
    
    /* wait until card is ready again */
    while((CF_REG_B(CF_REG_STATUS) ^ 0x40) & 0xC0)
    {
        msleep(20);
    }
    
    /* read received data */
    for(int word_num = 0; word_num < 256; word_num++)
    {
        data_buf[word_num] = CF_REG_W(CF_REG_DATA_IN);
    }
    
    /* reenable card interrupts */
    CF_REG_B(CF_REG_IREQ) = control;
    
    bmp_printf(FONT_MED, 0, font_med.height * y++, "Model:     %s", cf_acc_get_string(str_buf, &data_buf[27], 40));
    bmp_printf(FONT_MED, 0, font_med.height * y++, "Firmware:  %s", cf_acc_get_string(str_buf, &data_buf[23], 8));
    bmp_printf(FONT_MED, 0, font_med.height * y++, "Serial:    %s", cf_acc_get_string(str_buf, &data_buf[10], 20));
    bmp_printf(FONT_MED, 0, font_med.height * y++, "C/H/S:     %d/%d/%d", data_buf[1], data_buf[3], data_buf[6]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "Sectors:   0x%04X%04X", data_buf[7], data_buf[8]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "SectLBA:   0x%04X%04X", data_buf[61], data_buf[60]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "ECCBytes:  0x%04X  SectWrMax: %d", data_buf[22], data_buf[47]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "Caps:      0x%04X  FeatsSup:  0x%04X%04X%04X", data_buf[49], data_buf[82], data_buf[83], data_buf[84]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "MWTrans:   0x%04X  FeatsEn:   0x%04X%04X%04X", data_buf[63], data_buf[85], data_buf[86], data_buf[87]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "MinMW:     0x%04X  MaxMW:     0x%04X", data_buf[65], data_buf[66]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "UDMA:      0x%04X  AdvPIO:    0x%04X", data_buf[88], data_buf[64]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "IDECap:    0x%04X  PCMCIACap: 0x%04X", data_buf[163], data_buf[164]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "Security:  0x%04X  VendorDat: 0x%04X%04X", data_buf[128], data_buf[158], data_buf[159]);
    bmp_printf(FONT_MED, 0, font_med.height * y++, "Power:     0x%04X  PowerReq:  0x%04X", data_buf[91], data_buf[160]);
    
    call("dispcheck");
    msleep(3000);
    canon_gui_enable_front_buffer(0);
}

int do_drive_cmd(int fd, unsigned char *args, unsigned int timeout_secs)
{
    /*
     * Inputs:
     * from hdparm:
     *   args[0]: command in; status out.
     *   args[1]: lbal for SMART, nsect for all others; error out
     *   args[2]: feat in; nsect out.
     *   args[3]: data-count (512 multiple) for all cmds.
     * 
     * from ioctl doc:
     * Commands other than WIN_SMART
     *   args[0]	COMMAND
     *   args[1]	NSECTOR
     *   args[2]	FEATURE
     *   args[3]	NSECTOR
     * 
     * for Identify Drive: [EC 0 0 1]
     * 
     * Outputs:
     *   from ioctl doc:
     *   args[] buffer is filled with register values followed by any 
     *   data returned by the disk.
     *   args[0]	status
     *   args[1]	error
     *   args[2]	NSECTOR
     *   args[3]	undefined
     *   args[4+]	NSECTOR * 512 bytes of data returned by the command.
     */

    /* disable card interrupt. not sure if needed. */
    uint8_t control = CF_REG_B(CF_REG_IREQ);
    CF_REG_B(CF_REG_IREQ) = (control & ~2);
    
    /* disable controller interrupts for this command */
    CF_REG_D(CF_REG_CTRL_INT_B) = 0;
    CF_REG_D(CF_REG_CTRL_INT_A) = 0;
    
    /* issue the requested command */
    CF_REG_B(CF_REG_CDH) = 0;
    CF_REG_B(CF_REG_COMMAND) = args[0];
    CF_REG_B(CF_REG_SEC_COUNT) = args[3];
    
    /* wait until card is ready again */
    unsigned char status;
    while(((status = CF_REG_B(CF_REG_STATUS)) ^ 0x40) & 0xC0)
    {
        msleep(20);
    }
    
    /* output flags */
    args[0] = status;
    args[1] = CF_REG_B(CF_REG_ERROR);
    args[2] = args[3];
    
    /* read received data */
    for(int word_num = 0; word_num < 256 * args[3]; word_num++)
    {
        uint16_t word = CF_REG_W(CF_REG_DATA_IN);
        args[4 + word_num*2]   = word & 0xFF;
        args[4 + word_num*2+1] = word >> 8;
    }
    
    /* reenable card interrupts */
    CF_REG_B(CF_REG_IREQ) = control;
    
    return 0;
}

extern void hdparm_identify(int,int);

static void hdparm_identify_task()
{
    console_show();
    msleep(1000);
    hdparm_identify(1, 0);
}

static struct menu_entry cf_acc_menu[] =
{
    {
        .name = "Read CF details (MAY CAUSE ERR)",
        .select = run_in_separate_task,
        .priv = cf_acc_read_task,
    },
    {
        .name = "hdparm identify",
        .select = run_in_separate_task,
        .priv = hdparm_identify_task,
    },
};

unsigned int cf_acc_init()
{
    menu_add("Debug", cf_acc_menu, COUNT(cf_acc_menu));
    return 0;
}

unsigned int cf_acc_deinit()
{
    menu_remove("Debug", cf_acc_menu, COUNT(cf_acc_menu));
    return 0;
}


MODULE_INFO_START()
    MODULE_INIT(cf_acc_init)
    MODULE_DEINIT(cf_acc_deinit)
MODULE_INFO_END()

