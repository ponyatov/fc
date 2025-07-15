#include "sdram.h"

/// https://en.radzio.dxp.pl/stm32f429idiscovery/sdram.html
void SDRAM_Init(void) {
    uint8_t* s = &_sxram;
    uint8_t* e = &_exram;
    size_t l = e - s;
    uint8_t* x = &_sixram;
    memcpy(s, x, l);
}
