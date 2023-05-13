/******************************************************************************//**
 * @file     periph_conf.c
 * @version  V1.01
 * @brief    M251 peripheral configuration file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#include "scale_v1.h"

void FMC_Init()
{

    /* Enable FMC ISP function */
    FMC_Open();

    /* Config update enable */
    FMC_EnableConfigUpdate();

}
/*--------------------------------------------------------------------------------------------*/
/* GPIO                                                                                     */
/*--------------------------------------------------------------------------------------------*/
void GPIO_Init()
{
    const uint32_t u32RegDefault = 0;

    //GPIO_PA mode
    PA->MODE =

        (0x1UL << GPIO_MODE_MODE3_Pos) |

        (0x1UL << GPIO_MODE_MODE4_Pos) |

        (0x1UL << GPIO_MODE_MODE5_Pos) |

        (0x1UL << GPIO_MODE_MODE6_Pos) |

        (0x1UL << GPIO_MODE_MODE7_Pos) |

        (0x0UL << GPIO_MODE_MODE12_Pos) |

        u32RegDefault;

    //GPIO_PA disable digital input path
    PA->DINOFF =

        (0 << GPIO_DINOFF_DINOFF3_Pos) |

        (0 << GPIO_DINOFF_DINOFF4_Pos) |

        (0 << GPIO_DINOFF_DINOFF5_Pos) |

        (0 << GPIO_DINOFF_DINOFF6_Pos) |

        (0 << GPIO_DINOFF_DINOFF7_Pos) |

        (0 << GPIO_DINOFF_DINOFF12_Pos) |

        u32RegDefault;

    //GPIO_PA out data
    PA->DOUT =

        (1 << GPIO_DOUT_DOUT3_Pos) |

        (1 << GPIO_DOUT_DOUT4_Pos) |

        (1 << GPIO_DOUT_DOUT5_Pos) |

        (1 << GPIO_DOUT_DOUT6_Pos) |

        (1 << GPIO_DOUT_DOUT7_Pos) |

        (1 << GPIO_DOUT_DOUT12_Pos) |

        u32RegDefault;

    //GPIO_PA DOUT mask
    PA->DATMSK =

        (0 << GPIO_DATMSK_DATMSK3_Pos) |

        (0 << GPIO_DATMSK_DATMSK4_Pos) |

        (0 << GPIO_DATMSK_DATMSK5_Pos) |

        (0 << GPIO_DATMSK_DATMSK6_Pos) |

        (0 << GPIO_DATMSK_DATMSK7_Pos) |

        (0 << GPIO_DATMSK_DATMSK12_Pos) |

        u32RegDefault;

    //GPIO_PA enable de-bounce
    PA->DBEN =

        (0 << GPIO_DBEN_DBEN3_Pos) |

        (0 << GPIO_DBEN_DBEN4_Pos) |

        (0 << GPIO_DBEN_DBEN5_Pos) |

        (0 << GPIO_DBEN_DBEN6_Pos) |

        (0 << GPIO_DBEN_DBEN7_Pos) |

        (0 << GPIO_DBEN_DBEN12_Pos) |

        u32RegDefault;

    //GPIO_PA edge or level interrupt
    PA->INTTYPE =

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE3_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE4_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE5_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE6_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE7_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE12_Pos) |

        u32RegDefault;

    //GPIO_PA enable falling(edge) or low(level) interrupt
    PA->INTEN =

        (0 << GPIO_INTEN_FLIEN3_Pos) |

        (0 << GPIO_INTEN_FLIEN4_Pos) |

        (0 << GPIO_INTEN_FLIEN5_Pos) |

        (0 << GPIO_INTEN_FLIEN6_Pos) |

        (0 << GPIO_INTEN_FLIEN7_Pos) |

        (0 << GPIO_INTEN_FLIEN12_Pos) |

        u32RegDefault;

    //GPIO_PA enable rising(edge) or high(level) interrupt
    PA->INTEN |=

        (0 << GPIO_INTEN_RHIEN3_Pos) |

        (0 << GPIO_INTEN_RHIEN4_Pos) |

        (0 << GPIO_INTEN_RHIEN5_Pos) |

        (0 << GPIO_INTEN_RHIEN6_Pos) |

        (0 << GPIO_INTEN_RHIEN7_Pos) |

        (0 << GPIO_INTEN_RHIEN12_Pos) |

        u32RegDefault;

    //GPIO_PA slew rate
    PA->SLEWCTL =

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN3_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN4_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN5_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN6_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN7_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN12_Pos) |

        u32RegDefault;

    //GPIO_PA pull-up or pull-down
    PA->PUSEL =

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL3_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL4_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL5_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL6_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL7_Pos) |

        (GPIO_PUSEL_PULL_DOWN << GPIO_PUSEL_PUSEL12_Pos) |

        u32RegDefault;

    //GPIO_PB mode
    PB->MODE =

        (0x1UL << GPIO_MODE_MODE2_Pos) |

        (0x1UL << GPIO_MODE_MODE4_Pos) |

        (0x1UL << GPIO_MODE_MODE5_Pos) |

        (0x1UL << GPIO_MODE_MODE7_Pos) |

        (0x1UL << GPIO_MODE_MODE8_Pos) |

        (0x1UL << GPIO_MODE_MODE9_Pos) |

        u32RegDefault;

    //GPIO_PB disable digital input path
    PB->DINOFF =

        (0 << GPIO_DINOFF_DINOFF2_Pos) |

        (0 << GPIO_DINOFF_DINOFF4_Pos) |

        (0 << GPIO_DINOFF_DINOFF5_Pos) |

        (0 << GPIO_DINOFF_DINOFF7_Pos) |

        (0 << GPIO_DINOFF_DINOFF8_Pos) |

        (0 << GPIO_DINOFF_DINOFF9_Pos) |

        u32RegDefault;

    //GPIO_PB out data
    PB->DOUT =

        (1 << GPIO_DOUT_DOUT2_Pos) |

        (1 << GPIO_DOUT_DOUT4_Pos) |

        (1 << GPIO_DOUT_DOUT5_Pos) |

        (1 << GPIO_DOUT_DOUT7_Pos) |

        (1 << GPIO_DOUT_DOUT8_Pos) |

        (1 << GPIO_DOUT_DOUT9_Pos) |

        u32RegDefault;

    //GPIO_PB DOUT mask
    PB->DATMSK =

        (0 << GPIO_DATMSK_DATMSK2_Pos) |

        (0 << GPIO_DATMSK_DATMSK4_Pos) |

        (0 << GPIO_DATMSK_DATMSK5_Pos) |

        (0 << GPIO_DATMSK_DATMSK7_Pos) |

        (0 << GPIO_DATMSK_DATMSK8_Pos) |

        (0 << GPIO_DATMSK_DATMSK9_Pos) |

        u32RegDefault;

    //GPIO_PB enable de-bounce
    PB->DBEN =

        (0 << GPIO_DBEN_DBEN2_Pos) |

        (0 << GPIO_DBEN_DBEN4_Pos) |

        (0 << GPIO_DBEN_DBEN5_Pos) |

        (0 << GPIO_DBEN_DBEN7_Pos) |

        (0 << GPIO_DBEN_DBEN8_Pos) |

        (0 << GPIO_DBEN_DBEN9_Pos) |

        u32RegDefault;

    //GPIO_PB edge or level interrupt
    PB->INTTYPE =

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE2_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE4_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE5_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE7_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE8_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE9_Pos) |

        u32RegDefault;

    //GPIO_PB enable falling(edge) or low(level) interrupt
    PB->INTEN =

        (0 << GPIO_INTEN_FLIEN2_Pos) |

        (0 << GPIO_INTEN_FLIEN4_Pos) |

        (0 << GPIO_INTEN_FLIEN5_Pos) |

        (0 << GPIO_INTEN_FLIEN7_Pos) |

        (0 << GPIO_INTEN_FLIEN8_Pos) |

        (0 << GPIO_INTEN_FLIEN9_Pos) |

        u32RegDefault;

    //GPIO_PB enable rising(edge) or high(level) interrupt
    PB->INTEN |=

        (0 << GPIO_INTEN_RHIEN2_Pos) |

        (0 << GPIO_INTEN_RHIEN4_Pos) |

        (0 << GPIO_INTEN_RHIEN5_Pos) |

        (0 << GPIO_INTEN_RHIEN7_Pos) |

        (0 << GPIO_INTEN_RHIEN8_Pos) |

        (0 << GPIO_INTEN_RHIEN9_Pos) |

        u32RegDefault;

    //GPIO_PB slew rate
    PB->SLEWCTL =

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN2_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN4_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN5_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN7_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN8_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN9_Pos) |

        u32RegDefault;

    //GPIO_PB pull-up or pull-down
    PB->PUSEL =

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL2_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL4_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL5_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL7_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL8_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL9_Pos) |

        u32RegDefault;

    GPIO_CLR_DEBOUNCE_ICLKON(PB);

    NVIC_EnableIRQ(GPB_IRQn);

    NVIC_EnableIRQ(EINT0_IRQn);//PB.5

    NVIC_EnableIRQ(EINT1_IRQn);//PB.4

    NVIC_EnableIRQ(EINT3_IRQn);//PB.2

    //GPIO_PC mode
    PC->MODE =

        (0x0UL << GPIO_MODE_MODE0_Pos) |

        (0x0UL << GPIO_MODE_MODE1_Pos) |

        (0x1UL << GPIO_MODE_MODE2_Pos) |

        (0x0UL << GPIO_MODE_MODE3_Pos) |

        (0x0UL << GPIO_MODE_MODE4_Pos) |

        (0x1UL << GPIO_MODE_MODE6_Pos) |

        u32RegDefault;

    //GPIO_PC disable digital input path
    PC->DINOFF =

        (0 << GPIO_DINOFF_DINOFF0_Pos) |

        (0 << GPIO_DINOFF_DINOFF1_Pos) |

        (0 << GPIO_DINOFF_DINOFF2_Pos) |

        (0 << GPIO_DINOFF_DINOFF3_Pos) |

        (0 << GPIO_DINOFF_DINOFF4_Pos) |

        (0 << GPIO_DINOFF_DINOFF6_Pos) |

        u32RegDefault;

    //GPIO_PC out data
    PC->DOUT =

        (1 << GPIO_DOUT_DOUT0_Pos) |

        (1 << GPIO_DOUT_DOUT1_Pos) |

        (1 << GPIO_DOUT_DOUT2_Pos) |

        (1 << GPIO_DOUT_DOUT3_Pos) |

        (1 << GPIO_DOUT_DOUT4_Pos) |

        (1 << GPIO_DOUT_DOUT6_Pos) |

        u32RegDefault;

    //GPIO_PC DOUT mask
    PC->DATMSK =

        (0 << GPIO_DATMSK_DATMSK0_Pos) |

        (0 << GPIO_DATMSK_DATMSK1_Pos) |

        (0 << GPIO_DATMSK_DATMSK2_Pos) |

        (0 << GPIO_DATMSK_DATMSK3_Pos) |

        (0 << GPIO_DATMSK_DATMSK4_Pos) |

        (0 << GPIO_DATMSK_DATMSK6_Pos) |

        u32RegDefault;

    //GPIO_PC enable de-bounce
    PC->DBEN =

        (0 << GPIO_DBEN_DBEN0_Pos) |

        (0 << GPIO_DBEN_DBEN1_Pos) |

        (0 << GPIO_DBEN_DBEN2_Pos) |

        (0 << GPIO_DBEN_DBEN3_Pos) |

        (0 << GPIO_DBEN_DBEN4_Pos) |

        (0 << GPIO_DBEN_DBEN6_Pos) |

        u32RegDefault;

    //GPIO_PC edge or level interrupt
    PC->INTTYPE =

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE0_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE1_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE2_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE3_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE4_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE6_Pos) |

        u32RegDefault;

    //GPIO_PC enable falling(edge) or low(level) interrupt
    PC->INTEN =

        (0 << GPIO_INTEN_FLIEN0_Pos) |

        (0 << GPIO_INTEN_FLIEN1_Pos) |

        (0 << GPIO_INTEN_FLIEN2_Pos) |

        (0 << GPIO_INTEN_FLIEN3_Pos) |

        (0 << GPIO_INTEN_FLIEN4_Pos) |

        (0 << GPIO_INTEN_FLIEN6_Pos) |

        u32RegDefault;

    //GPIO_PC enable rising(edge) or high(level) interrupt
    PC->INTEN |=

        (1 << GPIO_INTEN_RHIEN0_Pos) |

        (0 << GPIO_INTEN_RHIEN1_Pos) |

        (0 << GPIO_INTEN_RHIEN2_Pos) |

        (0 << GPIO_INTEN_RHIEN3_Pos) |

        (0 << GPIO_INTEN_RHIEN4_Pos) |

        (0 << GPIO_INTEN_RHIEN6_Pos) |

        u32RegDefault;

    //GPIO_PC slew rate
    PC->SLEWCTL =

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN0_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN1_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN2_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN3_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN4_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN6_Pos) |

        u32RegDefault;

    //GPIO_PC pull-up or pull-down
    PC->PUSEL =

        (GPIO_PUSEL_PULL_DOWN << GPIO_PUSEL_PUSEL0_Pos) |

        (GPIO_PUSEL_PULL_DOWN << GPIO_PUSEL_PUSEL1_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL2_Pos) |

        (GPIO_PUSEL_PULL_DOWN << GPIO_PUSEL_PUSEL3_Pos) |

        (GPIO_PUSEL_PULL_DOWN << GPIO_PUSEL_PUSEL4_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL6_Pos) |

        u32RegDefault;

    GPIO_CLR_DEBOUNCE_ICLKON(PC);

    NVIC_EnableIRQ(GPC_IRQn);

    //GPIO_PD mode
    PD->MODE =

        (0x0UL << GPIO_MODE_MODE0_Pos) |

        (0x0UL << GPIO_MODE_MODE1_Pos) |

        (0x1UL << GPIO_MODE_MODE2_Pos) |

        (0x1UL << GPIO_MODE_MODE3_Pos) |

        u32RegDefault;

    //GPIO_PD disable digital input path
    PD->DINOFF =

        (0 << GPIO_DINOFF_DINOFF0_Pos) |

        (0 << GPIO_DINOFF_DINOFF1_Pos) |

        (0 << GPIO_DINOFF_DINOFF2_Pos) |

        (0 << GPIO_DINOFF_DINOFF3_Pos) |

        u32RegDefault;

    //GPIO_PD out data
    PD->DOUT =

        (1 << GPIO_DOUT_DOUT0_Pos) |

        (1 << GPIO_DOUT_DOUT1_Pos) |

        (1 << GPIO_DOUT_DOUT2_Pos) |

        (1 << GPIO_DOUT_DOUT3_Pos) |

        u32RegDefault;

    //GPIO_PD DOUT mask
    PD->DATMSK =

        (0 << GPIO_DATMSK_DATMSK0_Pos) |

        (0 << GPIO_DATMSK_DATMSK1_Pos) |

        (0 << GPIO_DATMSK_DATMSK2_Pos) |

        (0 << GPIO_DATMSK_DATMSK3_Pos) |

        u32RegDefault;

    //GPIO_PD enable de-bounce
    PD->DBEN =

        (0 << GPIO_DBEN_DBEN0_Pos) |

        (1 << GPIO_DBEN_DBEN1_Pos) |

        (0 << GPIO_DBEN_DBEN2_Pos) |

        (0 << GPIO_DBEN_DBEN3_Pos) |

        u32RegDefault;

    //GPIO_PD edge or level interrupt
    PD->INTTYPE =

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE0_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE1_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE2_Pos) |

        (GPIO_INTTYPE_EDGE << GPIO_INTTYPE_TYPE3_Pos) |

        u32RegDefault;

    //GPIO_PD enable falling(edge) or low(level) interrupt
    PD->INTEN =

        (0 << GPIO_INTEN_FLIEN0_Pos) |

        (0 << GPIO_INTEN_FLIEN1_Pos) |

        (0 << GPIO_INTEN_FLIEN2_Pos) |

        (0 << GPIO_INTEN_FLIEN3_Pos) |

        u32RegDefault;

    //GPIO_PD enable rising(edge) or high(level) interrupt
    PD->INTEN |=

        (0 << GPIO_INTEN_RHIEN0_Pos) |

        (1 << GPIO_INTEN_RHIEN1_Pos) |

        (0 << GPIO_INTEN_RHIEN2_Pos) |

        (0 << GPIO_INTEN_RHIEN3_Pos) |

        u32RegDefault;

    //GPIO_PD slew rate
    PD->SLEWCTL =

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN0_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN1_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN2_Pos) |

        (GPIO_SLEWCTL_NORMAL << GPIO_SLEWCTL_HSREN3_Pos) |

        u32RegDefault;

    //GPIO_PD pull-up or pull-down
    PD->PUSEL =

        (GPIO_PUSEL_PULL_DOWN << GPIO_PUSEL_PUSEL0_Pos) |

        (GPIO_PUSEL_PULL_DOWN << GPIO_PUSEL_PUSEL1_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL2_Pos) |

        (GPIO_PUSEL_DISABLE << GPIO_PUSEL_PUSEL3_Pos) |

        u32RegDefault;

    GPIO_CLR_DEBOUNCE_ICLKON(PD);

    NVIC_EnableIRQ(GPD_IRQn);

}
/*--------------------------------------------------------------------------------------------*/
/* SPII2S                                                                                     */
/*--------------------------------------------------------------------------------------------*/
void SPII2S0_Init()
{

    /* This function make SPI module be ready to transfer */
    SPI_Open(SPI0, SPI_MASTER, SPI_MODE_3, 8, 1000000);

    /* Select SS level */
    SPI0->SSCTL = (SPI0->SSCTL & (~SPI_SSCTL_SSACTPOL_Msk)) | SPI_SS_ACTIVE_LOW;

    /* Set MSB first */
    SPI_SET_MSB_FIRST(SPI0);

    /* Set FIFO threshold */
    SPI_SetFIFO(SPI0, 0, 0);

}
void TIMER0_Init()
{

    TIMER_Open(TIMER0, TIMER0_MODE, TIMER0_FREQ);

#if (TIMER0_MODE == TIMER_TOGGLE_MODE)
    TIMER_SELECT_TOUT_PIN(TIMER0, TIMER_TOUT_PIN_FROM_TX);
#endif

    // Enable timer time-out interrupt
    TIMER_EnableInt(TIMER0);

    NVIC_EnableIRQ(TMR0_IRQn);
	
}

void TIMER1_Init()
{

    TIMER_Open(TIMER1, TIMER1_MODE, TIMER1_FREQ);

#if (TIMER1_MODE == TIMER_TOGGLE_MODE)
    TIMER_SELECT_TOUT_PIN(TIMER1, TIMER_TOUT_PIN_FROM_TX);
#endif

    // Enable timer time-out interrupt
    TIMER_EnableInt(TIMER1);

    NVIC_EnableIRQ(TMR1_IRQn);

}
void UART2_Init()
{

    /* Configure UART2 and set UART2 baud rate */
    UART_Open(UART2, 115200);

    /* RX FIFO Interrupt Trigger Level */
    UART2->FIFO = (UART2->FIFO & ~ UART_FIFO_RFITL_Msk) | UART_FIFO_RFITL_1BYTE;
	

}
void WDT_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Setup WDT Configuration */
    WDT_Open(WDT_TOUTSEL_CONFIG, WDT_RSTDSEL_CONFIG, WDT_RSTEN_CONFIG, WDT_WKEN_CONFIG);

    /* Enable WDT Time-out Interrupt */
    WDT_EnableInt();

    /* NVIC Enable WDT Interrupt */
    NVIC_EnableIRQ(WDT_IRQn);

}

void Periph_Init(void)
{

    UART2_Init();

    GPIO_Init();

    SPII2S0_Init() ;

    TIMER0_Init();

    TIMER1_Init();

    WDT_Init();

    FMC_Init();

}
