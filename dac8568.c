#include "dac8568.h"

#define DAC8568_INTREF_EN       0x090a0000
#define DAC8568_PWUP_ALLCHN     (0x4 << 24) | 0xff
#define DAC8568_SWRST           (0x7 << 24)

#define DAC8568_UPDATE          (0x3 << 24)

void dac8568_sendCommand(uint32_t cmd)
{
    
    uint8_t buf[4];
    buf[0] = cmd >> 24;
    buf[1] = cmd >> 16;
    buf[2] = cmd >> 8;
    buf[3] = cmd & 0xff;
    NRF_LOG_HEXDUMP_INFO(buf, 4);
    spi_transfer(buf, 4, NULL, 0);
}

void dac8568_begin(void)
{
    spi_init();
    
    //dac8568_sendCommand(DAC8568_SWRST);
    //
    dac8568_sendCommand(DAC8568_INTREF_EN);
    dac8568_sendCommand(DAC8568_PWUP_ALLCHN);
}

void dac8568_setChannel(uint8_t chn, uint16_t val)
{
    uint32_t reg = DAC8568_UPDATE;
    reg |= (val << 4);
    reg |= (chn << 20);
    
    dac8568_sendCommand(reg);
    
}
