#ifndef SIGNAL_GENERATOR
#define SIGNAL_GENERATOR

#include <math.h>
#include <stdint.h>
#include "pico/stdlib.h"

// NOTE: These functions are NOT meant to have low latency as they are used for testing only


// returns one period of a sine wave of a given frequency (f), amplitude (A), and phase (phi)
uint16_t sine_wave(uint32_t f, uint16_t A, uint8_t phi);

// returns one period of a square wave of a given frequency (f), amplitude (A), phase (phi), and number of harmonics (n)
// generates a square wave by summing various sine waves.
uint16_t square_wave(uint32_t f, uint16_t A, uint8_t phi, uint8_t n);

// returns one period of a triangle wave of a given frequency (f), amplitude (A), phase (phi), and number of odd(?) harmonics (n)
// generates a triangle wave by summing various sine waves.
uint16_t triangle_wave(uint32_t f, uint16_t A, uint8_t phi, uint8_t n);

#endif