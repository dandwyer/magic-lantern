#include "dryos.h"
#include "bmp.h"
#include "menu.h"
#include "property.h"
#include "config.h"
#include "gui.h"
#include "af_patterns.h"

type_PATTERN_MAP_ITEM pattern_map[] = {
		{AF_PATTERN_CENTER,         AF_PATTERN_SQUARE, AF_PATTERN_TOPHALF,        AF_PATTERN_BOTTOMHALF,     AF_PATTERN_LEFTHALF,      AF_PATTERN_RIGHTHALF},
		{AF_PATTERN_SQUARE,         AF_PATTERN_HLINE,  AF_PATTERN_TOPHALF,        AF_PATTERN_BOTTOMHALF,     AF_PATTERN_LEFTHALF,      AF_PATTERN_RIGHTHALF},

		{AF_PATTERN_TOP,            AF_PATTERN_CENTER, AF_PATTERN_TOP,            AF_PATTERN_TOPTRIANGLE,    AF_PATTERN_TOPLEFT,       AF_PATTERN_TOPRIGHT},
		{AF_PATTERN_TOPTRIANGLE,    AF_PATTERN_CENTER, AF_PATTERN_TOP,            AF_PATTERN_TOPDIAMOND,     AF_PATTERN_LEFTTRIANGLE,  AF_PATTERN_RIGHTTRIANGLE},
		{AF_PATTERN_TOPDIAMOND,     AF_PATTERN_CENTER, AF_PATTERN_TOPTRIANGLE,    AF_PATTERN_TOPHALF,        AF_PATTERN_LEFTDIAMOND,   AF_PATTERN_RIGHTDIAMOND},
		{AF_PATTERN_TOPHALF,        AF_PATTERN_CENTER, AF_PATTERN_TOPDIAMOND,     AF_PATTERN_HLINE,          AF_PATTERN_LEFTHALF,      AF_PATTERN_RIGHTHALF},

		{AF_PATTERN_BOTTOM,         AF_PATTERN_CENTER, AF_PATTERN_BOTTOMTRIANGLE, AF_PATTERN_BOTTOM,         AF_PATTERN_BOTTOMLEFT,    AF_PATTERN_BOTTOMRIGHT},
		{AF_PATTERN_BOTTOMTRIANGLE, AF_PATTERN_CENTER, AF_PATTERN_BOTTOMDIAMOND,  AF_PATTERN_BOTTOM,         AF_PATTERN_LEFTTRIANGLE,  AF_PATTERN_RIGHTTRIANGLE},
		{AF_PATTERN_BOTTOMDIAMOND,  AF_PATTERN_CENTER, AF_PATTERN_BOTTOMHALF,     AF_PATTERN_BOTTOMTRIANGLE, AF_PATTERN_LEFTDIAMOND,   AF_PATTERN_RIGHTDIAMOND},
		{AF_PATTERN_BOTTOMHALF,     AF_PATTERN_CENTER, AF_PATTERN_HLINE,          AF_PATTERN_BOTTOMDIAMOND,  AF_PATTERN_LEFTHALF,      AF_PATTERN_RIGHTHALF},

		{AF_PATTERN_TOPLEFT,        AF_PATTERN_CENTER, AF_PATTERN_TOP,            AF_PATTERN_BOTTOMLEFT,     AF_PATTERN_LEFT,          AF_PATTERN_TOPRIGHT},
		{AF_PATTERN_TOPRIGHT,       AF_PATTERN_CENTER, AF_PATTERN_TOP,            AF_PATTERN_BOTTOMRIGHT,    AF_PATTERN_TOPLEFT,       AF_PATTERN_RIGHT},
		{AF_PATTERN_BOTTOMLEFT,     AF_PATTERN_CENTER, AF_PATTERN_TOPLEFT,        AF_PATTERN_BOTTOM,         AF_PATTERN_LEFT,          AF_PATTERN_BOTTOMRIGHT},
		{AF_PATTERN_BOTTOMRIGHT,    AF_PATTERN_CENTER, AF_PATTERN_TOPRIGHT,       AF_PATTERN_BOTTOM,         AF_PATTERN_BOTTOMLEFT,    AF_PATTERN_RIGHT},

		{AF_PATTERN_LEFT,           AF_PATTERN_CENTER, AF_PATTERN_TOPLEFT,        AF_PATTERN_BOTTOMLEFT,     AF_PATTERN_LEFT,          AF_PATTERN_LEFTTRIANGLE},
		{AF_PATTERN_LEFTTRIANGLE,   AF_PATTERN_CENTER, AF_PATTERN_TOPTRIANGLE,    AF_PATTERN_BOTTOMTRIANGLE, AF_PATTERN_LEFT,          AF_PATTERN_LEFTDIAMOND},
		{AF_PATTERN_LEFTDIAMOND,    AF_PATTERN_CENTER, AF_PATTERN_TOPDIAMOND,     AF_PATTERN_BOTTOMDIAMOND,  AF_PATTERN_LEFTTRIANGLE,  AF_PATTERN_LEFTHALF},
		{AF_PATTERN_LEFTHALF,       AF_PATTERN_CENTER, AF_PATTERN_TOPHALF,        AF_PATTERN_BOTTOMHALF,     AF_PATTERN_LEFTDIAMOND,   AF_PATTERN_VLINE},

		{AF_PATTERN_RIGHT,          AF_PATTERN_CENTER, AF_PATTERN_TOPRIGHT,       AF_PATTERN_BOTTOMRIGHT,    AF_PATTERN_RIGHTTRIANGLE, AF_PATTERN_RIGHT},
		{AF_PATTERN_RIGHTTRIANGLE,  AF_PATTERN_CENTER, AF_PATTERN_TOPTRIANGLE,    AF_PATTERN_BOTTOMTRIANGLE, AF_PATTERN_RIGHTDIAMOND,  AF_PATTERN_RIGHT},
		{AF_PATTERN_RIGHTDIAMOND,   AF_PATTERN_CENTER, AF_PATTERN_TOPDIAMOND,     AF_PATTERN_BOTTOMDIAMOND,  AF_PATTERN_RIGHTHALF,     AF_PATTERN_RIGHTTRIANGLE},
		{AF_PATTERN_RIGHTHALF,      AF_PATTERN_CENTER, AF_PATTERN_TOPHALF,        AF_PATTERN_BOTTOMHALF,     AF_PATTERN_VLINE,         AF_PATTERN_RIGHTDIAMOND},

		{AF_PATTERN_HLINE,          AF_PATTERN_VLINE,  AF_PATTERN_TOPHALF,        AF_PATTERN_BOTTOMHALF,     AF_PATTERN_LEFTHALF,      AF_PATTERN_RIGHTHALF},
		{AF_PATTERN_VLINE,          AF_PATTERN_ALL,    AF_PATTERN_TOPHALF,        AF_PATTERN_BOTTOMHALF,     AF_PATTERN_LEFTHALF,      AF_PATTERN_RIGHTHALF},

		{AF_PATTERN_ALL,            AF_PATTERN_CENTER, AF_PATTERN_TOPHALF,        AF_PATTERN_BOTTOMHALF,     AF_PATTERN_LEFTHALF,      AF_PATTERN_RIGHTHALF},

		END_OF_LIST
};

int afp_transformer (int pattern, type_DIRECTION direction);

PROP_INT(PROP_AFPOINT, af_point);

void afp_show_in_viewfinder()
{
	card_led_on();
	#if defined(CONFIG_60D) || defined(CONFIG_50D)
	int delay = 50;
	#else
	int delay = 0;
	#endif
	msleep(50);
	assign_af_button_to_halfshutter();
	msleep(50);
	SW1(1,delay);
	msleep(50);
	SW1(0,delay);
	msleep(50);
	restore_af_button_assignment();
	card_led_off();
}

void set_af_point(int afpoint)
{
	if (beep_enabled) Beep();
	prop_request_change(PROP_AFPOINT, &afpoint, 4);
	task_create("afp_tmp", 0x18, 0, afp_show_in_viewfinder, 0);
}

int afpoint_for_key_guess = 0;

void afp_center () {
	set_af_point(afp_transformer(af_point, DIRECTION_CENTER));
}

void afp_top () {
	set_af_point(afp_transformer(af_point, DIRECTION_UP));
}

void afp_bottom () {
	set_af_point(afp_transformer(af_point, DIRECTION_DOWN));
}

void afp_left () {
	set_af_point(afp_transformer(af_point, DIRECTION_LEFT));
}

void afp_right () {
	set_af_point(afp_transformer(af_point, DIRECTION_RIGHT));
}

int afp_transformer (int pattern, type_DIRECTION direction) {
	type_PATTERN_MAP_ITEM *item;

	// Loop over all items in the pattern map
	for (item = pattern_map; ! IS_EOL(item); item++) {

		// When we find an item matching the current pattern...
		if (item->pattern == pattern) {

			// ... we return the next pattern, according to the direction indicated
			switch (direction) {
			case DIRECTION_CENTER:
				return item->next_center;
			case DIRECTION_UP:
				return item->next_top;
			case DIRECTION_DOWN:
				return item->next_bottom;
			case DIRECTION_LEFT:
				return item->next_left;
			case DIRECTION_RIGHT:
				return item->next_right;
			}
		}
	}

	// Just in case something goes wrong
	return AF_PATTERN_CENTER;
}

int handle_af_patterns(struct event * event)
{
	extern int af_patterns;
	if (af_patterns && !lv && gui_state == GUISTATE_IDLE && tft_status)
	{
		if (event->param == BGMT_PRESS_LEFT)   { afp_left(); return 0; }
		if (event->param == BGMT_PRESS_RIGHT)  { afp_right(); return 0; }
		if (event->param == BGMT_PRESS_UP)     { afp_top(); return 0; }
		if (event->param == BGMT_PRESS_DOWN)   { afp_bottom(); return 0; }
		if (event->param == BGMT_PRESS_SET)    { afp_center(); return 0; }
	}
	return 1;
}
