/**
 * This file contatins various functions that test the functionality of the program.
 * The details and justififications for these tests can be found in the "Software Testing" document
 * 
 */

#include "DSP/dac4822.h"
#include "DSP/signal_generator.h"

// -------- SW1 - TESTING UI --------


// -------- SW2 - TESTING DSP COMPONENTS--------
// -------- SW2.1 - TESTING DAC --------
void SWTEST_DAC() {
    sine_wave(440, 1024, 0);
}

// -------- SW2.2 - TESTING ADC --------

// -------- SW2.3 - TESTING DSP --------


// -------- SW3 - INTEGRATION TESTING --------
