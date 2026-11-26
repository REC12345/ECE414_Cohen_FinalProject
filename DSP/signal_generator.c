// code influenced by ECE414_Examples_LafayetteCollege repo

#include "signal_generator.h"
#include "dac4822.h"
#include <math.h>

#define TABLE_SIZE 1024                            // must match the >> 22 below
#define SAMPLE_PERIOD_US 25                        // 40 kHz sample rate
#define SAMPLE_RATE (1000000.0 / SAMPLE_PERIOD_US)
#define NUM_TONES 4                                // number of independent oscillators
#define TAU 6.28318531f                            // equal to 2*pi

static int16_t tables[2][TABLE_SIZE];
static const int16_t * volatile active_table = tables[0];
static float work[TABLE_SIZE];

static volatile uint32_t step[NUM_TONES];      // frequency
static volatile uint32_t offset[NUM_TONES];    // phase shift
static volatile int32_t  level[NUM_TONES];     // amplitude


// -------- helper functions --------
static bool on_sample(repeating_timer_t *rt) {
    static uint32_t phase[NUM_TONES];
    const int16_t *table = active_table;
    int32_t value = 2048;

    for (int k = 0; k < NUM_TONES; k++) {
        uint32_t index = (phase[k] + offset[k]) >> 22;   // 0..1023
        value += (table[index] * level[k]) >> 16;
        phase[k] += step[k];
    }

    if (value < 0) value = 0;
    if (value > 4095) value = 4095;
    write_dac4822(value);
    return true;
}

// amplitude is peak-to-peak (0..4096). Keep the total of all tones <= 4096.
void set_tone(int k, float freq_hz, int amplitude, float phase_deg) {
    if (k < 0 || k >= NUM_TONES) return;
    if (amplitude < 0) amplitude = 0;
    if (amplitude > 4096) amplitude = 4096;
    if (freq_hz < 0.0f) freq_hz = 0.0f;
    if (freq_hz > SAMPLE_RATE / 2) freq_hz = SAMPLE_RATE / 2;

    float turns = phase_deg / 360.0f;
    turns -= floorf(turns);

    step[k]   = (uint32_t)(freq_hz * 4294967296.0 / SAMPLE_RATE);
    offset[k] = (uint32_t)(uint64_t)(turns * 4294967296.0f);
    level[k]  = amplitude;
}

// Scale one cycle to full range, write the spare buffer, then switch to it
static void load_table(const float *wave) {
    float peak = 0.0f;
    for (int i = 0; i < TABLE_SIZE; i++)
        peak = fmaxf(peak, fabsf(wave[i]));
    if (peak == 0.0f) peak = 1.0f;

    int16_t *spare = (active_table == tables[0]) ? tables[1] : tables[0];
    for (int i = 0; i < TABLE_SIZE; i++)
        spare[i] = (int16_t)lroundf(32767.0f * wave[i] / peak);

    __compiler_memory_barrier();               // finish writing before switching
    active_table = spare;
}

typedef struct {
    int   n;           // harmonic number: 1 = fundamental
    float strength;    // relative strength
    float phase_rad;
} harmonic_t;

void load_harmonics(const harmonic_t *h, int count) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        work[i] = 0.0f;
        for (int k = 0; k < count; k++)
            work[i] += h[k].strength *
                       sinf(TAU * h[k].n * i / TABLE_SIZE + h[k].phase_rad);
    }
    load_table(work);
}


// -------- signal generators --------
void sine_wave(uint32_t f, uint16_t A, float phi) {
    // load the sine wave
    const harmonic_t h = {1, 1.0f, 0.0f};
    load_harmonics(&h, 1);

    // play the sine wave
    set_tone(0, f, A, phi);

    absolute_time_t next = get_absolute_time();
    while(1) {
        on_sample(NULL);
        next = delayed_by_us(next, SAMPLE_PERIOD_US);
        busy_wait_until(next);
    }

}

void square_wave(uint32_t f, uint16_t A, float phi, uint8_t n) {

}

void triangle_wave(uint32_t f, uint16_t A, float phi, uint8_t n) {

}