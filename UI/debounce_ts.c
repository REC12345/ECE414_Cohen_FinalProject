#include "debounce_ts.h"

#define X1_SCREEN 200
#define X2_SCREEN 3800
#define X1_LCD 0
#define X2_LCD 319

#define Y1_SCREEN 200
#define Y2_SCREEN 3800
#define Y1_LCD 0
#define Y2_LCD 239

static bool ts_pressed;
static uint16_t px;
static uint16_t py;

static enum DB_States {
    NOPUSH, 
    MAYBEPUSH, 
    PUSHED, 
    MAYBENOPUSH
} DB_State;

void debounce_ts_init() {
    DB_State = NOPUSH;
    ts_pressed = false;
}

// a helper function that returns true true when the touchscreen is pressed.
// assigns db_px, db_py, and db_pz to the position of the press
bool get_press() {
    struct TSPoint p;
    int x;
    int y;
    int z;

    // reads the status of the touchscreen
    getPoint(&p);
    
    // checks if screen is actually being touched
    if (p.z > 500) {
        return false;
    }

    // set position
    px = ((p.x - X1_SCREEN) * (X2_LCD - X1_LCD)) / (X2_SCREEN - X1_SCREEN) + X1_LCD;
    py = ((p.y - Y1_SCREEN) * (Y2_LCD - Y1_LCD)) / (Y2_SCREEN - Y1_SCREEN) + Y1_LCD;
    
    return true;
}

void debounce_ts_tick() {
    bool pressed = get_press();
    switch(DB_State) {
        case NOPUSH:
            if (pressed) DB_State = MAYBEPUSH;
            else DB_State = NOPUSH;
            break;
        case MAYBEPUSH:
            if (pressed) {
                ts_pressed = true;
                DB_State = PUSHED;
            }
            else DB_State = NOPUSH;
            break;
        case PUSHED:
            if (pressed) DB_State = PUSHED;
            else DB_State = MAYBENOPUSH;
            break;
        case MAYBENOPUSH:
            if (pressed) DB_State = PUSHED;
            else DB_State = NOPUSH;
            break;
        default:
            DB_State = NOPUSH;
            break;
    }
}

bool debounce_ts_pressed(uint16_t *xpos, uint16_t *ypos) {
    if (!ts_pressed) return false;
    ts_pressed = false;
    *xpos = px;
    *ypos = py;
    return true;
}