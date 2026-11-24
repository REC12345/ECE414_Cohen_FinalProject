// code influenced by ECE414_Examples_LafayetteCollege repo

#include "signal_generator.h"

struct repeating_timer timer;

void sine_wave(uint32_t f, uint16_t A, float phi) {
    // generate a sin tookup table
    uint8_t table_size = (uint8_t) 256; // adding (uint8_t) makes an error go away. why???
    int16_t sin_table[table_size];

    for (int i = 0; i < table_size; i++) {
        sin_table[i] = (int16_t)(A*sin((i*2*PI) / table_size + phi)); // not sure if phi is in the right place
    }

    // initialize dac, add repeating timer
    init_dac4822();
    
}

void square_wave(uint32_t f, uint16_t A, float phi, uint8_t n) {

}

void triangle_wave(uint32_t f, uint16_t A, float phi, uint8_t n) {

}