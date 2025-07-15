#include "sdram.h"

uint8_t hello[] __attribute__((section(".xram"))) = "Hello XRAM";

/// https://en.radzio.dxp.pl/stm32f429idiscovery/sdram.html
void SDRAM_Init(void) {
    __IO uint32_t tmp = 0x00;

    /* (re)Enable GPIOD..GPIOG, /GPIOH /GPIOI interface clock */
    tmp = RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN |
          RCC_AHB1ENR_GPIOGEN;  // RCC_AHB1ENR_GPIOHEN | RCC_AHB1ENR_GPIOIEN;
    RCC->AHB1ENR |= tmp;        // 0x000001F8;
    /* Delay after an RCC peripheral clock enabling */
    tmp = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);

    /* Enable the FMC interface clock */
    RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;  // 0x00000001
    /* Delay after an RCC peripheral clock enabling */
    tmp = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);

    // // Initialization step 1
    // FMC_Bank5_6->SDCR[0] =
    //     FMC_SDCR1_SDCLK_1 | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE_1;
    // FMC_Bank5_6->SDCR[1] =
    //     FMC_SDCR1_NR_0 | FMC_SDCR1_MWID_0 | FMC_SDCR1_NB | FMC_SDCR1_CAS;
    // // Initialization step 2
    // FMC_Bank5_6->SDTR[0] = TRC(7) | TRP(2);
    // FMC_Bank5_6->SDTR[1] = TMRD(2) | TXSR(7) | TRAS(4) | TWR(2) | TRCD(2);
    // // Initialization step 3
    // while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)
    //     ;
    // FMC_Bank5_6->SDCMR = 1 | FMC_SDCMR_CTB2 | (1 << 5);
    // // Initialization step 4
    // for (int tmp = 0; tmp < 1000000; tmp++)
    //     ;
    // // Initialization step 5
    // while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)
    //     ;
    // FMC_Bank5_6->SDCMR = 2 | FMC_SDCMR_CTB2 | (1 << 5);
    // // Initialization step 6
    // while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)
    //     ;
    // FMC_Bank5_6->SDCMR = 3 | FMC_SDCMR_CTB2 | (4 << 5);
    // // Initialization step 7
    // while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)
    //     ;
    // FMC_Bank5_6->SDCMR = 4 | FMC_SDCMR_CTB2 | (1 << 5) | (0x231 << 9);
    // // Initialization step 8
    // while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)
    //     ;
    // FMC_Bank5_6->SDRTR |= (683 << 1);
    // while (FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)
    //     ;
    (void)(tmp);

    uint8_t* s = &_sxram;
    uint8_t* e = &_exram;
    size_t l = e - s;
    uint8_t* x = &_sixram;
    memcpy(s, x, l);
}
