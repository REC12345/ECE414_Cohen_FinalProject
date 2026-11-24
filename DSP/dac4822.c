// code taken from ECE414_Examples_LafayetteCollege repo

#include "dac4822.h"

// DAC parameters (see the DAC datasheet)
// important --> bit 13 = 1 (set gain=1x)
#define DAC_config_chan_A 0b0011000000000000 // A-channel, 1x, active
#define DAC_config_chan_B 0b1011000000000000 // B-channel, 1x, active (should probably be set inactive)

//SPI configurations (GPIO numbers, *not* pin numbers!)
#define PIN_MISO 4
#define PIN_CS   5
#define PIN_SCK  6
#define PIN_MOSI 7
#define SPI_PORT 0 //spi0

void init_dac4822() {
    // Initialize SPI channel (channel, baud rate set to 20MHz)
    spi_init(SPI_PORT, 20000000);
    // Format (channel, data bits per transfer, polarity, phase, order)
    spi_set_format(SPI_PORT, 16, 0, 0, 0);

    // Map SPI signals to GPIO ports
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS, GPIO_FUNC_SPI) ;
}

void write_dac4822(uint16_t val)
{
    uint16_t DAC_data_1;
    // Mask with DAC control bits
    DAC_data_1 = (DAC_config_chan_A | (val & 0xffff));

    // SPI write (no spinlock b/c of SPI buffer)
    spi_write16_blocking(SPI_PORT, &DAC_data_1, 1);
}