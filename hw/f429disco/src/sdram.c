#include "sdram.h"

uint8_t hello[] __attribute__((section(".xram"))) = "Hello XRAM";

/// https://en.radzio.dxp.pl/stm32f429idiscovery/sdram.html
void SDRAM_Init(void) {
    __IO uint32_t tmp = 0x00;

    /* (re)Enable GPIOD..GPIOG, /GPIOH /GPIOI interface clock */
    tmp = RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN |
          RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOHEN | RCC_AHB1ENR_GPIOIEN;
    RCC->AHB1ENR |= tmp;  // 0x000001F8;
    /* Delay after an RCC peripheral clock enabling */
    tmp = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);

    /* Enable the FMC interface clock */
    RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;  // 0x00000001
    /* Delay after an RCC peripheral clock enabling */
    tmp = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);

    // FMC_Bank5_6->SDCR[0] = 0x000019E4;
    // Column Address Bits (NC = 9)  (typical for 512 columns) (A0-A8)
    // Row Address Bits (NR = 12)  (typical for 4096 rows) (A0-A11)
    // Data Bus Width (MWID = 16-bit) IS42S16400J, MT48LC4M32B2
    // Internal Banks (NB = 4) 4 internal banks (standard for most SDRAMs)
    // CAS Latency (CAS = 2 cycles) read delay set to 2 clock cycles
    // Write Protection (WP = Disabled)
    // Read Pipeline Delay (RPIPE = 0) No additional delays for read operations
    // RBSZ Reserved (must be 0)
    FMC_Bank5_6->SDCR[0] =
        FMC_SDCR1_SDCLK_1 | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE_1;
    // FMC_SDCR1_SDCLK_1 SDCLK = 10 2 clock cycles delay (IS42S16400J 160 MHz
    // max) FMC_SDCR1_RBURST Enables burst read operations (need check for
    // speed) FMC_SDCR1_RPIPE_1 +clock cycle delay to improve timing (need
    // check)

    /* Configure and enable SDRAM bank2 @ 0xD0000000 */
    FMC_Bank5_6->SDCR[1] =
        FMC_SDCR1_NR_0 | FMC_SDCR1_MWID_0 | FMC_SDCR1_NB | FMC_SDCR1_CAS;
    // Number of Row Address Bits NR = 01 → 12 row bits
    // Memory Data Bus Width MWID = 01 → 16-bit bus
    // Number of Internal Banks (NB=1) 4 internal banks
    // CAS Latency (CAS=11) =3

    // FMC_Bank5_6->SDTR[0] = 0x01115351;
    // TRMD = 1 Load Mode Register to Active Delay = 2 cycles
    // TXSR = 5 Exit Self-Refresh Delay = 6 cycles
    // TRAS = 3 Self-Refresh Time = 4 cycles
    // TRC  = 5 Row Cycle Delay = 6 cycles
    // TWR  = 1 Write Recovery Time = 2 cycles
    // TRP  = 1 Row Precharge Delay = 2 cycles
    // TRCD = 5 Row-to-Column Delay = 6 cycles

    // Initialization step 2
    // FMC_Bank5_6->SDTR[0] = TRC(7) | TRP(2);
    FMC_Bank5_6->SDTR[0] = (7 << FMC_SDTR1_TRC_Pos) | (2 << FMC_SDTR1_TRP_Pos);

    // FMC_Bank5_6->SDTR[1] = TMRD(2) | TXSR(7) | TRAS(4) | TWR(2) |
    // TRCD(2);

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
