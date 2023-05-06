#include "Inc/app.h"
#include "Inc/keypad.h"

//#############################################################################################
//                               GLOBAL VARIABLE & DEFINITONS
//#############################################################################################
int sil = 0;
AIP    * p_LcdObj_S1;
AIP    * p_LcdObj_S2;
AIP    * p_LcdObj_S3;

Params _param1;
Params _param2;
Params _param3;

KEYPAD * p_KeypadObj;

FontDef font_small = {
	.FontWidth=3,
	.FontHeight=3,
	.data=&fontArray[0],
};

//#############################################################################################
//                                    USER FUNCTIONS
//#############################################################################################


//#############################################################################################
void APP_Init(){
	/****************************************/
	_param1.A0 	  = &SCREEN_1_AIP_A0Pin;
	_param1.Reset = &SCREEN_1_AIP_ResetPin;
	_param1.Cs 		= &SCREEN_1_AIP_CSPin;
	
	p_LcdObj_S1 			= newLCDObj(&_param1);
	p_LcdObj_S1->Init(p_LcdObj_S1);
	p_LcdObj_S1->ClearScreen(p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	/****************************************/

	_param2.A0 	  = &SCREEN_2_AIP_A0Pin;
	_param2.Reset = &SCREEN_2_AIP_ResetPin;
	_param2.Cs 		= &SCREEN_2_AIP_CSPin;

	p_LcdObj_S2 			= newLCDObj(&_param2);
	p_LcdObj_S2->Init(p_LcdObj_S2);
	p_LcdObj_S2->ClearScreen(p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	/****************************************/

	_param3.A0 	  = &SCREEN_3_AIP_A0Pin;
	_param3.Reset = &SCREEN_3_AIP_ResetPin;
	_param3.Cs 		= &SCREEN_3_AIP_CSPin;

	p_LcdObj_S3 			= newLCDObj(&_param3);
	p_LcdObj_S3->Init(p_LcdObj_S3);
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	/****************************************/
 	p_KeypadObj = newKeyPadObj();
  p_KeypadObj->Init(KEYPAD_COLUMN_SIZE,KEYPAD_ROW_SIZE);
	sil=1;

}
//#############################################################################################
void APP_SetBatteryLevel(uint8_t _level,AIP *p){
	p->Spoint(1,1,p);
	switch(_level){
		case 0: // low battery 
			p->Spoint(3,0,p);
			p->Spoint(2,0,p);
			break;
		case 1: // half battery 
			p->Spoint(3,1,p);
			p->Spoint(2,0,p);
			break;
		case 2: // full battery 
			p->Spoint(3,1,p);
			p->Spoint(2,1,p);
			break;
	}
}
//#############################################################################################
void APP_Handle(){
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"bersy",&font_small,p_LcdObj_S1);
	APP_SetBatteryLevel(BATTERY_FULL,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"hello",&font_small,p_LcdObj_S2);
	APP_SetBatteryLevel(BATTERY_FULL,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"hello",&font_small,p_LcdObj_S3);
	APP_SetBatteryLevel(BATTERY_FULL,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	while(1){
		int keypadRet	= p_KeypadObj->Scan();
		if(keypadRet > 0){
			printf("key : 0x%x\n",keypadRet);
		}
	}
		
	
}
//#############################################################################################
void  SCREEN_1_AIP_ResetPin(uint8_t _val){
	PA5=_val;
}
//#############################################################################################
void  SCREEN_1_AIP_A0Pin(uint8_t _val){
	PA3=_val;
}
//#############################################################################################
void  SCREEN_1_AIP_CSPin(uint8_t _val){
	PA4=_val;	
}



//#############################################################################################
void  SCREEN_2_AIP_ResetPin(uint8_t _val){
	PB2=_val;
}
//#############################################################################################
void  SCREEN_2_AIP_A0Pin(uint8_t _val){
	PB5=_val;
}
//#############################################################################################
void  SCREEN_2_AIP_CSPin(uint8_t _val){
	PB4=_val;	
}



//#############################################################################################
void  SCREEN_3_AIP_ResetPin(uint8_t _val){
	PB7=_val;
}
//#############################################################################################
void  SCREEN_3_AIP_A0Pin(uint8_t _val){
	PB8=_val;
}
//#############################################################################################
void  SCREEN_3_AIP_CSPin(uint8_t _val){
	PB9=_val;	
}
//#############################################################################################
void APP_StartScreen(){
	
#if (LOG_STATE)
     printf("Start Screen Runing ...\n");
#endif
	
	p_LcdObj_S1->ClearScreen(p_LcdObj_S1);
  APP_SetBatteryLevel(BATTERY_FULL,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"999999",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"888888",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"777777",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"666666",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"555555",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"444444",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"333333",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"222222",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"111111",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"000000",&font_small,p_LcdObj_S1);
	APP_All_Point_High();
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	CLK_SysTickLongDelay(1000000);

}
//#############################################################################################
void APP_All_Point_High(){
	for(int i=17;i>=0;i--){
		p_LcdObj_S1->Spoint(i,1,p_LcdObj_S1);
	}

}
//#############################################################################################





//#############################################################################################
//                                           END
//#############################################################################################