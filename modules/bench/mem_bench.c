/* this is included directly in bench.c */

/* optional routines */
extern WEAK_FUNC(ret_0) void* dma_memcpy(void* dest, void* srce, size_t n);
extern WEAK_FUNC(ret_0) void* edmac_memcpy(void* dest, void* srce, size_t n);
extern WEAK_FUNC(ret_0) void* edmac_copy_rectangle_adv(void* dst, void* src, int src_width, int src_x, int src_y, int dst_width, int dst_x, int dst_y, int w, int h);

#define HAS_DMA_MEMCPY ((void*)&dma_memcpy != (void*)&ret_0)
#define HAS_EDMAC_MEMCPY ((void*)&edmac_memcpy != (void*)&ret_0)

static void mem_benchmark_fill(uint32_t *dst, uint32_t *src, int size)
{
    for (int i = 0; i < size/4; i++)
    {
        src[i] = rand();
    }
    
    memset(dst, 0, size);
}

static void mem_benchmark_check(void *dst, void *src, int size, int x, int y)
{
    sync_caches();
    
    int color_fg = COLOR_WHITE;
    char *msg = "OK";

    if (memcmp(src, dst, size) != 0)
    {
        msg = "ERR!";
        color_fg = COLOR_RED;

        /* save the source and destination buffers, for debugging */
        dump_seg(src, size, "ML/LOGS/benchsrc.bin");
        dump_seg(dst, size, "ML/LOGS/benchdst.bin");
    }

    bmp_printf(
        FONT(FONT_MONO_20, color_fg, COLOR_BLACK) | FONT_ALIGN_RIGHT,
        x, y, msg
    );
}

static uint64_t FAST DUMP_ASM mem_test_read64(uint64_t *buf, uint32_t n)
{
    register uint64_t tmp = 0;
    for (uint32_t i = 0; i < n/8; i++)
        tmp += buf[i];
    return tmp;
}

static uint32_t FAST DUMP_ASM mem_test_read32(uint32_t *buf, uint32_t n)
{
    register uint32_t tmp = 0;
    for (uint32_t i = 0; i < n/4; i++)
        tmp += buf[i];
    return tmp;
}

// A set of wrapper functions to work with mem_benchmark_fun().
// That expects a uint32_t (*)(int, int, int, int), and casting
// random functions would be undefined behaviour.
static uint32_t memcpy_wrapper(intptr_t dst, intptr_t src, int count, int unused)
{
    return (uint32_t)memcpy((void *)dst, (const void *)src, (size_t)count);
}

static uint32_t memcpy64_wrapper(intptr_t dst, intptr_t src, int count, int unused)
{
    return (uint32_t)memcpy64((void *)dst, (void *)src, (size_t)count);
}

static uint32_t dma_memcpy_wrapper(intptr_t dst, intptr_t src, int count, int unused)
{
    return (uint32_t)dma_memcpy((void *)dst, (void *)src, (size_t)count);
}

static uint32_t edmac_memcpy_wrapper(intptr_t dst, intptr_t src, int count, int unused)
{
    return (uint32_t)edmac_memcpy((void *)dst, (void *)src, (size_t)count);
}

static uint32_t memset_wrapper(intptr_t dst, int ch, int count, int unused)
{
    return (uint32_t)memset((void *)dst, ch, (size_t)count);
}

static uint32_t memset64_wrapper(intptr_t dst, int ch, int count, int unused)
{
    return (uint32_t)memset64((void *)dst, ch, (size_t)count);
}

static uint32_t mem_test_read32_wrapper(intptr_t buf, int n, int unused1, int unused2)
{
    return mem_test_read32((uint32_t *)buf, (uint32_t)n);
}

static uint32_t mem_test_read64_wrapper(intptr_t buf, int n, int unused1, int unused2)
{
    return mem_test_read64((uint64_t *)buf, (uint32_t)n);
}

typedef uint32_t (*mem_bench_fun)(
    int arg0,
    int arg1,
    int arg2,
    int arg3
);

static void mem_benchmark_run(char *msg, int *y, int bufsize,
                              mem_bench_fun bench_fun,
                              int arg0, int arg1, int arg2, int arg3,
                              int is_memcpy, int test_length)
{
    bmp_fill(COLOR_BLACK, 0, 0, 720, font_large.height);
    bmp_printf(FONT_LARGE, 0, 0, "%s", msg);

    uint32_t speeds[2];

    for (int display = 1; display >= 0; display--)
    {
        if (!display && (msg[0] == 'e' || msg[0] == 'b'))
        {
            /* EDMAC and BMP tests crash with display off */
            speeds[display] = 0;
            continue;
        }
        
        if (display)
        {
            display_on();
        }
        else
        {
            bmp_printf(FONT_LARGE, 0, 0, "%s (display off)", msg);
            msleep(250);
            display_off();
        }
        msleep(200);

        int times = 0;
        int t0m = get_ms_clock();
        uint64_t t0 = get_us_clock();
        uint32_t res = 0;
        for (int i = 0; i < INT_MAX; i++)
        {
            if (i % 2)
                info_led_off();
            else
                info_led_on();

            // we accumulate the result to avoid gcc optimising away
            // the benchmark function body
            res += bench_fun(arg0, arg1, arg2, arg3);

            /* run the benchmark for specified time */
            if (get_ms_clock() - t0m > test_length)
            {
                times = i + 1;
                break;
            }
        }
        uint64_t t1 = get_us_clock();
        DryosDebugMsg(0, 1, "Meaningless test result: %d", res);

        uint64_t dt = t1 - t0;

        info_led_off();

        /* units: KB/s */
        // float cast is to avoid int overflow, which can happen even with uint64_t
        uint64_t speed = ((float)bufsize * times * 1000000) / dt / 1024;

        /* transform in MB/s x100 */
        speeds[display] = speed * 100 / 1024;
    }

    if (speeds[0])
    {
        bmp_printf(FONT_MONO_20, 0, 100, "Test function:          Display on:    Display off:         ");
        bmp_printf(FONT_MONO_20, 0, *y += 20, "%s   %d.%02d MB/s   %d.%02d MB/s          ",
                   msg, speeds[1]/100, speeds[1]%100, speeds[0]/100, speeds[0]%100);
    }
    else
    {
        bmp_printf(FONT_MONO_20, 0, *y += 20, "%s   %d.%02d MB/s     (test skipped)       ",
                   msg, speeds[1]/100, speeds[1]%100);
    }
    DryosDebugMsg(0, 15, "%s %d.%02d MB/s %d.%02d MB/s",
                  msg, speeds[1]/100, speeds[1]%100, speeds[0]/100, speeds[0]%100);

    display_on();

    if (is_memcpy)
    {
        /* perform an extra call, just for checking whether the copying is done correctly */
        /* assume memcpy-like syntax: (dst, src, size) */
        info_led_on();
        bmp_printf(FONT_LARGE, 0, 0, "%s (verifying)      ", msg);
        bmp_printf(FONT_MONO_20 | FONT_ALIGN_RIGHT, 720, *y, SYM_DOTS);
        mem_benchmark_fill((void*)arg0, (void*)arg1, arg2);
        bench_fun(arg0, arg1, arg2, arg3);
        mem_benchmark_check((void*)arg0, (void*)arg1, arg2, 720, *y);
        info_led_off();
    }

    msleep(100);
}

static uint32_t mem_test_bmp_fill(int arg0, int arg1, int arg2, int arg3)
{
    bmp_draw_to_idle(1);
    bmp_fill(COLOR_BLACK, arg0, arg1, arg2, arg3);
    bmp_draw_to_idle(0);
    return 0;
}

static uint32_t mem_test_edmac_copy_rectangle(int arg0, int arg1, int arg2, int arg3)
{
    uint8_t *real = BMP_VRAM_START(bmp_vram_real());
    uint8_t *idle = BMP_VRAM_START(bmp_vram_idle());

    /* careful - do not mix cacheable and uncacheable pointers unless you know what you are doing */
    return (uint32_t)edmac_copy_rectangle_adv(UNCACHEABLE(idle), UNCACHEABLE(real), 960, 0, 0, 960, 0, 0, 720, 480);
}

static void mem_benchmark_simple_task()
{
    // A simple, fast test, to indicate highest speed possible
    // for different copy subsystems
    //
    // memcpy: DryOS memcpy
    // memcpy64: ML memcpy64 in stdio.c
    // dma_memcpy: DryOS dma_memcpy
    // DMA unit
    // EDMAC unit

    msleep(500);

    if (!lv)
    {
        /* run the benchmark in either LV on PLAY mode */
        /* (photo mode is not very interesting) */
        enter_play_mode();
    }

    canon_gui_disable_front_buffer();
    clrscr();
    print_benchmark_header();

    int bufsize = 1*1024*1024;

    void *buf1, *raw_buf1 = NULL;
    void *buf2, *raw_buf2 = NULL;
    uint32_t align = 0x1000;
    raw_buf1 = fio_malloc(bufsize + align);
    raw_buf2 = fio_malloc(bufsize + align);

    // these casts are ugly and kind of dumb, uint32_t * should always
    // be aligned to sizeof(uint32_t) but whatever
    buf1 = raw_buf1;
    if ((uint32_t)raw_buf1 % align != 0)
        buf1 = (void *)((uint32_t)raw_buf1 + (align - (uint32_t)raw_buf1 % align));
    buf2 = raw_buf2;
    if ((uint32_t)raw_buf2 % align != 0)
        buf2 = (void *)((uint32_t)raw_buf2 + (align - (uint32_t)raw_buf2 % align));

    if (!buf1 || !buf2)
    {
        bmp_printf(FONT_LARGE, 0, 0, "malloc error :(");
        goto cleanup;
    }
    DryosDebugMsg(0, 15, "r_buf1, r_buf2: 0x%x, 0x%x", raw_buf1, raw_buf2);
    DryosDebugMsg(0, 15, "buf1, buf2:     0x%x, 0x%x", buf1, buf2);

    int y = 100;

    mem_benchmark_run("memcpy                   ", &y, bufsize, memcpy_wrapper,
                      (intptr_t)CACHEABLE(buf1), (intptr_t)CACHEABLE(buf2), bufsize, 0, 1, 250);
    mem_benchmark_run("memcpy64                 ", &y, bufsize, memcpy64_wrapper,
                      (intptr_t)CACHEABLE(buf1),   (intptr_t)CACHEABLE(buf2), bufsize, 0, 1, 250);

    if (HAS_DMA_MEMCPY)
    {
        mem_benchmark_run("dma_memcpy, unc, align   ", &y, bufsize, dma_memcpy_wrapper,
                          (intptr_t)UNCACHEABLE(buf1), (intptr_t)UNCACHEABLE(buf2), bufsize, 0, 1, 250);
        mem_benchmark_run("dma_memcpy, cac, align   ", &y, bufsize, dma_memcpy_wrapper,
                          (intptr_t)CACHEABLE(buf1), (intptr_t)CACHEABLE(buf2), bufsize, 0, 1, 250);
        mem_benchmark_run("dma_memcpy, unc, unalign ", &y, bufsize, dma_memcpy_wrapper,
                          (intptr_t)UNCACHEABLE(raw_buf1), (intptr_t)UNCACHEABLE(raw_buf2), bufsize, 0, 1, 250);
        mem_benchmark_run("dma_memcpy, cac, unalign ", &y, bufsize, dma_memcpy_wrapper,
                          (intptr_t)CACHEABLE(raw_buf1), (intptr_t)CACHEABLE(raw_buf2), bufsize, 0, 1, 250);
    }

    if (HAS_EDMAC_MEMCPY)
    {
        mem_benchmark_run("edmac_memcpy             ", &y, bufsize, edmac_memcpy_wrapper,
                          (intptr_t)UNCACHEABLE(buf1), (intptr_t)UNCACHEABLE(buf2), bufsize, 0, 1, 250);
        mem_benchmark_run("edmac_copy_rectangle     ", &y, 720*480, (mem_bench_fun)mem_test_edmac_copy_rectangle,
                          0, 0, 0, 0, 0, 250);
    }

    bmp_fill(COLOR_BLACK, 0, 0, 720, font_large.height);
    bmp_printf(FONT_LARGE, 0, 0, "Benchmark complete.");

    take_screenshot("bench%d.ppm", SCREENSHOT_BMP);
    msleep(1500);
    canon_gui_enable_front_buffer(0);

cleanup:
    if (raw_buf1)
        free(raw_buf1);
    if (raw_buf2)
        free(raw_buf2);
}

static void mem_benchmark_task()
{
    msleep(1000);
    
    if (!lv)
    {
        /* run the benchmark in either LV on PLAY mode */
        /* (photo mode is not very interesting) */
        enter_play_mode();
    }
    
    canon_gui_disable_front_buffer();
    clrscr();
    print_benchmark_header();

    int bufsize = 16*1024*1024;

    void* buf1 = 0;
    void* buf2 = 0;
    buf1 = fio_malloc(bufsize);
    buf2 = fio_malloc(bufsize);
    if (!buf1 || !buf2)
    {
        bmp_printf(FONT_LARGE, 0, 0, "malloc error :(");
        goto cleanup;
    }

    int y = 100;

#if 0 // need to hack the source code to run this benchmark
    extern int defish_ind;
    defish_draw_lv_color();
    void defish_draw_lv_color_loop(uint64_t* src_buf, uint64_t* dst_buf, int* ind);
    if (defish_ind)
    mem_benchmark_run("defish_draw_lv_color", &y, 720*os.y_ex, (mem_bench_fun)defish_draw_lv_color_loop, (intptr_t)UNCACHEABLE(buf1), (intptr_t)UNCACHEABLE(buf2), defish_ind, 0, 0);
#endif

    mem_benchmark_run("memcpy cacheable    ", &y, bufsize, memcpy_wrapper,
                      (intptr_t)CACHEABLE(buf1), (intptr_t)CACHEABLE(buf2), bufsize, 0, 1, 250);
    mem_benchmark_run("memcpy uncacheable  ", &y, bufsize, memcpy_wrapper,
                      (intptr_t)UNCACHEABLE(buf1), (intptr_t)UNCACHEABLE(buf2), bufsize, 0, 1, 250);
    mem_benchmark_run("memcpy64 cacheable  ", &y, bufsize, memcpy64_wrapper,
                      (intptr_t)CACHEABLE(buf1),   (intptr_t)CACHEABLE(buf2), bufsize, 0, 1, 250);
    mem_benchmark_run("memcpy64 uncacheable", &y, bufsize, memcpy64_wrapper,
                      (intptr_t)UNCACHEABLE(buf1), (intptr_t)UNCACHEABLE(buf2), bufsize, 0, 1, 250);
    
    if (HAS_DMA_MEMCPY)
    {
        mem_benchmark_run("dma_memcpy cacheable", &y, bufsize, dma_memcpy_wrapper,
                          (intptr_t)CACHEABLE(buf1), (intptr_t)CACHEABLE(buf2), bufsize, 0, 1, 250);
        mem_benchmark_run("dma_memcpy uncacheab", &y, bufsize, dma_memcpy_wrapper,
                          (intptr_t)UNCACHEABLE(buf1), (intptr_t)UNCACHEABLE(buf2), bufsize, 0, 1, 250);
    }
    
    if (HAS_EDMAC_MEMCPY)
    {
        mem_benchmark_run("edmac_memcpy        ", &y, bufsize, edmac_memcpy_wrapper,
                          (intptr_t)UNCACHEABLE(buf1), (intptr_t)UNCACHEABLE(buf2), bufsize, 0, 1, 250);
        mem_benchmark_run("edmac_copy_rectangle", &y, 720*480, (mem_bench_fun)mem_test_edmac_copy_rectangle,
                          0, 0, 0, 0, 0, 1000);
    }
    
    mem_benchmark_run("memset cacheable    ", &y, bufsize, memset_wrapper,
                      (intptr_t)CACHEABLE(buf1), 0, bufsize, 0, 0, 250);
    mem_benchmark_run("memset uncacheable  ", &y, bufsize, memset_wrapper,
                      (intptr_t)UNCACHEABLE(buf1), 0, bufsize, 0, 0, 250);
    mem_benchmark_run("memset64 cacheable  ", &y, bufsize, memset64_wrapper,
                      (intptr_t)CACHEABLE(buf1), 0, bufsize, 0, 0, 250);
    mem_benchmark_run("memset64 uncacheable", &y, bufsize, memset64_wrapper,
                      (intptr_t)UNCACHEABLE(buf1), 0, bufsize, 0, 0, 250);
    mem_benchmark_run("read32 cacheable    ", &y, bufsize, mem_test_read32_wrapper,
                      (intptr_t)CACHEABLE(buf1),   bufsize, 0, 0, 0, 250);
    mem_benchmark_run("read32 uncacheable  ", &y, bufsize, mem_test_read32_wrapper,
                      (intptr_t)UNCACHEABLE(buf1), bufsize, 0, 0, 0, 250);
    mem_benchmark_run("read64 cacheable    ", &y, bufsize, mem_test_read64_wrapper,
                      (intptr_t)CACHEABLE(buf1),   bufsize, 0, 0, 0, 250);
    mem_benchmark_run("read64 uncacheable  ", &y, bufsize, mem_test_read64_wrapper,
                      (intptr_t)UNCACHEABLE(buf1), bufsize, 0, 0, 0, 250);
    if (get_digic_version() < 6)
    {
        // On modern cams, FEATURE_VRAM_RGBA, there's no idle buffer,
        // so this fill would erase the benchmark result before the screenshot.
        mem_benchmark_run("bmp_fill to idle buf", &y, 720*480, mem_test_bmp_fill,
                          0, 0, 720, 480, 0, 250);
    }

    bmp_fill(COLOR_BLACK, 0, 0, 720, font_large.height);
    bmp_printf(FONT_LARGE, 0, 0, "Benchmark complete.");

    take_screenshot("bench%d.bmp", SCREENSHOT_BMP);
    msleep(3000);
    canon_gui_enable_front_buffer(0);

cleanup:
    if (buf1)
        free(buf1);
    if (buf2)
        free(buf2);
}
