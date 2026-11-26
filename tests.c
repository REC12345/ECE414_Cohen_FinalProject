/**
 * This file contatins various functions that test the functionality of the program.
 * The details and justififications for these tests can be found in the "Software Testing" document
 * 
 */
#include <stdio.h>
#include "pico/stdlib.h"

#include "DSP/dac4822.h"
#include "DSP/signal_generator.h"

// -------- SW1 - TESTING UI --------


// -------- SW2 - TESTING DSP COMPONENTS--------
// -------- SW2.1 - TESTING DAC --------
void SWTEST_DAC_SIMPLE() {
    // WORKS - 12:46PM, 11/26/2026
    stdio_init_all();
    init_dac4822();

    write_dac4822(2048);
    while(1) {
        sleep_ms(100);
        write_dac4822(0);
        sleep_ms(100);
        write_dac4822(2048);
    }
}

void SWTEST_DAC() {
    // WORKS - 2:xx, 11/26/2026
    stdio_init_all();
    init_dac4822();

    // sine wave
    sine_wave(1000, 4096, 0);
    return;
}

// -------- SW2.2 - TESTING ADC --------

// -------- SW2.3 - TESTING DSP --------


// -------- SW3 - INTEGRATION TESTING --------
