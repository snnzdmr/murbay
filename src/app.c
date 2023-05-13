#include "Inc/app.h"
#include "Inc/keypad.h"
#include "Inc/menu.h"
#include <stdlib.h>
//#############################################################################################
//                               GLOBAL VARIABLE & DEFINITONS
//#############################################################################################
AIP    * p_LcdObj_S1;
AIP    * p_LcdObj_S2;
AIP    * p_LcdObj_S3;

Params _param1;
Params _param2;
Params _param3;
MENU_Params m_Param;
KEYPAD * p_KeypadObj;
MENU   * p_MenuObj;
node * currentNode;
FontDef *p_CurrentFont;
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
	/****************************************/
	p_MenuObj = newMenuObj();
	p_MenuObj->Init();
	/****************************************/
	p_CurrentFont =&font_small;
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
void APP_SettingsHandle(){
	uint8_t longPres=0;
	char pressedKey=0;
	p_MenuObj->Enter(&(p_MenuObj->currentNode));
	while(1){
		pressedKey = p_KeypadObj->Scan(&longPres);
		switch(pressedKey){
			case 't': // enter tare 
				p_MenuObj->Enter(&(p_MenuObj->currentNode));
				break;
			case 'z':
				p_MenuObj->Exit(&(p_MenuObj->currentNode)); 
				if( (p_MenuObj->currentNode)->exit  == 0){
					return;
				}
				break;
			case 'm':
				p_MenuObj->Up(&(p_MenuObj->currentNode));
				break;
			case 'p':
				p_MenuObj->Down(&(p_MenuObj->currentNode));
				break;
		}
	}
}
float customValueInput(char pressedKey,AIP *p){
		static uint8_t pointCounter=0;
		static uint8_t _id=0;
		static uint8_t tempArray[7]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};
		uint8_t buffer[7]="";
		switch(pressedKey){
			case 'c':
				pointCounter = 0;
				_id=0;
				memset(&tempArray[0],0x00,7);
				p->WriteString(0,0,(uint8_t *)"      ",&font_small,p);
				p->UpdateScreen(p);
				break;
			case 'z':
				break;
			case 't':
				break;
			case 'q':
				break;
			case 's':
				break;
			case 'p':
				break;
			case 'u':
				break;
			case 'm':
				break;
			case 'C': //CH
				break;
			case '.': //CH
				if(pressedKey == '.' && pointCounter<1 && _id>0 && _id<6){
					pointCounter++;
				}
				else{
					break;
				}
			default:
				if(_id<(6+pointCounter)){
				  _id++;
					for(int i=0;i<((6+pointCounter)-_id);i++){
						buffer[i]  =0x20; // padding
					}
					if(pressedKey == '.'){
						buffer[(6+pointCounter)-(_id+pointCounter)]  =0x00;
					}
					strncat((char *)tempArray, &pressedKey, 1);
					strncat((char *)buffer,(const char *)tempArray,_id);
					
					p->WriteString(0,0,&buffer[0],&font_small,p);
					p->UpdateScreen(p);
					
					
					
				}
				break;
		}
		return atof((const char *)tempArray);
}

float setPrice(char pressedKey,AIP *p){
	return customValueInput(pressedKey,p);
}
void APP_ShowTotal(float _totatl,float _wight){
	char array[20]="";
	sprintf(&array[0],"%f",(_totatl*_wight));
	
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)array,&font_small,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
}
void APP_Handle(){
	uint8_t ret = 0;
	int16_t pressedKey=0;
	uint8_t longPres=0;
	float weight=0;
	float total = 0;
	ret = APP_StartScreen();
	if(ret){ // settings handle
		APP_SettingsHandle();
	}
	while(1){
		APP_Show_Weight(&weight);
		pressedKey = p_KeypadObj->Scan(&longPres);
		if(pressedKey > -1 && longPres == 0){
			total = setPrice((char)pressedKey,p_LcdObj_S2);
			APP_ShowTotal(total,weight);
		}
		
		if(pressedKey > -1 && longPres == 1){
			longPres=0;
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
uint8_t APP_StartScreen(){
	
#if (LOG_STATE)
     printf("Start Screen Runing ...\n");
#endif
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"999999",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"999999",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"999999",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"888888",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"888888",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"888888",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"777777",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"777777",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"777777",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"666666",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"666666",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"666666",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"555555",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"555555",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"555555",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"444444",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"444444",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"444444",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"333333",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"333333",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"333333",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"222222",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"222222",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"222222",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"111111",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"111111",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"111111",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"000000",&font_small,p_LcdObj_S1);
	APP_All_Point_High(1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"000000",&font_small,p_LcdObj_S2);
	APP_All_Point_High(2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"000000",&font_small,p_LcdObj_S3);
	APP_All_Point_High(3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	CLK_SysTickLongDelay(START_SCREEN_SPEED);
	
	p_LcdObj_S1->ClearScreen(p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	p_LcdObj_S2->ClearScreen(p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	
	char pressedKey=0;
	uint8_t _longPress=0;
	pressedKey = p_KeypadObj->Scan(&_longPress);
	if(pressedKey == 't'){
		return 1;
	}
	return 0;
	
}
//#############################################################################################
void APP_All_Point_High(uint8_t selScreen){
	AIP *p;
	switch (selScreen){
		case 1:
			p = p_LcdObj_S1;
			break;
		case 2:
			p = p_LcdObj_S2;
			break;
		case 3:
			p = p_LcdObj_S3;
			break;
		default:
			return;
	}
	for(int i=17;i>=0;i--){
		p->Spoint(i,1,p);
	}

}
//#############################################################################################



//#############################################################################################
//                                           MEAUSERE 
//#############################################################################################
bool APP_GetMeasure(float *_weight){
	bool stable=false;
	*_weight = 123456; 
	stable=true;
	return stable;
}



//#############################################################################################
//                                           -------- 
//#############################################################################################

bool APP_Show_Weight(float *_weight){
	char array[10]="";
	bool stable=false;
	stable = APP_GetMeasure(_weight);
	if(stable){
		p_LcdObj_S1->Spoint(16,1,p_LcdObj_S1); // stable icon on 
	}
	else{
		p_LcdObj_S1->Spoint(16,0,p_LcdObj_S1); // stable icon off 
	}
	sprintf(&array[0],"%f",*_weight);
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)array,&font_small,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	return stable;
}




//#############################################################################################
//                                           END
//#############################################################################################