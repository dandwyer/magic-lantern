#ifndef _bmp_h_
#define _bmp_h_

/** \file
 * Drawing routines for the bitmap VRAM.
 *
 * These are Magic Lantern routines to draw shapes and text into
 * the LVRAM for display on the LCD or HDMI output.
 */

#include "dryos.h"
#include "font.h"

/** Returns a pointer to the real BMP vram */
static inline uint8_t *
bmp_vram(void)
{
	return bmp_vram_info[1].vram2;
}


/** Returns the width, pitch and height of the BMP vram.
 * These should check the current mode since we might be in
 * HDMI output mode, which uses the full 960x540 space.
 */
static inline uint32_t bmp_width(void) { return 720; }
static inline uint32_t bmp_pitch(void) { return 960; }
static inline uint32_t bmp_height(void) { return 480; }

/** Font specifiers include the font, the fg color and bg color */
#define FONT_MASK		0x000F0000
#define FONT_LARGE		0x00030000
#define FONT_MED		0x00020000
#define FONT_SMALL		0x00010000

#define FONT(font,fg,bg)	( 0 \
	| ((font) & FONT_MASK) \
	| ((bg) & 0xFF) << 8 \
	| ((fg) & 0xFF) << 0 \
)

static inline struct font *
fontspec_font(
	unsigned		fontspec
)
{
	switch( fontspec & FONT_MASK )
	{
	default:
	case FONT_SMALL:	return &font_small;
	case FONT_MED:		return &font_med;
	case FONT_LARGE:	return &font_large;
	}
}


static inline unsigned
fontspec_fg(
	unsigned		fontspec
)
{
	return (fontspec >> 0) & 0xFF;
}

static inline unsigned
fontspec_bg(
	unsigned		fontspec
)
{
	return (fontspec >> 8) & 0xFF;
}



static inline unsigned
fontspec_height(
	unsigned		fontspec
)
{
	return fontspec_font(fontspec)->height;
}


extern void
bmp_printf(
	unsigned		fontspec,
	unsigned		x,
	unsigned		y,
	const char *		fmt,
	...
) __attribute__((format(printf,4,5)));


extern void
bmp_hexdump(
	unsigned		fontspec,
	unsigned		x,
	unsigned		y,
	const void *		buf,
	size_t			len
);


extern void
bmp_puts(
	unsigned		fontspec,
	unsigned		x,
	unsigned		y,
	const char *		s
);

/** Fill the screen with a bitmap palette */
extern void
bmp_draw_palette( void );


/** Fill a section of bitmap memory with solid color
 * Only has a four-pixel resolution in X.
 */
extern void
bmp_fill(
	uint8_t			color,
	uint32_t		x,
	uint32_t		y,
	uint32_t		w,
	uint32_t		h
);


/** Some selected colors */
#define COLOR_BG		0x03 // transparent black
#define COLOR_WHITE		0x01 // Normal white
#define COLOR_BLUE		0x0B // normal blue
#define COLOR_RED		0x08 // normal red

static inline uint32_t
color_word(
	uint8_t			color
)
{
	return 0
		| ( color << 24 )
		| ( color << 16 )
		| ( color <<  8 )
		| ( color <<  0 )
		;
}


#endif
