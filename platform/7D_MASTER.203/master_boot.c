/** \file
 * Code to run on the camera once it has been relocated.
 *
 * !!!!!! FOR NEW PORTS, READ PROPERTY.C FIRST !!!!!!
 * OTHERWISE YOU CAN CAUSE PERMANENT CAMERA DAMAGE
 * 
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
#include "consts.h"
#include "ml_rpc.h"
#include "cache_hacks.h"

void my_bzero( uint8_t * base, uint32_t size );
int my_init_task(int a, int b, int c, int d);


extern void (*pre_isr_hook)  (uint32_t);
extern uint32_t isr_table_handler[];
extern uint32_t isr_table_param[];

/** Specified by the linker */
extern uint32_t _bss_start[], _bss_end[];

/** Zeroes out bss */
static inline void
zero_bss( void )
{
    uint32_t *bss = _bss_start;
    while( bss < _bss_end )
        *(bss++) = 0;
}


/** Copy firmware to RAM, patch it and restart it */
void
copy_and_restart( int offset )
{
    // Clear bss
    zero_bss();

    /* make sure we have the first segment locked in d/i cache for patching */    
    cache_lock();

    /* patch init code to start our init task instead of canons default */
    cache_fake(HIJACK_CACHE_HACK_INITTASK_ADDR, (uint32_t) &my_init_task, TYPE_DCACHE);

    /* now start main firmware */
    void (*reset)(void) = (void*) ROMBASEADDR;
    reset();

    /* Unreachable */
    while(1);
}


#if defined(CONFIG_AUTOBACKUP_ROM)

#define BACKUP_BLOCKSIZE 0x00100000

void backup_region(char *file, uint32_t base, uint32_t length)
{
    FILE *handle = NULL;
    unsigned int size = 0;
    uint32_t pos = 0;
    
    /* already backed up that region? */
    if((FIO_GetFileSize( file, &size ) == 0) && (size == length) )
    {
        return;
    }
    
    /* no, create file and store data */
    handle = FIO_CreateFileEx(file);
    while(pos < length)
    {
        uint32_t blocksize = BACKUP_BLOCKSIZE;
        
        if(length - pos < blocksize)
        {
            blocksize = length - pos;
        }
        
        FIO_WriteFile(handle, &((uint8_t*)base)[pos], blocksize);
        pos += blocksize;
        
        /* to make sure lower prio tasks can also run */
        msleep(20);
    }
    FIO_CloseFile(handle);
}

void backup_task()
{
    msleep(1000);
    backup_region(CARD_DRIVE "ML/LOGS/ROM1.BIN", 0xF8000000, 0x01000000);
    backup_region(CARD_DRIVE "ML/LOGS/ROM0.BIN", 0xF0000000, 0x01000000);
}
#endif


#define UNCACHEABLE(x) ((void*)(((uint32_t)(x)) | 0x40000000))
#define PTPBUF_BUFS      16
#define PTPBUF_BUFSIZE   256
#define PTPBUF_MAGIC 0xEAEA3388

typedef struct
{
    uint32_t bytes_used;
    uint8_t data[PTPBUF_BUFSIZE];
} ptpbuf_buffer_t;

typedef struct
{
    uint32_t type;
    uint32_t length;
} ptpbuf_packet_t;

typedef struct
{
    uint32_t magic;
    uint32_t buffer_count;
    uint32_t buffer_size;
    uint32_t current_buffer;
    uint32_t overflow;
    ptpbuf_buffer_t *buffers;
    uint32_t *fetchable;
} ptpbuf_t;


ptpbuf_buffer_t ptpbuf_buffers[PTPBUF_BUFS];
uint32_t ptpbuf_fetchable[PTPBUF_BUFS];
ptpbuf_t ptpbuf_data = { PTPBUF_MAGIC, PTPBUF_BUFS, PTPBUF_BUFSIZE, 0, 0, ptpbuf_buffers, ptpbuf_fetchable};

uint32_t get_free_buffer()
{
    ptpbuf_t *ptpbuf = UNCACHEABLE(&ptpbuf_data);
    uint32_t *fetchable = UNCACHEABLE(ptpbuf->fetchable);
    
    /* go through all buffers */
    for(uint32_t buf = 0; buf < ptpbuf->buffer_count; buf++)
    {
        /* check if buffer is free for us */
        if(fetchable[buf] == 0)
        {
            ptpbuf_buffer_t *buffer = UNCACHEABLE(&(ptpbuf->buffers[buf]));
            buffer->bytes_used = 0;
            return buf;
        }
    }
    
    return 0xFFFFFFFF;
}

uint32_t ptpbuf_add(uint32_t type, uint8_t *data, uint32_t length)
{
    ptpbuf_t *ptpbuf = UNCACHEABLE(&ptpbuf_data);
    uint32_t *fetchable = UNCACHEABLE(ptpbuf->fetchable);
    ptpbuf_buffer_t *buffer = UNCACHEABLE(&(ptpbuf->buffers[ptpbuf->current_buffer]));
    ptpbuf_packet_t packet;
    
    /* check for enough space in current buffer */
    if(buffer->bytes_used + sizeof(ptpbuf_packet_t) + length >= ptpbuf->buffer_size)
    {
        /* buffer is full, get next */
        fetchable[ptpbuf->current_buffer] = 1;
        uint32_t next_buffer = get_free_buffer();
        
        if(next_buffer >= ptpbuf->buffer_count)
        {
            /* no free buffers. fail. */
            ptpbuf->overflow = 1;
            return 0;
        }
        
        ptpbuf->overflow = 0;        
        ptpbuf->current_buffer = next_buffer;
        buffer = UNCACHEABLE(&(ptpbuf->buffers[ptpbuf->current_buffer]));
        buffer->bytes_used = 0;
    }
    
    packet.type = type;
    packet.length = length;
    
    /* store packet header */
    memcpy(&(buffer->data[buffer->bytes_used]), &packet, sizeof(ptpbuf_packet_t));
    buffer->bytes_used += sizeof(ptpbuf_packet_t);
    
    /* store data */
    memcpy(&(buffer->data[buffer->bytes_used]), data, length);
    buffer->bytes_used += length;
    
    return 1;
}

#if 1
#include "gdb.h"
uint32_t master_hook_regs[16*4];
uint32_t master_hook_addr = 0;
uint32_t master_hook_addr_last = 0;
uint32_t master_cb_calls = 0;
uint32_t master_cb_calls2 = 0;
uint32_t master_cb_read = 0;
uint32_t master_hook_timer_08 = 0;
uint32_t master_hook_timer_14 = 0;
uint32_t master_hook_timer_3C = 0;
uint32_t master_hook_timer_50 = 0;

void master_callback(breakpoint_t *bkpt)
{
    master_cb_calls++;
    /*
    for(int reg = 0; reg < 16; reg++)
    {
        master_hook_regs[reg] = bkpt->ctx[reg];
    }
    */
    
    /* do stuff when engio write is called */
    if(master_hook_addr == 0xFF931A40)
    {
        uint32_t addr = MEM(bkpt->ctx[4]);
        if(addr == 0xC0F06008)
        {
            master_cb_calls2++;
            if(master_hook_timer_08 != 0)
            {
                MEM(bkpt->ctx[4] + 0x04) = (master_hook_timer_08<<16) | master_hook_timer_08;
            }
            
            char *callstack = gdb_get_callstack(bkpt);
            ptpbuf_add(0x4005, callstack, strlen(callstack));
        }
        if(addr == 0xC0F06014)
        {
            master_cb_calls2++;
            if(master_hook_timer_14 != 0)
            {
                MEM(bkpt->ctx[4] + 0x04) = (master_hook_timer_14<<16) | master_hook_timer_14;
            }
            char *callstack = gdb_get_callstack(bkpt);
            ptpbuf_add(0x4006, callstack, strlen(callstack));
        }
    }
    /* do stuff when SIO3_BufferReceived is called */
    if(master_hook_addr == 0xFF8333A4)
    {
        uint8_t *buffer = bkpt->ctx[0];
        uint32_t size = *(unsigned char*)(bkpt->ctx[0] - 2);

        ptpbuf_add(0x4001, buffer, size);
    }
    
    if(master_hook_addr == 0xFF891494)
    {
        ptpbuf_add(0x4002, bkpt->ctx[6], 64);
    }
    
    if(master_hook_addr == 0xFF826728)
    {
        ptpbuf_add(0x4003, bkpt->ctx, 64);
        ptpbuf_add(0x4004, bkpt->ctx[1], 8);
    }
}
#endif

/*
output:
    0000003a 00004b28 ff812d88 00000000 | 0000000a 00003e0d ff810974 00000000
    00000074 0000049c ff83e31c 00019f08 | 00000052 000001b0 ff8d3a74 00000000
    00000036 00000794 ff8d3b04 00000000 | 00000057 00000001 ff817f80 00000000
    00000051 00011b3e ff8db298 00000000 | 0000002f 00000001 ff83dc94 00019ef8
    00000034 000012b4 ff83d00c 00000001 | 00000064 00000001 ff8d5960 00000000
    00000065 00000002 ff95622c 00000000 | 0000005f 00000002 ff8d40f0 0000000a
    0000006e 00000002 ff8d40f0 0000000b | 0000005b 00000002 ff8d3eb8 00000003
    00000010 00000007 ff8371a4 00000000 | 00000054 00000001 ff8c2b14 00000000


*/
#define MAX_ISR_LOG 8192

typedef struct
{
    uint32_t isr_id;
    uint32_t count;
    uint32_t handler;
    uint32_t param;
} isrlog_t;

isrlog_t master_isr_log[MAX_ISR_LOG];

int locate_isr_entry(uint32_t isr_id)
{
    for(uint32_t pos = 0; pos < MAX_ISR_LOG; pos++)
    {
        if(master_isr_log[pos].isr_id == 0 || master_isr_log[pos].isr_id == isr_id)
        {
            return pos;
        }
    }
    return 0;
}

void isrlog(uint32_t isr_id)
{
    uint32_t pos = 0;
    
    pos = locate_isr_entry(isr_id);
    
    master_isr_log[pos].isr_id = isr_id;
    master_isr_log[pos].handler = isr_table_handler[isr_id];
    master_isr_log[pos].param = isr_table_param[isr_id];
    master_isr_log[pos].count++;
    
    clean_d_cache();
}


void ml_init()
{
    ml_rpc_init();
    
    //pre_isr_hook = isrlog;
    
    //cache_fake(0xFF88BCB4, 0xE3A01002, TYPE_ICACHE); /* flush video buffer every frame */
    //cache_fake(0xFF8C7C18, 0xE3A01001, TYPE_ICACHE); /* all-I */
    //cache_fake(0xFF8C7C18, 0xE3A01004, TYPE_ICACHE); /* GOP4 */
    //cache_fake(0xFF8CD448, 0xE3A00006, TYPE_ICACHE); /* deblock alpha set to 6 */
    //cache_fake(0xFF8CD44C, 0xE3A00106, TYPE_ICACHE); /* deblock beta set to 6 */
   
#if 0
    breakpoint_t *bp = NULL;
    msleep(100);
    
    cache_lock();
    gdb_setup();
    
    /* hook engio writes */
    master_hook_addr = 0xFF931A40;
    /* hook SIO3 packets */
    //master_hook_addr = 0xFF8333A4;
    
    //master_hook_addr = 0xFF891494;
    //master_hook_addr = 0xFF826728;
    
    while(1)
    {
        msleep(100);
        if(master_hook_addr != master_hook_addr_last)
        {
            if(bp != NULL)
            {
                gdb_delete_bkpt(bp);
            }
            master_cb_calls = 0;
            bp = gdb_add_watchpoint(master_hook_addr, 0, &master_callback);
            master_hook_addr_last = master_hook_addr;
        }
    }
#endif
}



/** Initial task setup.
 *
 * This is called instead of the task at 0xFF811DBC.
 * It does all of the stuff to bring up the debug manager,
 * the terminal drivers, stdio, stdlib and armlib.
 */
int
my_init_task(int a, int b, int c, int d)
{
    extern int master_init_task( int a, int b, int c, int d );
    cache_fake(HIJACK_CACHE_HACK_BSS_END_ADDR, HIJACK_CACHE_HACK_BSS_END_INSTR, TYPE_ICACHE);
        
    int ans = init_task(a,b,c,d);
    
    task_create("ml_init", 0x18, 0x4000, &ml_init, 0 );    
    
#if defined(CONFIG_AUTOBACKUP_ROM)
    /* backup ROM first time to be prepared if anything goes wrong. choose low prio */
    task_create("ml_backup", 0x1f, 0x4000, backup_task, 0 );
#endif

    return ans;
}

