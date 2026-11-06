#ifndef USER_INTERFACE
#define USER_INTERFACE

#include "TFTMaster.h"
#include "TouchScreen.h"

// initialize the touchscreen, draw the background for the display
void user_interface_init();

// returns the button corresponding to the given coordinates
char which_button(uint16_t x, uint16_t y);

// underlines the selected button
void underline_button(char button);

// for debugging only: display text on the screen
void debug_display(char *message);

#endif