#include "user_interface.h"

#define BLACK 0x0000
#define WHITE 0xFFFF

void user_interface_init() {
    adc_init();
    tft_init_hw();
    tft_begin();

    tft_fillScreen(BLACK);
}

void debug_display(char* message) {
    // clear previous result
    tft_fillRect(100, 100, 100, 100, BLACK);

    // display new result
    tft_setCursor(100, 100);
    tft_setTextColor(WHITE);
    tft_setTextSize(3);
    tft_setTextWrap(false);
    tft_writeString(message);
}