/****************************************************************************
 * @file     clk_conf.c
 * @version  V0.42
 * @Date     2023/05/18-12:01:26
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2016-2023 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M251SE3AE(LQFP64)
Base Clocks:
LIRC:38.4kHz
HIRC:48MHz
MIRC:4MHz
HXT:24MHz
HCLK:24MHz
PCLK0:24MHz
PCLK1:24MHz
Enabled-Module Frequencies:
FMCIDLE=Bus Clock(HCLK):24MHz/Engine Clock:48MHz
I2C1=Bus Clock(PCLK1):24MHz
ISP=Bus Clock(HCLK):24MHz
SPI0=Bus Clock(PCLK1):24MHz/Engine Clock:24MHz
TMR0=Bus Clock(PCLK0):24MHz/Engine Clock:48MHz
TMR1=Bus Clock(PCLK0):24MHz/Engine Clock:48MHz
UART2=Bus Clock(PCLK0):24MHz/Engine Clock:24MHz
WDT=Bus Clock(PCLK0):24MHz/Engine Clock:38.4kHz
WWDT=Bus Clock(PCLK0):24MHz/Engine Clock:11.7188kHz
********************/

#include "scale_v2.h"

/*
 * @brief This function updates clock registers to fulfill the configuration
 * @param None
 * @return None
 */
void Clock_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    //CLK->PWRCTL   = (CLK->PWRCTL   & ~(0x0008000FUL)) | 0x0079001DUL;
    //CLK->PLLCTL   = (CLK->PLLCTL   & ~(0x001FDE3FUL)) | 0x00054618UL;
    //CLK->CLKDIV0  = (CLK->CLKDIV0  & ~(0x00FFFFFFUL)) | 0x00000000UL;
    //CLK->CLKDIV1  = (CLK->CLKDIV1  & ~(0xFF0000FFUL)) | 0x00000000UL;
    //CLK->CLKDIV4  = (CLK->CLKDIV4  & ~(0x0000000FUL)) | 0x00000000UL;
    //CLK->PCLKDIV  = (CLK->PCLKDIV  & ~(0x00000077UL)) | 0x00000000UL;
    //CLK->CLKSEL0  = (CLK->CLKSEL0  & ~(0x0000013FUL)) | 0x00000038UL;
    //CLK->CLKSEL1  = (CLK->CLKSEL1  & ~(0x7777777FUL)) | 0x4477773BUL;
    //CLK->CLKSEL2  = (CLK->CLKSEL2  & ~(0x7000033FUL)) | 0x2000032BUL;
    //CLK->CLKSEL3  = (CLK->CLKSEL3  & ~(0x07000003UL)) | 0x04000003UL;
    //CLK->AHBCLK   = (CLK->AHBCLK   & ~(0x0000808EUL)) | 0x00008004UL;
    //CLK->APBCLK0  = (CLK->APBCLK0  & ~(0x180733FFUL)) | 0x0004220DUL;
    //CLK->APBCLK1  = (CLK->APBCLK1  & ~(0xC00F1701UL)) | 0x00000000UL;
    //CLK->CLKOCTL  = (CLK->CLKOCTL  & ~(0x0000007FUL)) | 0x00000000UL;
    //SysTick->CTRL = (SysTick->CTRL & ~(0x00000005UL)) | 0x00000000UL;
    //RTC->LXTCTL   = (RTC->LXTCTL   & ~(0x00000080UL)) | 0x780F010EUL;

    /* Enable clock source */
    CLK_EnableXtalRC(CLK_PWRCTL_LIRCEN_Msk | CLK_PWRCTL_HIRCEN_Msk | CLK_PWRCTL_HXTEN_Msk | CLK_PWRCTL_MIRCEN_Msk);

    /* Waiting for clock source ready */
    CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk | CLK_STATUS_HIRCSTB_Msk | CLK_STATUS_HXTSTB_Msk | CLK_STATUS_MIRCSTB_Msk);

    /* Set HCLK clock */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT, CLK_CLKDIV0_HCLK(1));

    /* Set PCLK-related clock */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV1 | CLK_PCLKDIV_APB1DIV_DIV1);

    /* Enable IP clock */
    CLK_EnableModuleClock(FMCIDLE_MODULE);
    CLK_EnableModuleClock(I2C1_MODULE);
    CLK_EnableModuleClock(ISP_MODULE);
    CLK_EnableModuleClock(SPI0_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_EnableModuleClock(TMR1_MODULE);
    CLK_EnableModuleClock(UART2_MODULE);
    CLK_EnableModuleClock(WDT_MODULE);
    CLK_EnableModuleClock(WWDT_MODULE);

    /* Set IP clock */
    CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0SEL_PCLK1, MODULE_NoMsk);
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HIRC, MODULE_NoMsk);
    CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HIRC, MODULE_NoMsk);
    CLK_SetModuleClock(UART2_MODULE, CLK_CLKSEL3_UART2SEL_PCLK0, CLK_CLKDIV4_UART2(1));
    CLK_SetModuleClock(WDT_MODULE, CLK_CLKSEL1_WDTSEL_LIRC, MODULE_NoMsk);
    CLK_SetModuleClock(WWDT_MODULE, CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048, MODULE_NoMsk);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    return;
}

/*** (C) COPYRIGHT 2016-2023 Nuvoton Technology Corp. ***/
