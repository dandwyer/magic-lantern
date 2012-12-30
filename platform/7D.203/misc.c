// misc functions specific to 7D.203

#include <dryos.h>
#include <property.h>
#include <bmp.h>
#include <config.h>
#include <consts.h>
#include <lens.h>
#ifdef STROBO_READY_AND_WE_CAN_USE_IT
#include <strobo.h>
#endif
#include <version.h>

void display_shooting_info() // called from debug task
{
	if (lv) return;

	uint32_t fnt;
	int bg;
	int col_bg;
	int col_field;

    col_bg = bmp_getpixel(1,1);
    col_field = bmp_getpixel(615,455);
    
#ifdef DISPLAY_HEADER_FOOTER_INFO
    extern int header_left_info;
    extern int header_right_info;
    extern int footer_left_info;
    extern int footer_right_info;
    char adate[11];
    char info[63];

    bmp_fill(col_bg,28,3,694,21);
    bmp_fill(col_bg,28,459,694,21);

    if (header_left_info==3 || header_right_info==3 || footer_left_info==3 || footer_right_info==3) 
    {
		struct tm now;
		LoadCalendarFromRTC( &now );
// need to find the date format settings and use it here
//		snprintf(adate, sizeof(adate), "%2d.%2d.%4d.", (now.tm_mon+1),now.tm_mday,(now.tm_year+1900));
//		snprintf(adate, sizeof(adate), "%2d.%2d.%4d.", now.tm_mday,(now.tm_mon+1),(now.tm_year+1900));
		snprintf(adate, sizeof(adate), "%4d.%2d.%2d.", (now.tm_year+1900),(now.tm_mon+1),now.tm_mday);
	}
    
    fnt = FONT(FONT_MED, COLOR_FG_NONLV, col_bg); 
    if (header_left_info>0) 
		bmp_printf(fnt, 28, 3, (
			header_left_info==1 ? artist_name:
			header_left_info==2 ? copyright_info:
			header_left_info==3 ? adate:
			header_left_info==4 ? lens_info.name:
			header_left_info==5 ? build_version: 
			"")
		);
    if (footer_left_info>0) 
		bmp_printf(fnt, 28, 459, ( 
			footer_left_info==1 ? artist_name:
			footer_left_info==2 ? copyright_info:
			footer_left_info==3 ? adate:
			footer_left_info==4 ? lens_info.name:
			footer_left_info==5 ? build_version: 
			"") 
	);
    if (header_right_info>0) 
    {
    	snprintf(info, sizeof(info), "%s", (
			header_right_info==1 ? artist_name:
			header_right_info==2 ? copyright_info:
			header_right_info==3 ? adate:
			header_right_info==4 ? lens_info.name:
			header_right_info==5 ? build_version: 
			""));
		bmp_printf(fnt, 693-strlen(info) * font_med.width, 3, info);
	}
    
    if (footer_right_info>0) {
	    snprintf(info, sizeof(info), "%s", (
			footer_right_info==1 ? artist_name:
			footer_right_info==2 ? copyright_info:
			footer_right_info==3 ? adate:
			footer_right_info==4 ? lens_info.name:
			footer_right_info==5 ? build_version: 
			""));
		bmp_printf(fnt, 693-strlen(info) * font_med.width, 459, info);
	}
#endif

#ifdef STROBO_READY_AND_WE_CAN_USE_IT
	if (flash_info.mode==STROBO_FLASH_MODE_MANUAL)
	{
		uint32_t fntl = FONT(FONT_LARGE, COLOR_YELLOW, col_field);
		fnt = FONT(FONT_SMALL, COLOR_CYAN, col_field);
		bmp_printf(fnt, 488, 188, "A");
		bmp_printf(fntl, 498, 185, "%3d", 1 << flash_info.group_a_output);
		bmp_printf(fnt, 556, 188, "B");
		bmp_printf(fntl, 564, 185, "%3d", 1 << flash_info.group_b_output );
		bmp_printf(fnt, 624, 188, "C");
		bmp_printf(fntl, 632, 185, "%3d", 1 << flash_info.group_c_output);
		bmp_fill(bmp_getpixel(1,1),486,212,212,6);
	}
	//~ bmp_printf(fnt, 400, 450, "Flash:%s",
		//~ strobo_firing == 0 ? " ON" :
		//~ strobo_firing == 1 ? "OFF" : "Auto"
		//~ strobo_firing < 2 && flash_and_no_flash ? "/T" : "  "
		//~ );
#endif
    
    
	if (lens_info.raw_iso == 0) // ISO: AUTO
 	{
        fnt = FONT(FONT_MED, COLOR_YELLOW, col_field);
        bmp_printf(fnt, 455, 92, "[%d-%d]", MAX((get_htp() ? 200 : 100), raw2iso(auto_iso_range >> 8)), raw2iso((auto_iso_range & 0xFF)));
        bmp_fill(bmp_getpixel(1,1),455,110,120,2);
	}

	if (lens_info.wb_mode == WB_KELVIN)
	{
        fnt = FONT(FONT_MED, COLOR_YELLOW, col_field);
		bmp_printf(fnt, 393, 276, "%5d", lens_info.kelvin);
        bmp_fill(bmp_getpixel(1,1),377,294,100,3);
	}

	if (lens_info.wbs_gm || lens_info.wbs_ba)
	{
		fnt = FONT(FONT_LARGE, COLOR_YELLOW, col_field);
        bmp_fill(col_field,166,424,94,28);

		int ba = lens_info.wbs_ba;
		if (ba) bmp_printf(fnt, 177 + 2 * font_large.width, 426, "%s%d", ba > 0 ? "A" : "B", ABS(ba));
		else    bmp_printf(fnt, 177 + 2 * font_large.width, 426, "  ");

		int gm = lens_info.wbs_gm;
		if (gm) bmp_printf(fnt, 177, 426, "%s%d", gm > 0 ? "G" : "M", ABS(gm));
		else    bmp_printf(fnt, 177, 426, "  ");
	}

	//iso_refresh_display(); //what is it for ??? (sometimes it writes the same iso value plus a smaller ISO icon)

	hdr_display_status(fnt);

    int batlev = GetBatteryLevel();

    if (batlev >= 10) // if battery level<10 and the icon is flashing we don't redraw our battery 
    {
		uint batcol,batfil;
		bmp_fill(col_field,296,404,96,32); // clear the Canon battery icon
        
		if (batlev <= DISPLAY_BATTERY_LEVEL_2)
        {
            batcol = COLOR_RED;
        }
        else
        {
            batcol = COLOR_WHITE;
        }
        
		bmp_fill(batcol,DISPLAY_BATTERY_POS_X+10,DISPLAY_BATTERY_POS_Y,84,32); // draw the new battery icon
		bmp_fill(batcol,DISPLAY_BATTERY_POS_X,DISPLAY_BATTERY_POS_Y+8,12,16);
        
		if (batlev <= DISPLAY_BATTERY_LEVEL_1)
        {
            batcol = COLOR_YELLOW;
        }
		else if (batlev <= DISPLAY_BATTERY_LEVEL_2)
        {
            batcol = COLOR_RED;
        }
        else
        {
            batcol = COLOR_GREEN2;
        }
        
		bmp_fill(col_field,DISPLAY_BATTERY_POS_X+14,DISPLAY_BATTERY_POS_Y+4,76,24);
		batfil = batlev*68/100;
		bmp_fill(batcol,DISPLAY_BATTERY_POS_X+18+69-batfil,DISPLAY_BATTERY_POS_Y+8,batfil,16);
		fnt = FONT(FONT_LARGE, COLOR_FG_NONLV, col_field);
		bmp_printf(fnt, DISPLAY_BATTERY_POS_X+14, DISPLAY_BATTERY_POS_Y+35, "%3d%%", batlev);
    }
    else
    {
		fnt = FONT(FONT_LARGE, COLOR_FG_NONLV, col_field);
		bmp_printf(fnt, DISPLAY_BATTERY_POS_X+14, DISPLAY_BATTERY_POS_Y+35, "%3d%%", batlev);
	}

	bg = bmp_getpixel(MLU_STATUS_POS_X, MLU_STATUS_POS_Y);
	bmp_printf(FONT(FONT_MED, COLOR_YELLOW, bg), MLU_STATUS_POS_X, MLU_STATUS_POS_Y, get_mlu() ? "MLU" : "   ");

    if (avail_shot>999) // it is a Canon bug (only 3 digits), it can display on the other info screen four digit number
    {                   // but we can write 5 digits if necessary
		bmp_fill(col_field,540,384,152,72); // clear the "[999]" 
		if (avail_shot>9999) 
		{
            char msg[7];
            snprintf(msg, sizeof(msg), "[%5d%]", avail_shot);
            bfnt_puts(msg, 550 , 402, COLOR_FG_NONLV, col_field);
		} 
		else 
		{
            char msg[6];
            snprintf(msg, sizeof(msg), "[%4d%]", avail_shot);
            bfnt_puts(msg, 560 , 402, COLOR_FG_NONLV, col_field);
		}
    }

	//~ display_lcd_remote_info();
	display_trap_focus_info();
}


int battery_level = 0;
CONFIG_INT("battery.drain.rate.rev", battery_seconds_same_level_ok, 0);
int battery_seconds_same_level_tmp = 0;
int battery_level_transitions = 0;

PROP_HANDLER(PROP_BATTERY_REPORT)
{
	battery_level = buf[1] & 0xff;
}
int GetBatteryLevel()
{
	return battery_level;
}
int GetBatteryTimeRemaining()
{
	return battery_seconds_same_level_ok * battery_level;
}
int GetBatteryDrainRate() // percents per hour
{
	return 3600 / battery_seconds_same_level_ok;
}

// called every second
void RefreshBatteryLevel_1Hz()
{
	static int k = 0;
	k++;

    #if 0 // probably works, but let's play safe
	if (k % 10 == 0 &&
		lens_info.job_state == 0) // who knows what race conditions are here... I smell one :)
	{
		int x = 31;
		prop_request_change(PROP_BATTERY_REPORT, &x, 1); // see PROP_Request PROP_BATTERY_REPORT
	}
    #endif

	msleep(50);

	// check how many seconds battery indicator was at the same percentage
	// this is a rough indication of how fast the battery is draining
	static int old_battery_level = -1;
	if (battery_level == old_battery_level)
	{
		battery_seconds_same_level_tmp++;
	}
	else
	{
		battery_level_transitions++;
		if (battery_level_transitions >= 2)
			battery_seconds_same_level_ok = battery_seconds_same_level_tmp;
		battery_seconds_same_level_tmp = 0;
	}
	old_battery_level = battery_level;
}

// dummy stub
int new_LiveViewApp_handler = 0xff123456;

