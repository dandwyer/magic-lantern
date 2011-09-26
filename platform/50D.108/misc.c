// misc functions specific to 550D/109

#include <dryos.h>
#include <property.h>
#include <bmp.h>
#include <config.h>
#include <consts.h>
#include <lens.h>

int lv_disp_mode;
PROP_HANDLER(PROP_HOUTPUT_TYPE)
{
	lv_disp_mode = buf[0];
	return prop_cleanup(token, property);
}

void display_shooting_info() // called from debug task
{
	if (lv) return;
	
	int bg = bmp_getpixel(314, 260);
	uint32_t fnt = FONT(FONT_MED, COLOR_FG_NONLV, bg);

	if (lens_info.wb_mode == WB_KELVIN)
	{
		bmp_printf(fnt, 320, 260, "%5dK", lens_info.kelvin);
	}
	if (lens_info.wbs_gm || lens_info.wbs_ba)
	{
		fnt = FONT(FONT_LARGE, COLOR_FG_NONLV, bg);

		int ba = lens_info.wbs_ba;
		if (ba) bmp_printf(fnt, 435, 240, "%s%d ", ba > 0 ? "A" : "B", ABS(ba));
		else bmp_printf(fnt, 435, 240, "   ");

		int gm = lens_info.wbs_gm;
		if (gm) bmp_printf(fnt, 435, 270, "%s%d ", gm > 0 ? "G" : "M", ABS(gm));
		else bmp_printf(fnt, 435, 270, "   ");
	}

	iso_refresh_display();

	bg = bmp_getpixel(15, 430);
	fnt = FONT(FONT_MED, COLOR_FG_NONLV, bg);
	
	extern int hdr_steps, hdr_stepsize;
	if (hdr_steps > 1)
		bmp_printf(fnt, 380, 450, "HDR %dx%dEV", hdr_steps, hdr_stepsize/8);
	else
		bmp_printf(fnt, 380, 450, "           ");

	//~ bmp_printf(fnt, 200, 450, "Flash:%s", 
		//~ strobo_firing == 0 ? " ON" : 
		//~ strobo_firing == 1 ? "OFF" : "Auto"
		//~ strobo_firing < 2 && flash_and_no_flash ? "/T" : "  "
		//~ );

	bmp_printf(fnt, 40, 460, get_mlu() ? "MLU" : "   ");

	display_lcd_remote_icon(480, 0);
	display_trap_focus_info();
}



// image buffers
// http://magiclantern.wikia.com/wiki/VRAM

PROP_INT(0x80030002, mvr_rec)

struct vram_info * get_yuv422_hd_vram()
{
	static struct vram_info _vram_info;
	_vram_info.vram = (uint8_t*)YUV422_HD_BUFFER_DMA_ADDR;
	_vram_info.width = 1 ? 1560 : 1024;
	_vram_info.pitch = _vram_info.width << 1; 
	_vram_info.height = 1 ? 1048 : 680;
	
	NotifyBox(1000, "%d %d", recording, mvr_rec);
	return &_vram_info;
}


void* get_fastrefresh_422_buf()
{
	switch (YUV422_LV_BUFFER_DMA_ADDR)
	{
		case YUV422_LV_BUFFER_1:
			return (void*) YUV422_LV_BUFFER_2;
		case YUV422_LV_BUFFER_2:
			return (void*) YUV422_LV_BUFFER_3;
		case YUV422_LV_BUFFER_3:
			return (void*) YUV422_LV_BUFFER_1;
	}
	return YUV422_LV_BUFFER_1;
}

void* get_write_422_buf()
{
	switch (YUV422_LV_BUFFER_DMA_ADDR)
	{
		case YUV422_LV_BUFFER_1:
			return (void*) YUV422_LV_BUFFER_1;
		case YUV422_LV_BUFFER_2:
			return (void*) YUV422_LV_BUFFER_2;
		case YUV422_LV_BUFFER_3:
			return (void*) YUV422_LV_BUFFER_3;
	}
	return YUV422_LV_BUFFER_1;
}

int vram_width = 720;
int vram_height = 480;

struct vram_info * get_yuv422_vram()
{
	static struct vram_info _vram_info;
	_vram_info.vram = get_fastrefresh_422_buf();
	if (gui_state == GUISTATE_PLAYMENU) _vram_info.vram = (void*) YUV422_LV_BUFFER_DMA_ADDR;

	_vram_info.width = vram_width;
	_vram_info.height = vram_height;
	_vram_info.pitch = _vram_info.width * 2;

	//~ bmp_printf(FONT_LARGE, 100, 100, "%d x %d", _vram_info.width, _vram_info.height);

	return &_vram_info;
}

void guess_fastrefresh_direction(){};
/*
int GetBatteryLevel()
{
	return -1;
	if (!is_safe_to_mess_with_the_display(0)) return -1;
	return PD_GetBatteryPower() + 1;
}
*/


// some dummy stubs
int lcd_release_running = 0;
void lcd_release_step() {};
int get_lcd_sensor_shortcuts() { return 0; }
void display_lcd_remote_icon(int x0, int y0) {}
