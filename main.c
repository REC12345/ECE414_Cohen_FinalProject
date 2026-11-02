#include "UI/debounce_ts.h"
#include "UI/user_interface.h"

// helps initialize various components of the program
void initialize(void) {
    // misc
    
    // UI
    user_interface_init();

    // DSP
}

int main(void) {
    initialize();

    // main loop
    while(1) {
        sleep_ms(100); // replacing with timer later
        debug_display("hello world"); // debugging
    }
    return 1;
}