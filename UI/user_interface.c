#include "user_interface.h"

#define BLACK 0x0000
#define DARKGREY 0x7BEF
#define WHITE 0xFFFF

// constants for basic ui
#define BUTTON_WIDTH 95
#define BUTTON_HEIGHT 95
#define BUTTON_SPACING 10
#define BUTTON_RADIUS 10

// a helper function that displays the basic user interface on the screen
void basic_ui() {
    // effect button one
    tft_fillRoundRect(
        BUTTON_SPACING, BUTTON_SPACING,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        BUTTON_RADIUS, DARKGREY
    );

    // effect button two
    tft_fillRoundRect(
        BUTTON_SPACING, 2*BUTTON_SPACING + BUTTON_HEIGHT,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        BUTTON_RADIUS, DARKGREY
    );

    // effect button three
    tft_fillRoundRect(
        BUTTON_SPACING, 3*BUTTON_SPACING + 2*BUTTON_HEIGHT,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        BUTTON_RADIUS, DARKGREY
    );
}

void user_interface_init() {
    adc_init();
    tft_init_hw();
    tft_begin();

    tft_fillScreen(BLACK);
    basic_ui();
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