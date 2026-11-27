#ifndef ADC_CONTROL
#define ADC_CONTROL

#include <stdint.h>

// initializes various components of the ADC
// assumes adc_init() has already been called
void init_adc_control();

// returns the value of the input signal
uint16_t read_adc_value();

#endif