#include <stdio.h>

#include "UI/debounce_ts.h"
#include "UI/user_interface.h"

// helps initialize various components of the program
void initialize(void) {
    // misc
    
    // UI
    user_interface_init();
    debounce_ts_init();

    // DSP
}

int main(void) {
    initialize();
    uint16_t x;
    uint16_t y;
    char button;

    // main loop
    while(1) {
        sleep_ms(150); // replacing with timer later
        
        // tick functions
        debounce_ts_tick();

        // get button press and underline selected button
        debounce_ts_pressed(&x, &y);
        button = which_button(x, y);
        underline_button(button);
    }
    return 1;
}