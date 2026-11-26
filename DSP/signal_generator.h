#ifndef SIGNAL_GENERATOR
#define SIGNAL_GENERATOR

#include <stdint.h>
#include "pico/stdlib.h"


// NOTE: These functions are NOT meant to have low latency as they are used for testing only

// plays a sine wave of a given frequency (f), amplitude (A), and phase (phi)
void sine_wave(uint32_t f, uint16_t A, float phi);

// plays a square wave of a given frequency (f), amplitude (A), phase (phi), and number of harmonics (n)
// generates a square wave by summing various sine waves.
void square_wave(uint32_t f, uint16_t A, float phi, uint8_t n);

// plays a triangle wave of a given frequency (f), amplitude (A), phase (phi), and number of odd(?) harmonics (n)
// generates a triangle wave by summing various sine waves.
void triangle_wave(uint32_t f, uint16_t A, float phi, uint8_t n);

#endif