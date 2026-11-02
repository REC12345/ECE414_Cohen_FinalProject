#ifndef USER_INTERFACE
#define USER_INTERFACE

#include "TFTMaster.h"
#include "TouchScreen.h"

// initialize the touchscreen, draw the background for the display
void user_interface_init();

// for debugging only: display text on the screen
void debug_display(char *message);

#endif