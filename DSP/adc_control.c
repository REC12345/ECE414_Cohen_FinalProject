#include "adc_control.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define CH2_PIN 28 // ADC2 (pin 34 on the pico)
#define CH2 2

void init_adc_control() {
    adc_gpio_init(CH2_PIN);
}

uint16_t read_adc_value() {
    adc_select_input(CH2);
    return adc_read();
}