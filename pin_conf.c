/****************************************************************************
 * @file     pin_conf.c
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
Pin Configuration:
Pin2:PB.5
Pin3:PB.4
Pin4:I2C1_SCL
Pin5:PB.2
Pin7:UART2_RXD
Pin16:XT1_IN
Pin17:XT1_OUT
Pin19:PC.6
Pin20:PA.7
Pin21:PA.6
Pin25:PA.5
Pin26:PA.4
Pin27:PA.3
Pin28:SPI0_CLK
Pin29:SPI0_MISO
Pin30:SPI0_MOSI
Pin33:ICE_DAT
Pin34:ICE_CLK
Pin35:UART2_TXD
Pin36:PC.4
Pin37:PC.3
Pin38:PC.2
Pin39:PC.1
Pin40:PC.0
Pin41:PD.3
Pin42:PD.2
Pin43:PD.1
Pin44:PD.0
Pin45:PA.12
Pin46:I2C1_SDA
Pin62:PB.9
Pin63:PB.8
Pin64:PB.7
Module Configuration:
PB.2(Pin:5)
PB.4(Pin:3)
PB.5(Pin:2)
PB.7(Pin:64)
PB.8(Pin:63)
PB.9(Pin:62)
I2C1_SCL(Pin:4)
I2C1_SDA(Pin:46)
UART2_RXD(Pin:7)
UART2_TXD(Pin:35)
XT1_IN(Pin:16)
XT1_OUT(Pin:17)
PC.0(Pin:40)
PC.1(Pin:39)
PC.2(Pin:38)
PC.3(Pin:37)
PC.4(Pin:36)
PC.6(Pin:19)
PA.3(Pin:27)
PA.4(Pin:26)
PA.5(Pin:25)
PA.6(Pin:21)
PA.7(Pin:20)
PA.12(Pin:45)
SPI0_CLK(Pin:28)
SPI0_MISO(Pin:29)
SPI0_MOSI(Pin:30)
ICE_CLK(Pin:34)
ICE_DAT(Pin:33)
PD.0(Pin:44)
PD.1(Pin:43)
PD.2(Pin:42)
PD.3(Pin:41)
GPIO Configuration:
PA.0:SPI0_MOSI(Pin:30)
PA.1:SPI0_MISO(Pin:29)
PA.2:SPI0_CLK(Pin:28)
PA.3:PA.3(Pin:27)
PA.4:PA.4(Pin:26)
PA.5:PA.5(Pin:25)
PA.6:PA.6(Pin:21)
PA.7:PA.7(Pin:20)
PA.12:PA.12(Pin:45)
PA.13:I2C1_SDA(Pin:46)
PB.0:UART2_RXD(Pin:7)
PB.2:PB.2(Pin:5)
PB.3:I2C1_SCL(Pin:4)
PB.4:PB.4(Pin:3)
PB.5:PB.5(Pin:2)
PB.7:PB.7(Pin:64)
PB.8:PB.8(Pin:63)
PB.9:PB.9(Pin:62)
PC.0:PC.0(Pin:40)
PC.1:PC.1(Pin:39)
PC.2:PC.2(Pin:38)
PC.3:PC.3(Pin:37)
PC.4:PC.4(Pin:36)
PC.5:UART2_TXD(Pin:35)
PC.6:PC.6(Pin:19)
PD.0:PD.0(Pin:44)
PD.1:PD.1(Pin:43)
PD.2:PD.2(Pin:42)
PD.3:PD.3(Pin:41)
PF.0:ICE_DAT(Pin:33)
PF.1:ICE_CLK(Pin:34)
PF.2:XT1_OUT(Pin:17)
PF.3:XT1_IN(Pin:16)
********************/

#include "scale_v2.h"

/*
 * @brief This function provides the configured MFP registers
 * @param None
 * @return None
 */
void Pin_Init(void)
{
    //SYS->GPA_MFPH = 0x00400000UL;
    //SYS->GPA_MFPL = 0x00000444UL;
    //SYS->GPB_MFPH = 0x00000000UL;
    //SYS->GPB_MFPL = 0x00004007UL;
    //SYS->GPC_MFPH = 0x00000000UL;
    //SYS->GPC_MFPL = 0x00800000UL;
    //SYS->GPD_MFPH = 0x00000000UL;
    //SYS->GPD_MFPL = 0x00000000UL;
    //SYS->GPF_MFPL = 0x0000AAEEUL;

    SYS->GPA_MFPH = SYS_GPA_MFPH_PA13MFP_I2C1_SDA | SYS_GPA_MFPH_PA12MFP_GPIO;
    SYS->GPA_MFPL = SYS_GPA_MFPL_PA7MFP_GPIO | SYS_GPA_MFPL_PA6MFP_GPIO | SYS_GPA_MFPL_PA5MFP_GPIO | SYS_GPA_MFPL_PA4MFP_GPIO | SYS_GPA_MFPL_PA3MFP_GPIO | SYS_GPA_MFPL_PA2MFP_SPI0_CLK |
                    SYS_GPA_MFPL_PA1MFP_SPI0_MISO | SYS_GPA_MFPL_PA0MFP_SPI0_MOSI;
    SYS->GPB_MFPH = SYS_GPB_MFPH_PB9MFP_GPIO | SYS_GPB_MFPH_PB8MFP_GPIO;
    SYS->GPB_MFPL = SYS_GPB_MFPL_PB7MFP_GPIO | SYS_GPB_MFPL_PB5MFP_GPIO | SYS_GPB_MFPL_PB4MFP_GPIO | SYS_GPB_MFPL_PB3MFP_I2C1_SCL | SYS_GPB_MFPL_PB2MFP_GPIO | SYS_GPB_MFPL_PB0MFP_UART2_RXD;
    SYS->GPC_MFPH = 0x00000000;
    SYS->GPC_MFPL = SYS_GPC_MFPL_PC6MFP_GPIO | SYS_GPC_MFPL_PC5MFP_UART2_TXD | SYS_GPC_MFPL_PC4MFP_GPIO | SYS_GPC_MFPL_PC3MFP_GPIO | SYS_GPC_MFPL_PC2MFP_GPIO | SYS_GPC_MFPL_PC1MFP_GPIO |
                    SYS_GPC_MFPL_PC0MFP_GPIO;
    SYS->GPD_MFPH = 0x00000000;
    SYS->GPD_MFPL = SYS_GPD_MFPL_PD3MFP_GPIO | SYS_GPD_MFPL_PD2MFP_GPIO | SYS_GPD_MFPL_PD1MFP_GPIO | SYS_GPD_MFPL_PD0MFP_GPIO;
    SYS->GPF_MFPL = SYS_GPF_MFPL_PF3MFP_XT1_IN | SYS_GPF_MFPL_PF2MFP_XT1_OUT | SYS_GPF_MFPL_PF1MFP_ICE_CLK | SYS_GPF_MFPL_PF0MFP_ICE_DAT;

    return;
}

/*** (C) COPYRIGHT 2016-2023 Nuvoton Technology Corp. ***/
