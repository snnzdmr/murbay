
#ifndef __APP_H__
#define __APP_H__

#include<stdint.h>
#include "scale_v2.h"
#include "Inc/costumLcd.h"
#include "Inc/menu.h"
#include<stdbool.h>

//#############################################################################################
//                               GLOBAL VARIABLE & DEFINITONS
//#############################################################################################

typedef struct workVariable{
	MENU_Params	*p_menuParams;
	uint32_t PLU_Buffer[100];
	bool saveButtonFlag;
	bool unitButtonFlag;
	bool stableFlag;
	bool oneShotMeasure;
	bool qytFlag;
}workVariable;

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
uint8_t APP_StartScreen(MENU_Params *p_MenuParam);
void APP_All_Point_High(uint8_t selScreen);
bool APP_GetMeasure(float *_weight,MENU_Params *p_MenuParam);
bool APP_Show_Weight(float *_weight,MENU_Params *p_MenuParam);
void APP_ShowTotal(float _price,MENU_Params *p_MenuParam,AIP *p);
void calculate_2gr(float *_weight,MENU_Params *p_MenuParam);
void calculate_5gr(float *_weight,MENU_Params *p_MenuParam);
void calculate_10gr(float *_weight,MENU_Params *p_MenuParam);
 float customValueInputFix(char pressedKey,AIP *p,MENU_Params *p_MenuParam);
float customValueInput(char pressedKey,AIP *p);
uint32_t _pow(uint32_t x,uint32_t y);
float _abs(float x);
float setPrice(char pressedKey,AIP *p,MENU_Params *p_MenuParam);
void tare(MENU_Params *p_MenuParam);
void clearPriceScreen(AIP *p,MENU_Params *p_MenuParam);
//#############################################################################################
//                                           END
//#############################################################################################
#endif