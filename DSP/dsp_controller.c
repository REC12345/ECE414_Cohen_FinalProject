#include "dsp_controller.h"

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "dac4822.h"
#include "dsp_effects.h"

#define ADC_GPIO     28          /* GPIO28 = ADC input 2 */
#define ADC_INPUT    2
#define ADC_CLOCK_HZ 48000000
#define MIDSCALE     2048.0f

/* ---------------- Effect settings: edit these ---------------- */

static distortion_t distortion = { .drive = 5.0f, .level = 0.8f };
static tremolo_t    tremolo    = { .rate_hz = 5.0f, .depth = 0.6f };
/* 1 second of echo memory = 80 KB of RAM. */
static int16_t      echo_memory[SAMPLE_RATE_HZ];
static delay_fx_t   echo       = {
    .buffer = echo_memory,
    .buffer_len = SAMPLE_RATE_HZ,
    .delay_samples = SAMPLE_RATE_HZ * 3 / 10,   /* 300 ms */
    .feedback = 0.4f,
    .mix = 0.35f,
};

/* Signal flows top to bottom. All disabled = clean passthrough. */
static effect_t chain[] = {
    { distortion_process, &distortion, false },
    { tremolo_process,    &tremolo,    false },
    { delay_process,      &echo,       false },
};

#define CHAIN_LENGTH (sizeof chain / sizeof chain[0])

/* ------------------------------------------------------------- */

static void adc_start(void)
{
    adc_init();
    adc_gpio_init(ADC_GPIO);
    adc_select_input(ADC_INPUT);

    /* Put each result in the FIFO; no DMA, keep full 12 bits. */
    adc_fifo_setup(true, false, 1, false, false);

    /* The ADC hardware sets the sample rate: one sample every
     * (1 + clkdiv) cycles of its 48 MHz clock. */
    adc_set_clkdiv((float)ADC_CLOCK_HZ / SAMPLE_RATE_HZ - 1.0f);

    adc_run(true);
}

/* Raw ADC code (0..4095) -> float (-1..+1), with the DC bias removed. */
static inline float adc_to_float(uint16_t raw)
{
    static float dc = MIDSCALE;
    dc += 0.001f * ((float)raw - dc);   /* tracks bias, ~6 Hz high-pass */
    return ((float)raw - dc) * (1.0f / MIDSCALE);
}

/* Float (-1..+1) -> DAC code (0..4095), clipping anything out of range. */
static inline uint16_t float_to_dac(float x)
{
    int32_t code = (int32_t)(x * MIDSCALE + MIDSCALE);
    if (code < 0)    code = 0;
    if (code > 4095) code = 4095;
    return (uint16_t)code;
}

void dsp_start() {
    adc_start();
    init_dac4822();

    while (true) {
        uint16_t raw = adc_fifo_get_blocking();   /* waits for next sample */

        float sample = adc_to_float(raw);
        sample = effects_process(chain, CHAIN_LENGTH, sample);
        write_dac4822(float_to_dac(sample));
    }
}