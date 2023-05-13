
#ifndef __APP_H__
#define __APP_H__

#include<stdint.h>
#include "scale_v1.h"
#include "Inc/costumLcd.h"
#include<stdbool.h>

//#############################################################################################
//                               GLOBAL VARIABLE & DEFINITONS
//#############################################################################################

#define BATTERY_LOW				   0
#define BATTERY_HALF			   1
#define BATTERY_FULL			   2
#define START_SCREEN_SPEED   200000

//#############################################################################################
//                                    USER FUNCTIONS
//#############################################################################################

void ISR_timer();

void APP_Init();
void APP_SetBatteryLevel(uint8_t _level,AIP *p);
void APP_SettingsHandle();
void APP_Handle();
uint8_t APP_StartScreen();
void APP_All_Point_High(uint8_t selScreen);
bool APP_GetMeasure(float *_weight);
bool APP_Show_Weight(float *_weight);

 
 float customValueInput(char pressedKey,AIP *p);
 
//#############################################################################################
//                                           END
//#############################################################################################
#endif