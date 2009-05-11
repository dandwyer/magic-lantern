/** \file
 * ARM control registers
 */
#ifndef _arm_mcr_h_
#define _arm_mcr_h_

typedef unsigned long uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

static inline void
select_normal_vectors( void )
{
	uint32_t reg;
	asm(
		"mrc p15, 0, %0, c1, c0\n"
		"bic %0, %0, #0x2000\n"
		"mcr p15, 0, %0, c1, c0\n"
		: "=r"(reg)
	);
}


static inline void
flush_caches( void )
{
	uint32_t reg = 0;
	asm(
		"mcr p15, 0, %0, c7, c5, 0\n" // entire I cache
		"mcr p15, 0, %0, c7, c6, 1\n" // entire D cache
		: : "r"(reg)
	);
}


// This must be a macro
#define setup_memory_region( region, value ) \
	asm __volatile__ ( "mcr p15, 0, %0, c6, c" #region "\n" : : "r"(value) )

#define set_d_cache_regions( value ) \
	asm __volatile__ ( "mcr p15, 0, %0, c2, c0\n" : : "r"(value) )

#define set_i_cache_regions( value ) \
	asm __volatile__ ( "mcr p15, 0, %0, c2, c0, 1\n" : : "r"(value) )

#define set_d_buffer_regions( value ) \
	asm __volatile__ ( "mcr p15, 0, %0, c3, c0\n" : : "r"(value) )

#define set_d_rw_regions( value ) \
	asm __volatile__ ( "mcr p15, 0, %0, c5, c0, 0\n" : : "r"(value) )

#define set_i_rw_regions( value ) \
	asm __volatile__ ( "mcr p15, 0, %0, c5, c0, 1\n" : : "r"(value) )

static inline void
set_control_reg( uint32_t value )
{
	asm __volatile__ ( "mcr p15, 0, %0, c3, c0\n" : : "r"(value) );
}

static inline uint32_t
read_control_reg( void )
{
	uint32_t value;
	asm __volatile__ ( "mrc p15, 0, %0, c3, c0\n" : "=r"(value) );
	return value;
}


static inline void
set_d_tcm( uint32_t value )
{
	asm( "mcr p15, 0, %0, c9, c1, 0\n" : : "r"(value) );
}

static inline void
set_i_tcm( uint32_t value )
{
	asm( "mcr p15, 0, %0, c9, c1, 1\n" : : "r"(value) );
}


/**
 * Some common instructions.
 */
#define RET_INSTR 0xe12fff1e	// bx lr
#define FAR_CALL_INSTR 0xe51ff004	// ldr pc, [pc,#-4]
#define LOOP_INSTR 0xeafffffe	// 1: b 1b

/** Simple boot loader memcpy.
 *
 * \note This is not general purpose; len must be > 0 and must be % 4
 */
static inline void
blob_memcpy(
	void *		dest_v,
	const void *	src_v,
	const void *	end
)
{
	uint32_t *	dest = dest_v;
	const uint32_t * src = src_v;

	while( (void*) src < end )
		*dest++ = *src++;
}

#endif
