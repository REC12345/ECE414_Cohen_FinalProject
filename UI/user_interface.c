#include "user_interface.h"

#define BLACK 0x0000
#define DARKGREY 0x7BEF
#define WHITE 0xFFFF

// constants for basic ui
#define BUTTON_WIDTH 95
#define BUTTON_HEIGHT 95
#define BUTTON_SPACING 10
#define BUTTON_RADIUS 10
#define TEXT_SIZE 4

// a helper function that displays the basic user interface on the screen
void basic_ui() {
    // effect button A
    tft_fillRoundRect(
        BUTTON_SPACING, BUTTON_SPACING,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        BUTTON_RADIUS, DARKGREY
    );
    tft_drawChar(
        (BUTTON_WIDTH / 2) + BUTTON_SPACING - 2*TEXT_SIZE, 
        (BUTTON_HEIGHT / 2) + BUTTON_SPACING - 2*TEXT_SIZE,
        'A', BLACK, DARKGREY, TEXT_SIZE
    );
    
    // effect button B
    tft_fillRoundRect(
        BUTTON_SPACING, 2*BUTTON_SPACING + BUTTON_HEIGHT,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        BUTTON_RADIUS, DARKGREY
    );
    tft_drawChar(
        (BUTTON_WIDTH / 2) + BUTTON_SPACING - 2*TEXT_SIZE, 
        ((2*BUTTON_SPACING + BUTTON_HEIGHT)) + (BUTTON_HEIGHT / 2) - 2*TEXT_SIZE,
        'B', BLACK, DARKGREY, TEXT_SIZE
    );
    
    // effect button C
    tft_fillRoundRect(
        BUTTON_SPACING, 3*BUTTON_SPACING + 2*BUTTON_HEIGHT,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        BUTTON_RADIUS, DARKGREY
    );
    tft_drawChar(
        (BUTTON_WIDTH / 2) + BUTTON_SPACING - 2*TEXT_SIZE, 
        ((3*BUTTON_SPACING + 2*BUTTON_HEIGHT)) + (BUTTON_HEIGHT / 2) - 2*TEXT_SIZE,
        'C', BLACK, DARKGREY, TEXT_SIZE
    );
}

void user_interface_init() {
    adc_init();
    tft_init_hw();
    tft_begin();

    tft_fillScreen(BLACK);
    basic_ui();
}

char which_button(uint16_t x, uint16_t y) {
    // check buttons
    if (x >= BUTTON_SPACING && x <= BUTTON_SPACING + BUTTON_WIDTH) {
        if (y >= 20 && y <= 80) {
            return 'A';
        } else if (y >= 90 && y <= 150) {
            return 'B';
        } else if (y >= 160 && y <= 220) {
            return 'C';
        }
    }

    // return '/0' if no button pressed
    return 'n';
}

void underline_button(char button) {
    int a_color = BLACK;
    int b_color = BLACK;
    int c_color = BLACK;

    if (button == 'A') {
        a_color = WHITE;
    } else if (button == 'B') {
        b_color = WHITE;
    } else if (button == 'C') {
        c_color = WHITE;
    }

    // A
    tft_drawFastVLine(
        BUTTON_WIDTH + BUTTON_SPACING + 5, BUTTON_SPACING,
        BUTTON_WIDTH, a_color
    );

    // B
    tft_drawFastVLine(
        BUTTON_WIDTH + BUTTON_SPACING + 5, 2*BUTTON_SPACING + BUTTON_HEIGHT, 
        BUTTON_WIDTH, b_color
    ); 

    // C
    tft_drawFastVLine(
        BUTTON_WIDTH + BUTTON_SPACING + 5, 3*BUTTON_SPACING + 2*BUTTON_HEIGHT,
        BUTTON_WIDTH, c_color
    ); 

    return;
}

void debug_display(char* message) {
    // clear previous result
    tft_fillRect(115, 100, 100, 100, BLACK);

    // display new result
    tft_setCursor(115, 100);
    tft_setTextColor(WHITE);
    tft_setTextSize(3);
    tft_setTextWrap(false);
    tft_writeString(message);
}