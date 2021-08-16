/*
 *  77D 1.0.2 consts
 */

#define CARD_LED_ADDRESS            0xD208016C
#define LEDON                       0x20D0002
#define LEDOFF                      0x20C0003

#define HIJACK_FIXBR_DCACHE_CLN_1   0xe0040058   /* first call to dcache_clean, before cstart */
#define HIJACK_FIXBR_ICACHE_INV_1   0xe0040062   /* first call to icache_invalidate, before cstart */
#define HIJACK_FIXBR_DCACHE_CLN_2   0xe0040090   /* second call to dcache_clean, before cstart */
#define HIJACK_FIXBR_ICACHE_INV_2   0xe004009a   /* second call to icache_invalidate, before cstart */
#define HIJACK_INSTR_BL_CSTART      0xe00400b0   /* easier to fix up here */
#define HIJACK_FIXBR_BZERO32        0xe004013a   /* called from cstart */
#define HIJACK_FIXBR_CREATE_ITASK   0xe004019c   /* called from cstart */
#define HIJACK_INSTR_MY_ITASK       0xe00401cc   /* address of init_task passed to create_init_task */

#define PTR_USER_MEM_SIZE           0xe00401c0   /* easier to patch the size; start address is computed */

#define PTR_SYS_OFFSET              0xe00401b8   // offset from DryOS base to sys_mem start
#define PTR_SYS_OBJS_OFFSET         0xe00401c4   // offset from DryOS base to sys_obj start
#define PTR_DRYOS_BASE              0xe00401a4
#define ML_MAX_USER_MEM_STOLEN 0x40000 // True max differs per cam, 0x40000 has been tested on
                                       // the widest range of D678 cams with no observed problems,
                                       // but not all cams have been tested!

#define ML_MAX_SYS_MEM_INCREASE 0x40000 // More may be VERY unsafe!  Increasing this pushes sys_mem
                                        // higher in memory, at some point that must cause Bad Things,
                                        // consequences unknown.  0x40000 has been tested, a little...

#define ML_RESERVED_MEM 0x66000 // Can be lower than ML_MAX_USER_MEM_STOLEN + ML_MAX_SYS_MEM_INCREASE,
                                // but must not be higher; sys_objs would get overwritten by ML code.
                                // Must be larger than MemSiz reported by build for magiclantern.bin

/*
Before patching:
DryOS base    user_start                       sys_objs_start    sys_start
    |-------------|--------------------------------|---------------|--------------------->
                   <-------  user_mem_size ------->                 <---- sys_len ------->
    ---------------- sys_objs_offset ------------->
    ---------------- sys_mem_offset ------------------------------>

After patching, user mem reduced and sys mem moved up
DryOS base    user_start                                 sys_objs_start    sys_start
    |-------------|-------------------|<-- ml_reserved_mem -->|---------------|--------------------->
                   <- user_mem_size ->                                         <---- sys_len ------->
    ---------------- sys_objs_offset ------------------------>
    ---------------- sys_mem_offset ----------------------------------------->
*/

#if ML_RESERVED_MEM > ML_MAX_USER_MEM_STOLEN + ML_MAX_SYS_MEM_INCREASE
#error "ML_RESERVED_MEM too big to fit!"
#endif

#define XIMR_CONTEXT 0xa0fa4
