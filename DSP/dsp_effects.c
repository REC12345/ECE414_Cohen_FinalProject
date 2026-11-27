#include "dsp_effects.h"

static inline float clampf(float x, float lo, float hi)
{
    return x < lo ? lo : (x > hi ? hi : x);
}

float effects_process(const effect_t *chain, size_t count, float sample)
{
    for (size_t i = 0; i < count; i++) {
        if (chain[i].enabled) {
            sample = chain[i].process(sample, chain[i].state);
        }
    }
    return sample;
}

float distortion_process(float in, void *state)
{
    const distortion_t *d = state;
    float x = in * d->drive;

    /* Soft clip: smooth, and much cheaper than tanhf(). */
    float magnitude = x < 0.0f ? -x : x;
    return d->level * (x / (1.0f + magnitude));
}

float tremolo_process(float in, void *state)
{
    tremolo_t *t = state;

    t->phase += t->rate_hz * (1.0f / SAMPLE_RATE_HZ);
    if (t->phase >= 1.0f) {
        t->phase -= 1.0f;
    }

    /* Triangle wave 0 .. 1 (avoids calling sinf() every sample). */
    float lfo = t->phase < 0.5f ? 2.0f * t->phase : 2.0f - 2.0f * t->phase;

    return in * (1.0f - t->depth * lfo);
}

float delay_process(float in, void *state)
{
    delay_fx_t *d = state;

    size_t length = d->delay_samples;
    if (length < 1) length = 1;
    if (length > d->buffer_len) length = d->buffer_len;
    if (d->pos >= length) d->pos = 0;   /* in case length was reduced */

    float echo = d->buffer[d->pos] * (1.0f / 32767.0f);

    float store = clampf(in + echo * d->feedback, -1.0f, 1.0f);
    d->buffer[d->pos] = (int16_t)(store * 32767.0f);

    if (++d->pos >= length) {
        d->pos = 0;
    }

    return in * (1.0f - d->mix) + echo * d->mix;
}