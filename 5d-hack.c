/** \file
 * Code to run on the 5D once it has been relocated.
 *
 * This has been updated to work with the 2.0.3 firmware.
 * IT DOES NOT WORK WITH 1.1.0 NOR 1.0.7 ANY MORE!
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
#include "config.h"
#include "version.h"
#include "bmp.h"
#include "menu.h"
#include "version.h"
#include "property.h"

/** If CONFIG_EARLY_PORT is defined, only a few things will be enabled */
#undef CONFIG_EARLY_PORT

/** These are called when new tasks are created */
void my_task_dispatch_hook( struct context ** );
void my_init_task(void);
void my_bzero( uint8_t * base, uint32_t size );

/** This just goes into the bss */
#define RELOCSIZE 0x10000
static uint8_t _reloc[ RELOCSIZE ];
#define RELOCADDR ((uintptr_t) _reloc)

/** Translate a firmware address into a relocated address */
#define INSTR( addr ) ( *(uint32_t*)( (addr) - ROMBASEADDR + RELOCADDR ) )

/** Fix a branch instruction in the relocated firmware image */
#define FIXUP_BRANCH( rom_addr, dest_addr ) \
	INSTR( rom_addr ) = BL_INSTR( &INSTR( rom_addr ), (dest_addr) )

/** Was this an autoboot or firmware file load? */
int autoboot_loaded;


/** Specified by the linker */
extern uint32_t _bss_start[], _bss_end[];

static inline void
zero_bss( void )
{
	uint32_t *bss = _bss_start;
	while( bss < _bss_end )
		*(bss++) = 0;
}


void
__attribute__((noreturn,noinline,naked))
copy_and_restart( int offset )
{
	zero_bss();

	// Set the flag if this was an autoboot load
	autoboot_loaded = (offset == 0);

	// Copy the firmware to somewhere safe in memory
	const uint8_t * const firmware_start = (void*) ROMBASEADDR;
	const uint32_t firmware_len = RELOCSIZE;
	uint32_t * const new_image = (void*) RELOCADDR;

	blob_memcpy( new_image, firmware_start, firmware_start + firmware_len );

	/*
	 * in entry2() (0xff010134) make this change to
	 * return to our code before calling cstart().
	 * This should be a "BL cstart" instruction.
	 */
	INSTR( 0xFF01019C ) = RET_INSTR;


	/*
	 * in cstart() (0xff010ff4) make these changes:
	 * calls bzero(), then loads bs_end and calls
	 * create_init_task
	 */
	// Reserve memory after the BSS for our application
	INSTR( 0xFF01109C ) = (uintptr_t) _bss_end;

	// Fix the calls to bzero32() and create_init_task()
	FIXUP_BRANCH( 0xFF011004, bzero32 );
	FIXUP_BRANCH( 0xFF01108C, create_init_task );

	// Set our init task to run instead of the firmware one
	INSTR( 0xFF0110A8 ) = (uint32_t) my_init_task;

	// Make sure that our self-modifying code clears the cache
	clean_d_cache();
	flush_caches();

	// We enter after the signature, avoiding the
	// relocation jump that is at the head of the data
	thunk reloc_entry = (thunk)( RELOCADDR + 0xC );
	reloc_entry();

	/*
	* We're back!
	* The RAM copy of the firmware startup has:
	* 1. Poked the DMA engine with what ever it does
	* 2. Copied the rw_data segment to 0x1900 through 0x20740
	* 3. Zeroed the BSS from 0x20740 through 0x47550
	* 4. Copied the interrupt handlers to 0x0
	* 5. Copied irq 4 to 0x480.
	* 6. Installed the stack pointers for CPSR mode D2 and D3
	* (we are still in D3, with a %sp of 0x1000)
	* 7. Returned to us.
	*
	* Now is our chance to fix any data segment things, or
	* install our own handlers.
	*/

#ifndef CONFIG_EARLY_PORT
	// Install our task creation hooks
	task_dispatch_hook = my_task_dispatch_hook;
#endif

	// This will jump into the RAM version of the firmware,
	// but the last branch instruction at the end of this
	// has been modified to jump into the ROM version
	// instead.
	void (*ram_cstart)(void) = (void*) &INSTR( cstart );
	ram_cstart();

	// Unreachable
	while(1)
		;
}


#ifndef CONFIG_EARLY_PORT

void
null_task( void )
{
	DebugMsg( DM_SYS, 3, "%s created (and exiting)", __func__ );
	return;
}

/**
 * Called by DryOS when it is dispatching (or creating?)
 * a new task.
 */
void
my_task_dispatch_hook(
	struct context **	context
)
{
	if( !context )
		return;
	
	// Do nothing unless a new task is starting via the trampoile
	if( (*context)->pc != (uint32_t) task_trampoline )
		return;
	
	// Determine the task address
	struct task * const task = *(struct task**) 0x1a20;

	thunk entry = (thunk) task->entry;

	// Search the task_mappings array for a matching entry point
	extern struct task_mapping _task_overrides_start[];
	extern struct task_mapping _task_overrides_end[];
	const struct task_mapping * mapping = _task_overrides_start;

	for( ; mapping < _task_overrides_end ; mapping++ )
	{
		thunk original_entry = mapping->orig;
		if( original_entry != entry )
			continue;

/* -- can't call debugmsg from this context */
#if 0
		DebugMsg( DM_SYS, 3, "***** Replacing task %x with %x",
			original_entry,
			mapping->replacement
		);
#endif

		task->entry = mapping->replacement;
		break;
	}
}


/** First task after a fresh rebuild.
 *
 * Try to dump the debug log after ten seconds.
 * This requires the create_task(), dmstart(), msleep() and dumpf()
 * routines to have been found.
 */
void
my_dump_task( void )
{
	dmstart();

	msleep( 10000 );
	dispcheck();

	dumpf();
	dmstop();
}


struct config * global_config;

static void
call_init_funcs( void * priv )
{
	// Call all of the init functions
	extern struct task_create _init_funcs_start[];
	extern struct task_create _init_funcs_end[];
	struct task_create * init_func = _init_funcs_start;

	for( ; init_func < _init_funcs_end ; init_func++ )
	{
		DebugMsg( DM_MAGIC, 3,
			"Calling init_func %s (%x)",
			init_func->name,
			(unsigned) init_func->entry
		);

		thunk entry = (thunk) init_func->entry;
		entry();
	}
}

#endif // !CONFIG_EARLY_PORT


static void nop( void ) { }
void menu_init( void ) __attribute__((weak,alias("nop")));
void debug_init( void ) __attribute__((weak,alias("nop")));

int magic_off = 0;
int magic_is_off() 
{
	return magic_off; 
}


#ifndef CONFIG_EARLY_PORT

static void *
prop_startup_handler(
	unsigned property,
	void * token,
	void * arg,
	unsigned len
)
{
	uint32_t * const buf = arg;

	if (buf[0] != 0xFF) // shutdown maybe?
	{
		return prop_cleanup( token, property );
	}

	bmp_printf( FONT(FONT_LARGE, COLOR_WHITE, COLOR_BLACK), 100, 100,
		"Magic Lantern for 550D \n"
		"Loading, please wait...\n"
	);

	menu_init();
	debug_init();
	display_clock();

	// Parse our config file
	config_parse_file( "B:/magic.cfg" );


	// INIT_FUNC's
	call_init_funcs( 0 );

	// Create all of our auto-create tasks
	extern struct task_create _tasks_start[];
	extern struct task_create _tasks_end[];
	struct task_create * task = _tasks_start;

	for( ; task < _tasks_end ; task++ )
	{
		task_create(
			task->name,
			task->priority,
			task->flags,
			task->entry,
			task->arg
		);
	}

	return prop_cleanup( token, property );
}

static struct prop_handler prop_startup = {
	.handler	= prop_startup_handler,
	.property	= PROP_TERMINATE_SHUT_REQ,
};

#endif // !CONFIG_EARLY_PORT


/** Initial task setup.
 *
 * This is called instead of the task at 0xFF811DBC.
 * It does all of the stuff to bring up the debug manager,
 * the terminal drivers, stdio, stdlib and armlib.
 */
void
my_init_task(void)
{
	// Call their init task
	init_task();

#ifndef CONFIG_EARLY_PORT
	// Overwrite the PTPCOM message
	dm_names[ DM_MAGIC ] = "[MAGIC] ";
	//~ dmstart(); // already called by firmware?

	DebugMsg( DM_MAGIC, 3, "Magic Lantern %s (%s)",
		build_version,
		build_id
	);

	DebugMsg( DM_MAGIC, 3, "Built on %s by %s",
		build_date,
		build_user
	);
#endif

	// Re-write the version string.
	// Don't use strcpy() so that this can be done
	// before strcpy() or memcpy() are located.
	extern char additional_version[];
	additional_version[0] = '-';
	additional_version[1] = 'm';
	additional_version[2] = 'l';
	additional_version[3] = '-';
	additional_version[4] = build_version[0];
	additional_version[5] = build_version[1];
	additional_version[6] = build_version[2];
	additional_version[7] = build_version[3];
	additional_version[8] = build_version[4];
	additional_version[9] = build_version[5];
	additional_version[10] = build_version[6];
	additional_version[11] = build_version[7];
	additional_version[12] = build_version[8];
	additional_version[13] = '\0';

#ifndef CONFIG_EARLY_PORT

	msleep( 1000 );

	magic_off = FOCUS_CONFIRMATION_AF_PRESSED ? 1 : 0;
	if (magic_off)
	{
		bmp_printf(FONT_LARGE, 0, 0, "Magic OFF");
		additional_version[0] = '-';
		additional_version[1] = 'm';
		additional_version[2] = 'l';
		additional_version[3] = '-';
		additional_version[4] = 'o';
		additional_version[5] = 'f';
		additional_version[6] = 'f';
		additional_version[7] = '\0';
		return;
	}
	
	msleep(5000);
	bmp_printf(FONT_LARGE, 0, 0, "acu-i acu");
	msleep(1000);

	prop_handler_init( &prop_startup );
#endif // !CONFIG_EARLY_PORT
}
