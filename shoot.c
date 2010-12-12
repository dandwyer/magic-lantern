/** \file
 * Shooting experiments: intervalometer, LCD RemoteShot. More to come.
 * 
 * (C) 2010 Alex Dumitrache, broscutamaker@gmail.com
 */
/*
 * Magic Lantern is Copyright (C) 2009 Trammell Hudson <hudson+ml@osresearch.net>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include "dryos.h"
#include "bmp.h"
#include "version.h"
#include "config.h"
#include "menu.h"
#include "property.h"

CONFIG_INT( "interval.timer.index", interval_timer_index, 2 );

int intervalometer_running = 0;
int lcd_release_running = 0;

int timer_values[] = {1,2,5,10,30,60,300,900,3600};

static void
interval_timer_display( void * priv, int x, int y, int selected )
{
	bmp_printf(
		selected ? MENU_FONT_SEL : MENU_FONT,
		x, y,
		"IntervalTime: %4ds", 
		timer_values[*(int*)priv]
	);
}

static void
interval_timer_toggle( void * priv )
{
	unsigned * ptr = priv;
	*ptr = (*ptr + 1) % COUNT(timer_values);
}

static void 
intervalometer_display( void * priv, int x, int y, int selected )
{
	bmp_printf(
		selected ? MENU_FONT_SEL : MENU_FONT,
		x, y,
		"Intervalometer: %s",
		(*(int*)priv) ? "ON " : "OFF"
	);
}

static void 
lcd_release_display( void * priv, int x, int y, int selected )
{
	bmp_printf(
		selected ? MENU_FONT_SEL : MENU_FONT,
		x, y,
		"LCD RemoteShot: %s",
		(*(int*)priv) ? "ON " : "OFF"
	);
}

struct menu_entry shoot_menus[] = {
	{
		.priv		= &interval_timer_index,
		.select		= interval_timer_toggle,
		.display	= interval_timer_display,
	},
	{
		.priv		= &intervalometer_running,
		.select		= menu_binary_toggle_and_close,
		.display	= intervalometer_display,
	},
	{
		.priv		= &lcd_release_running,
		.select		= menu_binary_toggle_and_close,
		.display	= lcd_release_display,
	},
};

int display_sensor_active()
{
	return !(*(int*)(0x3128+44));
}

PROP_HANDLER( PROP_GUI_STATE )
{
    int gui_state = buf[0];
    if (gui_state == 1) // PLAYMENU
    {
		intervalometer_running = 0;
		lcd_release_running = 0;
	}		
	return prop_cleanup( token, property );
}

int lv_drawn;
PROP_HANDLER( PROP_LV_ACTION )
{
    DebugMsg(DM_MAGIC, 3, "PROP_LV_ACTION => %d", buf[0]);
	lv_drawn = !buf[0];
	return prop_cleanup( token, property );
}

static void
shoot_task( void )
{
	int i = 0;
    menu_add( "Shoot", shoot_menus, COUNT(shoot_menus) );
	while(1)
	{
		if (intervalometer_running)
		{
			lens_take_picture(0);
			for (i = 0; i < timer_values[interval_timer_index]; i++)
			{
				msleep(1000);
				if (intervalometer_running) bmp_printf(FONT_MED, 20, 35, "Press PLAY or MENU to stop the intervalometer.");
			}
		}
		else if (lcd_release_running)
		{
			if (!lv_drawn) bmp_printf(FONT_MED, 20, 35, "Move your hand close to the LCD screen to take a picture!");
			else bmp_printf(FONT_MED, 20, 35, "LCD RemoteShot does not work in LiveView, sorry...");
			if (display_sensor_active())
			{
				lens_take_picture(0);
				while (display_sensor_active()) { msleep(500); }
			}
			msleep(20);
		}
		else msleep(500);
	}
}

TASK_CREATE( "shoot_task", shoot_task, 0, 0x18, 0x1000 );


