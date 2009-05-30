#ifndef _dryos_gui_h_
#define _dryos_gui_h_

/** \file
 * DryOS GUI structures and functions.
 */

/** Display types.
 *
 * 0 == 720p LCD
 * 3 == 960 HDMI
 * 6 == 960 HDMI
 * All others unknown.
 */
extern int
gui_get_display_type( void );

extern void
color_palette_push(
	int			palette_id
);


/** Create a GUI event handler.
 * Does this always take a dialog pointer?
 */
extern int
gui_task_create(
	int			(*handler)( void * ),
	void *			arg_dialog
);



/** Event types */
#define GOT_TOP_OF_CONTROL		0x800
#define LOST_TOP_OF_CONTROL		0x801
#define INITIALIZE_CONTROLLER		0x802
#define TERMINATE_WINSYS		0x804
#define DELETE_DIALOG_REQUEST		0x805
#define PRESS_RIGHT_BUTTON		0x807
#define PRESS_LEFT_BUTTON		0x809
#define PRESS_UP_BUTTON			0x80B
#define PRESS_DOWN_BUTTON		0x80D
#define PRESS_MENU_BUTTON		0x80F
#define PRESS_SET_BUTTON		0x812
#define PRESS_INFO_BUTTON		0x829
#define ELECTRONIC_SUB_DIAL_RIGHT	0x82B
#define ELECTRONIC_SUB_DIAL_LEFT	0x82C
#define PRESS_DISP_BUTTON		0x10000000
#define PRESS_DIRECT_PRINT_BUTTON	0x10000005
#define PRESS_FUNC_BUTTON		0x10000007
#define PRESS_PICTURE_STYLE_BUTTON	0x10000009
#define OPEN_SLOT_COVER			0x1000000B
#define CLOSE_SLOT_COVER		0x1000000C
#define START_SHOOT_MOVIE		0x1000008A
#define RESIZE_MAYBE			0x10000085


struct gui_struct
{
	uint32_t		off_0x00;
	uint32_t		off_0x04;
	uint32_t		off_0x08;
	uint32_t		off_0x0c;
	uint32_t		off_0x10;
	uint32_t		off_0x14;
	uint32_t		off_0x18;
	uint32_t		off_0x1c;
	uint32_t		off_0x20;
	uint32_t		off_0x24;
	uint32_t		off_0x28;
	uint32_t		off_0x2c;
	uint32_t		off_0x30;
	uint32_t		off_0x34;
	uint32_t		off_0x38;
	uint32_t		off_0x3c;
	uint32_t		off_0x40;
	uint32_t		off_0x44;
	uint32_t		off_0x48;
	uint32_t		off_0x4c;
	uint32_t		off_0x50;
	uint32_t		off_0x54;
	uint32_t		off_0x58;
	uint32_t		off_0x5c;
	uint32_t		off_0x60;
	uint32_t		off_0x64;
	uint32_t		off_0x68;
	uint32_t		off_0x6c;
	uint32_t		off_0x70;
	uint32_t		off_0x74;
	uint32_t		off_0x78;
	uint32_t		off_0x7c;
	uint32_t		off_0x80;
	uint32_t		off_0x84;
	uint32_t		off_0x88;
	uint32_t		off_0x8c;
	uint32_t		off_0x90;
	uint32_t		off_0x94;
	uint32_t		off_0x98;
	uint32_t		off_0x9c;
	uint32_t		off_0xa0;
	uint32_t		off_0xa4;
	uint32_t		off_0xa8;
	uint32_t		off_0xac;
	uint32_t		off_0xb0;
	uint32_t		off_0xb4;
	uint32_t		off_0xb8;
	uint32_t		off_0xbc;

	/**
	 * 0 == no,
	 * 1 == starting,
	 * 2 == started,
	 * 3 == ending
	*/
	uint32_t		movie_is_recording;		// off_0xc0;

	uint32_t		off_0xc4;
	uint32_t		off_0xc8;
	uint32_t		off_0xcc;
	uint32_t		off_0xd0;
	uint32_t		off_0xd4;
	uint32_t		off_0xd8;

	/**
	 * 0 - 100%
	 */
	uint32_t		movie_record_buffer;		// off_0xdc;

	uint32_t		off_0xe0;
	uint32_t		off_0xe4;
	uint32_t		off_0xe8;
	uint32_t		off_0xec;
	uint32_t		off_0xf0;
	uint32_t		off_0xf4;
	uint32_t		off_0xf8;
	uint32_t		off_0xfc;
};

extern struct gui_struct gui_struct;

#endif
