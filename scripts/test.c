/*
@title PicoC testing script
@param a Misc small tests
@range a 0 1
@param b Expo settings tests
@range b 0 1
@param c Powersave tests
@range c 0 1
@param d Movie recording tests
@range d 0 1
@param e Picture taking tests
@range e 0 1
@param f Focus tests
@range f 0 1
*/

printf("PicoC testing...\n");

if (a) // misc tests
{
    /* Some basic functions */
    beep();
    sleep(2);

    printf("LiveView:%d Recording:%d\n", lv, recording);

    /* Date/time  */
    struct tm * t = get_time();
    printf("Time: %02d:%02d:%02d\n", t->hour, t->minute, t->second);
    printf("Date: %02d/%02d/%02d\n", t->year, t->month, t->day);

    /* Some math */
    float pi = 3.14;
    float twopi = 2 * pi;
    printf("2*pi = %f\n", twopi);
    printf("some float values: %f %f %f %f %f %f %f %f %f %f %f %f \n", 0.0000001, 0.001, 0.123, 10000, 200000, 300000000, 5433546.45262432, 5.450267432, 0, 42, 555555.5555555, 1.0/0.0 );

    /* Dumping memory */
    for (unsigned addr = 0xFF010000; addr < 0xFF010010; addr += 4)
        printf("%x: %x\n", addr, *(int*)addr);

    /* Key press test */
    sleep(2);
    console_hide();
    click(MENU);
    sleep(1);
    click(RIGHT);
    sleep(1);
    click(MENU);
    sleep(1);
    console_show();
    
    printf("Press any key to continue.\n");
    get_key();
}

if (b) // expo tests
{
    /* Exposure settings test (read/write) */
    printf("ISO %d 1/%f f/%f\n", get_iso(), 1/get_shutter(), get_aperture());
    printf("Sv%f Tv%f Av%f\n", get_sv(), get_tv(), get_av());
    printf("Raw ISO %d shutter %d aperture %d\n \n", get_rawiso(), get_rawshutter(), get_rawaperture());
    sleep(2);

    printf("setting ISO 200 1/2000 f/2.8...\n");
    set_iso(200);
    set_shutter(1./2000);
    set_aperture(2.8);
    printf(" => got ISO %d 1/%f f/%f\n\n", get_iso(), 1/get_shutter(), get_aperture());
    sleep(2);

    printf("setting ISO 400 1/128 f/11 (APEX)...\n");
    set_tv(7);
    set_sv(7);
    set_av(7);
    printf(" => got ISO %d 1/%f f/%f\n\n", get_iso(), 1/get_shutter(), get_aperture());
    sleep(2);

    printf("setting ISO 200 1/32 f/8 (raw units)...\n");
    set_rawiso(80);
    set_rawshutter(96);
    set_rawaperture(56);
    printf(" => got ISO %d 1/%f f/%f\n\n", get_iso(), 1/get_shutter(), get_aperture());
    sleep(2);

    /* AE tests */
    printf("AE: %d; flash AE: %d\n", get_ae(), get_flash_ae());
    set_ae(1);
    set_flash_ae(-2);

    /* Let's go into LiveView */
    if (!lv) { click(LV); sleep(1); }

    /* Kelvin tests */
    int kelvin_0 = get_kelvin();
    printf("White balance: %d K, %d G/M\n", get_kelvin(), get_green());
    set_green(0);
    printf("Kelvin from 2000 to 10000...\n");
    sleep(1);
    console_hide();
    sleep(2);
    for (int k = 2000; k < 10000; k += 50)
    {
        set_kelvin(k);
        sleep(0.01);
    }
    sleep(1);
    set_kelvin(kelvin_0);
    console_show();
    
    printf("Press any key to continue.\n");
    get_key();
}

if (c) // powersave tests
{
    /* Let's go into LiveView */
    if (!lv) { click(LV); sleep(1); }

    /* Powersave tests */
    printf("Display off... ");
    sleep(1);
    display_off();
    sleep(2);
    display_on();
    sleep(2);
    printf("and back on.\n");

    sleep(1);

    printf("LiveView paused... ");
    sleep(1);
    lv_pause();
    sleep(2);
    lv_resume();
    sleep(2);
    printf("and resumed.\n");

    console_show();
    printf("Press any key to continue.\n");
    get_key();
}

if (d) // movie test
{
    /* Movie recording test */
    sleep(1);
    printf("Recording... ");
    movie_start();
    sleep(3);
    movie_end();
    printf("done.\n");
    sleep(1);

    console_show();
    printf("Press any key to continue.\n");
    get_key();
}

if (e) // photo tests
{
    /* Picture taking test */
    int n = 2;
    for (int i = 0; i < n; i++)
    {
        printf("Taking pic %d of %d...\n", i+1, n);
        sleep(1);
        takepic();
    }

    printf("Taking bulb picture...\n");
    sleep(1);
    bulbpic(2.5);

    console_show();
    printf("Press any key to continue.\n");
    get_key();
}


if (f) // focus tests
{
    /* Lens focusing test */

    /* We need LiveView */
    if (!lv) { click(LV); sleep(1); }
    
    focus_setup(3, 200, 1); // step size 3, delay 200ms, wait
    
    printf("5 steps forward...\n");
    focus(5);

    printf("and 5 steps backward...\n");
    focus(-5);

    printf("Done.\n");
    console_show();
    printf("Press any key to continue.\n");
    get_key();
}

printf("Done :)\n");

