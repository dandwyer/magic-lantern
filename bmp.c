/** \file
 * Drawing routines.
 *
 * These are Magic Lantern routines to draw into the BMP LVRAM.
 * They are not derived from DryOS routines.
 */
/*
 * Copyright (C) 2009 Trammell Hudson <hudson+ml@osresearch.net>
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
#include "font.h"
#include <stdarg.h>


static void
_draw_char(
	unsigned	fontspec,
	uint8_t *	bmp_vram_row,
	char		c
)
{
	unsigned i,j;
	const struct font * const font = fontspec_font( fontspec );

	uint32_t	fg_color	= fontspec_fg( fontspec ) << 24;
	uint32_t	bg_color	= fontspec_bg( fontspec ) << 24;

	// Special case -- fg=bg=0 => white on transparent
	if( fg_color == 0 && bg_color == 0 )
	{
		fg_color = COLOR_WHITE << 24;
		bg_color = COLOR_BG << 24;
	}

	const uint32_t	pitch		= bmp_pitch() / 4;
	uint32_t *	front_row	= (uint32_t *) bmp_vram_row;

	//uint32_t flags = cli();
	for( i=0 ; i<font->height ; i++ )
	{
		// Start this scanline
		uint32_t * row = front_row;

		// move to the next scanline
		front_row += pitch;

		uint32_t pixels = font->bitmap[ c + (i << 7) ];
		uint8_t pixel;

		for( j=0 ; j<font->width/4 ; j++ )
		{
			uint32_t bmp_pixels = 0;
			for( pixel=0 ; pixel<4 ; pixel++, pixels <<=1 )
			{
				bmp_pixels >>= 8;
				bmp_pixels |= (pixels & 0x80000000) ? fg_color : bg_color;
			}

			*(row++) = bmp_pixels;
		}
	}

	//sei( flags );
}


void
bmp_puts(
	unsigned		fontspec,
	unsigned		x,
	unsigned		y,
	const char *		s
)
{
	const uint32_t		pitch = bmp_pitch();
	uint8_t * vram = bmp_vram();
	if( !vram )
		return;
	uint8_t * first_row = vram + y * pitch + x;
	uint8_t * row = first_row;

	char c;

	const struct font * const font = fontspec_font( fontspec );

	while( (c = *s++) )
	{
		if( c == '\n' )
		{
			row = first_row += pitch * font->height;
			continue;
		}

		_draw_char( fontspec, row, c );
		row += font->width;
	}

}

void
bmp_printf(
	unsigned		fontspec,
	unsigned		x,
	unsigned		y,
	const char *		fmt,
	...
)
{
	va_list			ap;
	char			buf[ 256 ];

	va_start( ap, fmt );
	vsnprintf( buf, sizeof(buf), fmt, ap );
	va_end( ap );

	bmp_puts( fontspec, x, y, buf );
}


void
bmp_hexdump(
	unsigned		fontspec,
	unsigned		x,
	unsigned		y,
	const void *		buf,
	size_t			len
)
{
	if( len == 0 )
		return;

	// Round up
	len = (len + 15) & ~15;

	const uint32_t *	d = (uint32_t*) buf;

	do {
		bmp_printf(
			fontspec,
			x,
			y,
			"%08x: %08x %08x %08x %08x",
			(unsigned) d,
			len >  0 ? (unsigned) d[ 0/4] : 0,
			len >  4 ? (unsigned) d[ 4/4] : 0,
			len >  8 ? (unsigned) d[ 8/4] : 0,
			len > 12 ? (unsigned) d[12/4] : 0
		);

		y += fontspec_height( fontspec );
		d += 4;
		len -= 16;
	} while(len);
}


/** Fill a section of bitmap memory with solid color
 * Only has a four-pixel resolution in X.
 */
void
bmp_fill(
	uint8_t			color,
	uint32_t		x,
	uint32_t		y,
	uint32_t		w,
	uint32_t		h
)
{
	const uint32_t start = x;
	const uint32_t width = bmp_width();
	const uint32_t pitch = bmp_pitch();
	const uint32_t height = bmp_height();

	// Convert to words and limit to the width of the LCD
	if( start + w > width )
		w = width - start;
	
	const uint32_t word = 0
		| (color << 24)
		| (color << 16)
		| (color <<  8)
		| (color <<  0);

	if( y > height )
		y = height;

	uint16_t y_end = y + h;
	if( y_end > height )
		y_end = height;

	if( w == 0 || h == 0 )
		return;

	//uint32_t flags = cli();
	uint8_t * const vram = bmp_vram();
	uint32_t * row = (void*)( vram + y * pitch + start );

	bmp_printf( FONT_SMALL, 0, 400, "bmp %08x", (unsigned) vram );
	DebugMsg( DM_MAGIC, 3,
		"%s: vram=%x start=%d-%d y=%d-%d => %x",
		__func__,
		(unsigned) vram,
		start,
		w/4,
		y,
		y_end,
		(unsigned) row
	);
	if( !vram || ( 1 & (uintptr_t) vram ) )
	{
		//sei( flags );
		return;
	}


	for( ; y<y_end ; y++, row += pitch/4 )
	{
		uint32_t x;

		for( x=0 ; x<w/4 ; x++ )
		{
			row[ x ] = word;
			asm( "nop" );
			asm( "nop" );
			asm( "nop" );
			asm( "nop" );
		}
	}

	//sei( flags );
}


/** Draw a picture of the BMP color palette. */
void
bmp_draw_palette( void )
{
	uint32_t x, y, msb, lsb;
	const uint32_t height = 30;
	const uint32_t width = 45;

	for( msb=0 ; msb<16; msb++ )
	{
		for( y=0 ; y<height; y++ )
		{
			uint8_t * const row = bmp_vram() + (y + height*msb) * bmp_pitch();

			for( lsb=0 ; lsb<16 ; lsb++ )
			{
				for( x=0 ; x<width ; x++ )
					row[x+width*lsb] = (msb << 4) | lsb;
			}
		}
	}

	static int written;
	if( !written )
		dispcheck();
	written = 1;
}


/** Load a BMP file into memory so that it can be drawn onscreen */
struct bmp_file_t *
bmp_load(
	const char *		filename
)
{
	FILE * file = FIO_Open( filename, O_RDONLY );
	if( file == INVALID_PTR )
		goto open_fail;

	unsigned size;
	if( FIO_GetFileSize( filename, &size ) != 0 )
		goto getfilesize_fail;

	DebugMsg( DM_MAGIC, 3, "File '%s' (%x) size %d bytes",
		filename,
		(unsigned) file,
		size
	);

	void * buf = malloc( size );
	if( !buf )
	{
		DebugMsg( DM_MAGIC, 3, "%s: malloc failed", filename );
		goto malloc_fail;
	}

	unsigned rc = FIO_ReadFile( file, buf, size );
	if( rc != size )
	{
		DebugMsg( DM_MAGIC, 3, "%s: size=%d rc=%d", filename, size, rc );
		goto read_fail;
	}

	// Try to force data to appear in the buffer
	msleep( 100 );

	struct bmp_file_t * bmp = buf;
	if( bmp->signature != 0x4D42 )
	{
		DebugMsg( DM_MAGIC, 3, "%s: signature %04x", filename, bmp->signature );
		goto signature_fail;
	}

	// Update the offset pointer to point to the image data
	// if it is within bounds
	unsigned offset = (unsigned) bmp->image;
	if( offset > size )
	{
		DebugMsg( DM_MAGIC, 3, "%s: size too large: %x > %x", filename, offset, size );
		goto offsetsize_fail;
	}

	bmp->image = offset + (uint8_t*) buf;

	FIO_CloseFile( file );
	return buf;

offsetsize_fail:
signature_fail:
read_fail:
	free( buf );
malloc_fail:
getfilesize_fail:
	FIO_CloseFile( file );
open_fail:
	return NULL;
}
