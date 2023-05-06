/******************************************************************************//**
 * @file     int_handler.c
 * @version  V1.01
 * @brief    M251 interrupt handler file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include "scale_v1.h"
void GPB_IRQHandler(void)
{
    /* To check if PB.2 interrupt occurred */
    if (GPIO_GET_INT_FLAG(PB, BIT2))
    {
        GPIO_CLR_INT_FLAG(PB, BIT2);
        printf("PB.2 INT occurred.\n");
    }
    else
    {
        /* Un-expected interrupt. Just clear all PB interrupts */
        PB->INTSRC = PB->INTSRC;
        printf("Un-expected interrupts.\n");
    }
}

void GPC_IRQHandler(void)
{
    /* To check if PC.0 interrupt occurred */
    if (GPIO_GET_INT_FLAG(PC, BIT0))
    {
        GPIO_CLR_INT_FLAG(PC, BIT0);
        printf("PC.0 INT occurred.\n");
    }
    else
    {
        /* Un-expected interrupt. Just clear all PC interrupts */
        PC->INTSRC = PC->INTSRC;
        printf("Un-expected interrupts.\n");
    }
}

void GPD_IRQHandler(void)
{
    /* To check if PD.0 interrupt occurred */
    if (GPIO_GET_INT_FLAG(PD, BIT0))
    {
        GPIO_CLR_INT_FLAG(PD, BIT0);
        printf("PD.0 INT occurred.\n");
    }
    else
    {
        /* Un-expected interrupt. Just clear all PD interrupts */
        PD->INTSRC = PD->INTSRC;
        printf("Un-expected interrupts.\n");
    }
}

void EINT0_IRQHandler(void)
{

    /* To check if PB.5 external interrupt occurred */
    if (GPIO_GET_INT_FLAG(PB, BIT5))
    {
        GPIO_CLR_INT_FLAG(PB, BIT5);
        printf("PB.5 EINT0 occurred.\n");
    }

}

void EINT1_IRQHandler(void)
{

    /* To check if PB.4 external interrupt occurred */
    if (GPIO_GET_INT_FLAG(PB, BIT4))
    {
        GPIO_CLR_INT_FLAG(PB, BIT4);
        printf("PB.4 EINT1 occurred.\n");
    }

}

void EINT3_IRQHandler(void)
{

    /* To check if PB.2 external interrupt occurred */
    if (GPIO_GET_INT_FLAG(PB, BIT2))
    {
        GPIO_CLR_INT_FLAG(PB, BIT2);
        printf("PB.2 EINT3 occurred.\n");
    }

}
void TMR0_IRQHandler(void)
{

    if (TIMER_GetIntFlag(TIMER0))
    {
        /* Clear Timer0 time-out interrupt flag */
        TIMER_ClearIntFlag(TIMER0);
    }

}

void TMR1_IRQHandler(void)
{

    if (TIMER_GetIntFlag(TIMER1))
    {
        /* Clear TIMER1 time-out interrupt flag */
        TIMER_ClearIntFlag(TIMER1);
    }

}
void WDT_IRQHandler(void)
{
    /* Get WDT Time-out interrupt flag */
    if (WDT_GET_TIMEOUT_INT_FLAG())
    {
        /* Clear WDT time-out interrupt flag */
        WDT_CLEAR_TIMEOUT_INT_FLAG();
    }

    /* Get WDT time-out wakeup  flag */
    if (WDT_GET_TIMEOUT_WAKEUP_FLAG())
    {
        /* Clear WDT time-out wakeup  flag */
        WDT_CLEAR_TIMEOUT_WAKEUP_FLAG();
    }

    /* To prevent system from reset by WDT, it is necessary to clear WDT counter
       by software before WDT counter reaches the reset delay time after time-out occurs. */

    WDT_RESET_COUNTER();
}
