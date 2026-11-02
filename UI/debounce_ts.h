#ifndef DEBOUNCE_TS
#define DEBOUNCE_TS

#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TFTMaster.h"
#include "TouchScreen.h"

// initializes the debounce module
void debounce_ts_init();

// tick function for the debounce state machine
void debounce_ts_tick();

// returns true if pressed, maps given variables to the coordinates of the press
bool debounce_ts_pressed(uint16_t *xpos, uint16_t *ypos);

#endif