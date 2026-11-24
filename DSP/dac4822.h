#ifndef DAC4822
#define DAC4822

#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h" // probably should uncomment this ???

// initializes the dac
void init_dac4822();

// writes the given value to the dac
void write_dac4822(uint16_t val);

#endif