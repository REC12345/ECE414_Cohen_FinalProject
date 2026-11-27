#ifndef DSP_EFFECTS
#define DSP_EFFECTS

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define SAMPLE_RATE_HZ 40000

/*
 * Every effect has the same shape: take one sample in the range -1.0 .. +1.0,
 * return one sample. Settings and memory live in a per-effect struct, so you
 * can have several copies of the same effect with different settings.
 */
typedef float (*effect_fn)(float in, void *state);

typedef struct {
    effect_fn process;
    void *state;
    bool enabled;
} effect_t;

/* Run a sample through each enabled effect, in array order. */
float effects_process(const effect_t *chain, size_t count, float sample);

/* ---- Distortion ---- */
typedef struct {
    float drive;    /* gain before clipping, 1 = mild, 20 = heavy */
    float level;    /* output volume, 0 .. 1 */
} distortion_t;

float distortion_process(float in, void *state);

/* ---- Tremolo (volume wobble) ---- */
typedef struct {
    float rate_hz;  /* wobble speed */
    float depth;    /* 0 = none, 1 = full */
    float phase;    /* internal, start at 0 */
} tremolo_t;

float tremolo_process(float in, void *state);

/* ---- Delay / echo ---- */
typedef struct {
    int16_t *buffer;        /* echo memory that you provide */
    size_t buffer_len;      /* number of samples in buffer */
    size_t delay_samples;   /* 1 .. buffer_len */
    float feedback;         /* 0 .. 0.95, how long echoes repeat */
    float mix;              /* 0 = dry only, 1 = echo only */
    size_t pos;             /* internal, start at 0 */
} delay_fx_t;

float delay_process(float in, void *state);

#endif