/** \file
 * Onscreen audio meters
 */
#include "dryos.h"
#include "bmp.h"
#include "config.h"
#include "property.h"

/** Read the raw level from the audio device.
 *
 * Expected values are signed 16-bit?
 */
static inline int16_t
audio_read_level( int channel )
{
	uint32_t *audio_level = (uint32_t*)( 0xC0920000 + 0x110 );
	return (int16_t) audio_level[channel];
}

struct audio_level
{
	int		last;
	int		avg;
	int		peak;
	int		pad;
};


struct audio_level audio_levels[2];



/** Returns a dB translated from the raw level
 *
 * Range is -40 to 0 dB
 */
static int
audio_level_to_db(
	int			raw_level
)
{
	int db;

	for( db = 40 ; db ; db-- )
	{
		if( audio_thresholds[db] > raw_level )
			return -db;
	}

	return 0;
}




#ifdef OSCOPE_METERS
void draw_meters(void)
{
#define MAX_SAMPLES 720
	static int16_t levels[ MAX_SAMPLES ];
	static uint32_t index;
	levels[ index++ ] = audio_read_level();
	if( index >= MAX_SAMPLES )
		index = 0;


	struct vram_info * vram = &vram_info[ vram_get_number(2) ];
	//thunk audio_dev_compute_average_level = (void*) 0xFF9725C4;
	//audio_dev_compute_average_level();

	// The level goes from -40 to 0
	uint32_t x;
	for( x=0 ; x<MAX_SAMPLES && x<vram->width ; x++ )
	{
		uint16_t y = 256 + levels[ x ] / 128;
		vram->vram[ y * vram->pitch + x ] = 0xFFFF;
	}

	uint32_t y;
	for( y=0 ; y<128 ; y++ )
	{
		vram->vram[ y * vram->pitch + index ] = 0x888F;
	}

}
#else


static uint8_t
db_to_color(
	int			db
)
{
	if( db < -35 )
		return 0x2F; // white
	if( db < -20 )
		return 0x06; // dark green
	if( db < -15 )
		return 0x0F; // yellow
	return 0x0c; // dull red
}

static uint8_t
db_peak_to_color(
	int			db
)
{
	if( db < -35 )
		return 0x7f; // dark blue
	if( db < -20 )
		return 0x7f; // dark blue
	if( db < -15 )
		return 0xAE; // bright yellow
	return 0x08; // bright red
}


static void
draw_meter(
	int			y_origin,
	struct audio_level *	level
)
{
	const uint32_t width = 640; // bmp_width();
	const uint32_t pitch = bmp_pitch();
	uint32_t * row = (uint32_t*) bmp_vram();
	if( !row )
		return;

	// Skip to the desired y coord and over the
	// space for the numerical levels
	row += (pitch/4) * y_origin + 8;

	const int db_avg = audio_level_to_db( level->avg );
	const int db_peak = audio_level_to_db( level->peak );

	// levels go from -40 to 0, so -40 * 16 == 640
	const uint32_t x_db_avg = (width + db_avg * 16) / 4;
	const uint32_t x_db_peak = (width + db_peak * 16) / 4;

	const uint8_t bar_color = db_to_color( db_avg );
	const uint8_t peak_color = db_peak_to_color( db_peak );
	const int meter_height = 12;

	const uint32_t bar_color_word = color_word( bar_color );
	const uint32_t peak_color_word = color_word( peak_color );
	const uint32_t bg_color_word = color_word( BG_COLOR );

	// Write the meter an entire scan line at a time
	int y;
	for( y=0 ; y<meter_height ; y++, row += pitch/4 )
	{
		uint32_t x;
		for( x=0 ; x<width/4 ; x++ )
		{
			if( x < x_db_avg )
				row[x] = bar_color_word;
			else
			if( x < x_db_peak )
				row[x] = bg_color_word;
			else
			if( x < x_db_peak + 4 )
				row[x] = peak_color_word;
			else
				row[x] = bg_color_word;
		}
	}

	// Write the current level
	bmp_printf( 0, y_origin, "%3d", db_avg );
}


static void
draw_ticks(
	int		y,
	int		tick_height
)
{
	const uint32_t width = bmp_width();
	const uint32_t pitch = bmp_pitch();
	uint32_t * row = (uint32_t*) bmp_vram();
	if( !row )
		return;
	row += (pitch/4) * y;

	const uint32_t white_word = 0
		| ( WHITE_COLOR << 24 )
		| ( WHITE_COLOR << 16 )
		| ( WHITE_COLOR <<  8 )
		| ( WHITE_COLOR <<  0 );

	for( ; tick_height > 0 ; tick_height--, row += pitch/4 )
	{
		int db;
		for( db=-40 * 8; db<= 0 ; db+=5*8 )
		{
			const uint32_t x_db = width + db * 2;
			row[x_db/4] = white_word;
		}
	}
}


/* Normal VU meter */
static void draw_meters(void)
{
	// The db values are multiplied by 8 to make them
	// smoother.
	draw_meter( 0, &audio_levels[0] );
	draw_ticks( 12, 4 );
	draw_meter( 16, &audio_levels[1] );
}

#endif





static void
compute_audio_levels(
	int ch
)
{
	struct audio_level * const level = &audio_levels[ch];

	int raw = audio_read_level( ch );
	if( raw < 0 )
		raw = -raw;

	level->last	= raw;
	level->avg	= (level->avg * 15 + raw) / 16;
	if( raw > level->peak )
		level->peak = raw;

	// Decay the peak to the average
	level->peak = ( level->peak * 31 + level->avg ) / 32;
}


/** Task to monitor the audio levels.
 *
 * Compute the average and peak level, periodically calling
 * the draw_meters() function to display the results on screen.
 * \todo Check that we have live-view enabled and the TFT is on
 * before drawing.
 */
static void
meter_task( void )
{
	DebugMsg( DM_MAGIC, 3, "!!!!! User task is running" );

	msleep( 4000 );

	while(1)
	{
		msleep( 50 );
		draw_meters();
	}
}


TASK_CREATE( "meter_task", meter_task, 0, 0x18, 0x1000 );


/** Monitor the audio levels very quickly */
static void
compute_audio_level_task( void )
{
	msleep( 4000 );
	audio_levels[0].peak = audio_levels[1].peak = 0;
	audio_levels[1].avg = audio_levels[1].avg = 0;

	while(1)
	{
		msleep( 16 );
		compute_audio_levels( 0 );
		compute_audio_levels( 1 );
	}
}

TASK_CREATE( "audio_level_task", compute_audio_level_task, 0, 0x1e, 0x1000 );


/** Write the MGAIN2-0 bits.
 * Table 19 for the gain values:
 *
 *       0 == +0 dB
 *       1 == +20 dB
 *       2 == +26 dB
 *       3 == +32 dB
 *       4 == +10 dB
 *       5 == +17 dB
 *       6 == +23 dB
 *       7 == +29 dB
 *
 * Why is it split between two registers?  I don't know.
 */
static inline void
audio_ic_set_mgain(
	unsigned		bits
)
{
	bits &= 0x7;
	unsigned sig1 = audio_ic_read( AUDIO_IC_SIG1 );
	sig1 &= ~0x3;
	sig1 |= (bits & 1);
	sig1 |= (bits & 4) >> 1;
	audio_ic_write( AUDIO_IC_SIG1 | sig1 );

	unsigned sig2 = audio_ic_read( AUDIO_IC_SIG2 );
	sig2 &= ~(1<<5);
	sig2 |= (bits & 2) << 4;
	audio_ic_write( AUDIO_IC_SIG2 | sig2 );
}


static inline void
audio_ic_set_input_volume(
	int			gain
)
{
	unsigned cmd = ( gain * 1000 ) / 375 + 145;
	cmd &= 0xFF;

	audio_ic_write( AUDIO_IC_IVL | cmd );
	audio_ic_write( AUDIO_IC_IVR | cmd );
}



void
audio_configure( void )
{
	audio_ic_write( AUDIO_IC_PM1 | 0x6D ); // power up ADC and DAC
	audio_ic_write( AUDIO_IC_SIG1 | 0x14 ); // power up, no gain
	audio_ic_write( AUDIO_IC_SIG2 | 0x04 ); // external, no gain
	audio_ic_write( AUDIO_IC_PM3 | 0x07 ); // external input
	audio_ic_write( AUDIO_IC_ALC1 | 0x00 ); // disable all ALC
	//audio_ic_write( AUDIO_IC_ALC1 | 0x24 ); // enable recording ALC

	// Set manual low gain; +30dB == 0xE1
	// gain == (byte - 145) * 0.375
	//const uint32_t gain = 12;
	audio_ic_set_input_volume( audio_dgain );

	// 4 == 10 dB
	// 5 == 17 dB
	// 3 == 32 dB
	audio_ic_set_mgain( audio_mgain ); // 10 dB

	//const uint32_t gain_cmd = (gain * 1000) / 375 + 145;
	//audio_ic_write( AUDIO_IC_IVL | (gain_cmd & 0xFF) );
	//audio_ic_write( AUDIO_IC_IVR | (gain_cmd & 0xFF) );

	// Disable the HPF
	//audio_ic_write( AUDIO_IC_HPF0 | 0x00 );
	//audio_ic_write( AUDIO_IC_HPF1 | 0x00 );
	//audio_ic_write( AUDIO_IC_HPF2 | 0x00 );
	//audio_ic_write( AUDIO_IC_HPF3 | 0x00 );

	// Enable the LPF
	// Canon uses F2A/B = 0x0ED4 and 0x3DA9.
	audio_ic_write( AUDIO_IC_LPF0 | 0xD4 );
	audio_ic_write( AUDIO_IC_LPF1 | 0x0E );
	audio_ic_write( AUDIO_IC_LPF2 | 0xA9 );
	audio_ic_write( AUDIO_IC_LPF3 | 0x3D );
	audio_ic_write( AUDIO_IC_FIL1 | audio_ic_read( AUDIO_IC_FIL1 ) | (1<<5) );

	// Enable loop mode
	uint32_t mode3 = audio_ic_read( AUDIO_IC_MODE3 );
	mode3 |= (1<<6);
	audio_ic_write( AUDIO_IC_MODE3 | mode3 );

	//draw_audio_regs();
	bmp_printf( 500, 400, "Gain %d/%d", audio_mgain, audio_dgain );
	DebugMsg( DM_AUDIO, 3,
		"Gain mgain=%d dgain=%d",
		audio_mgain,
		audio_dgain
	);
}


struct gain_struct
{
	void *			mvr_rec_token;
	struct semaphore *	sem;
};

static struct gain_struct gain = { (void*) 1, (void*) 1 };

static void
handle_mvr_rec_token(
	void *			token
)
{
	gain.mvr_rec_token = token;
}


static void
handle_mvr_rec_property(
	unsigned		property,
	void *			UNUSED( priv ),
	void *			buf,
	unsigned		len
)
{
	const unsigned		mode = *(unsigned*) buf;
	DebugMsg( DM_MAGIC, 3, "mvr_rec_start: %x %x", (unsigned) buf, mode );

	switch( mode )
	{
	case 0:
		// Movie recording stopped;  (fallthrough)
	case 2:
		// Movie recording started
		give_semaphore( gain.sem );
		break;
	case 1:
		// Movie recording about to start?
		break;
	default:
		// Uh?
		break;
	}

	return prop_cleanup( gain.mvr_rec_token, property );
}


/** Replace the sound dev task with our own to disable AGC.
 *
 * This task disables the AGC when the sound device is activated.
 */
void
my_sounddev_task( void )
{
	DebugMsg( DM_AUDIO, 3, "!!!!! %s started sem=%x", __func__, (uint32_t) sounddev.sem_alc );

	gain.sem = create_named_semaphore( "audio_gain", 1 );

	static unsigned mvr_rec_events[] = { PROP_MVR_REC_START, };
	prop_register_slave(
		mvr_rec_events,
		1,
		handle_mvr_rec_property,
		NULL,
		handle_mvr_rec_token
	);

	msleep( 2000 );

	// Fake the sound dev task parameters
	sounddev.sem_alc = create_named_semaphore( 0, 0 );

	sounddev_active_in(0,0);

	// Set defaults
	audio_mgain = config_int( global_config, "audio.mgain", 4 );
	audio_dgain = config_int( global_config, "audio.dgain", 18 );
	int disable_powersave = config_int( global_config, "disable-powersave", 1 );

	while(1)
	{
		msleep( 1500 );
		DebugMsg( DM_MAGIC, 3, "%s: out of sleep", __func__ );

		audio_configure();

		if( disable_powersave )
			prop_request_icu_auto_poweroff( EM_PROHIBIT );

		// will be unlocked by the property handler
		take_semaphore( gain.sem, 0 );
	}
}


TASK_OVERRIDE( sounddev_task, my_sounddev_task );


/** Replace the audio level task with our own.
 *
 * This task runs when the sound device is activated to keep track of
 * the average audio level and translate it to dB.  Nothing ever seems
 * to activate it, so it is commented out for now.
 */
static void
my_audio_level_task( void )
{
	//const uint32_t * const thresholds = (void*) 0xFFC60ABC;
	DebugMsg( DM_AUDIO, 3, "!!!!! %s: Replaced Canon task %x", __func__, audio_level_task );

	audio_in.gain		= -40;
	audio_in.sample_count	= 0;
	audio_in.max_sample	= 0;
	audio_in.sem_interval	= create_named_semaphore( 0, 1 );
	audio_in.sem_task	= create_named_semaphore( 0, 0 );

	while(1)
	{
		DebugMsg( DM_AUDIO, 3, "%s: sleeping init=%d",
			__func__,
			audio_in.initialized
		);

		if( take_semaphore( audio_in.sem_interval, 0 ) & 1 )
		{
			//DebugAssert( "!IS_ERROR", "SoundDevice sem_interval", 0x82 );
			break;
		}

		if( take_semaphore( audio_in.sem_task, 0 ) & 1 )
		{
			//DebugAssert( "!IS_ERROR", SoundDevice", 0x83 );
			break;
		}

		DebugMsg( DM_AUDIO, 3, "%s: awake init=%d\n", __func__, audio_in.initialized );

		if( !audio_in.initialized )
		{
			DebugMsg( DM_AUDIO, 3, "**** %s: agc=%d/%d wind=%d volume=%d",
				__func__,
				audio_in.agc_on,
				audio_in.last_agc_on,
				audio_in.windcut,
				audio_in.volume
			);

			audio_set_filter_off();

			if( audio_in.last_agc_on == 1
			&&  audio_in.agc_on == 0
			)
				audio_set_alc_off();
			
			audio_in.last_agc_on = audio_in.agc_on;
			audio_set_windcut( audio_in.windcut );

			audio_set_sampling_param( 44100, 0x10, 1 );
			audio_set_volume_in(
				audio_in.agc_on,
				audio_in.volume
			);

			if( audio_in.agc_on == 1 )
				audio_set_alc_on();

			audio_in.initialized	= 1;
			audio_in.gain		= -39;
			audio_in.sample_count	= 0;

		}

		if( audio_in.asif_started == 0 )
		{
			DebugMsg( DM_AUDIO, 3, "%s: Starting asif observer", __func__ );
			audio_start_asif_observer();
			audio_in.asif_started = 1;
		}

		//uint32_t level = audio_read_level(0);
		give_semaphore( audio_in.sem_task );

		// Never adjust it!
		//set_audio_agc();
		//if( file != (void*) 0xFFFFFFFF )
			//FIO_WriteFile( file, &level, sizeof(level) );

		// audio_interval_wakeup will unlock our semaphore
		oneshot_timer( 0x200, audio_interval_unlock, audio_interval_unlock, 0 );
	}

	DebugMsg( DM_AUDIO, 3, "!!!!! %s task exited????", __func__ );
}


TASK_OVERRIDE( audio_level_task, my_audio_level_task );

#if 0
static void
dump_task( void )
{
	msleep( 10000 );
	DebugMsg( DM_MAGIC, 3, "Calling dumpf" );
	dumpf();
}


TASK_CREATE( "dump_task", dump_task, 0, 0x1f, 0x1000 );
#endif
