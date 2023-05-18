#include "Inc/app.h"
#include "Inc/keypad.h"
#include "Inc/SparkFun_NAU7802.h"
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
SCALE  * p_ScaleObj;
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
	
	/****************************************/
	p_ScaleObj = newScaleObj();
	p_ScaleObj->begin();
	
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

float customValueInputFix(char pressedKey,AIP *p,MENU_Params *p_MenuParam){
	static uint8_t _id=0;
	static float total  = 0;
	float templateValue = 0;
	uint8_t buffer[7]="";
	static uint8_t tempArray[7]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	uint8_t len=0;
	switch(pressedKey){
			case 'c':
				_id=0;
			  total=0;
			  memset(&tempArray[0],0x00,7);
					switch(p_MenuParam->decimalPoint){
						case dp_0:
							p->WriteString(0,0,(uint8_t *)"     0",&font_small,p);
							break;
						case dp_0_0:
							p->WriteString(0,0,(uint8_t *)"    0.0",&font_small,p);
							break;
						case dp_0_00:
							p->WriteString(0,0,(uint8_t *)"   0.00",&font_small,p);
							break;
						case dp_0_000:
							p->WriteString(0,0,(uint8_t *)"  0.000",&font_small,p);
							break;
						case dp_0_0000:
							p->WriteString(0,0,(uint8_t *)" 0.0000",&font_small,p);
							break;
					}
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
					total = total * 100;
					switch(p_MenuParam->decimalPoint){
						case dp_0:
							if(total > 999999){total = total / 100;}
							break;
						case dp_0_0:
							if(total > 99999){total = total / 100;}
							break;
						case dp_0_00:
							if(total > 9999){total = total / 100;}
							break;
						case dp_0_000:
							if(total > 999){total = total / 100;}
							break;
						case dp_0_0000:
							if(total > 99){total = total / 100;}
							break;
					}
				// break; break olmayacak ! 
			default:
				if( _id<6){
					if(pressedKey != '.'){
						_id++;			
						templateValue = (pressedKey-'0'); //
						templateValue = templateValue / (_pow(10,p_MenuParam->decimalPoint));
						total = (total*10) + templateValue;
					}
					memset(&tempArray[0],0x00,7);
					switch(p_MenuParam->decimalPoint){
						case dp_0:
							len = sprintf((char*)(&tempArray[0]),"%d",(int)total);len+=1;
							break;
						case dp_0_0:
							len = sprintf((char*)(&tempArray[0]),"%.1f",total);
							break;
						case dp_0_00:
							len = sprintf((char*)(&tempArray[0]),"%.2f",total);
							break;
						case dp_0_000:
							len = sprintf((char*)(&tempArray[0]),"%.3f",total);
							break;
						case dp_0_0000:
							len = sprintf((char*)(&tempArray[0]),"%.4f",total);
							break;
					}
					for(int i=0;i<(7-len);i++){
						buffer[i]  =0x20; // add padding
					}
					strncat((char *)buffer,(const char *)tempArray,len);								
					p->WriteString(0,0,&buffer[0],&font_small,p);
					p->UpdateScreen(p);
				}
				break;
		}
		return atof((const char *)tempArray);
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

float setPrice(char pressedKey,AIP *p,MENU_Params *p_MenuParam){
	if(p_MenuParam->FixFloat == ff_float){
		return customValueInput(pressedKey,p);
	}
	else if(p_MenuParam->FixFloat == ff_fix){
		return customValueInputFix(pressedKey,p,p_MenuParam);
	}
	else{
		return -1;
	}
}
void APP_ShowTotal(float _price,float _wight,MENU_Params *p_MenuParam){	
	uint8_t array[10]="";
	uint8_t buffer[7]="";
	int len=0;
	float totalPrices = 0;
	totalPrices = _price * _wight;
	switch(p_MenuParam->decimalPoint){
		case dp_0:
			if(totalPrices > 999999){totalPrices=9999999;}
			len = sprintf((char*)(&array[0]),"%d",(int)(totalPrices));len+=1;
			break;
		case dp_0_0:
			if(totalPrices > 99999){totalPrices=99999.9;}
			len = sprintf((char*)(&array[0]),"%.1f",totalPrices);
			break;
		case dp_0_00:
			if(totalPrices > 9999){totalPrices=9999.99;}
			len = sprintf((char*)(&array[0]),"%.2f",totalPrices);
			break;
		case dp_0_000:
			if(totalPrices > 999){totalPrices=999.999;}
			len = sprintf((char*)(&array[0]),"%.3f",totalPrices);
			break;
		case dp_0_0000:
			if(totalPrices > 99){totalPrices=99.9999;}
			len = sprintf((char*)(&array[0]),"%.4f",totalPrices);
			break;
	}
	for(int i=0;i<(7-len);i++){
		buffer[i]  =0x20; // add padding
	}
	strncat((char *)buffer,(const char *)array,len);
	
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)buffer,&font_small,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
}
void APP_Handle(){
	uint8_t ret = 0;
	int16_t pressedKey=0;
	uint8_t longPres=0;
	float weight=0;
	float total = 0;
	
	m_Param.decimalPoint = dp_0_00;
	ret = APP_StartScreen(&m_Param);
	if(ret){ // settings handle
		APP_SettingsHandle();
	}
	while(1){
		APP_Show_Weight(&weight,&m_Param);
		pressedKey = p_KeypadObj->Scan(&longPres);
		if(pressedKey > -1 && longPres == 0){
			total = setPrice((char)pressedKey,p_LcdObj_S2,&m_Param);
			APP_ShowTotal(total,weight,&m_Param);
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
uint8_t APP_StartScreen(MENU_Params *p_MenuParam){
	
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
	

	switch(p_MenuParam->decimalPoint){
		case dp_0:
			p_LcdObj_S1->WriteString(0,0,(uint8_t *)"     0",&font_small,p_LcdObj_S1);
			p_LcdObj_S2->WriteString(0,0,(uint8_t *)"     0",&font_small,p_LcdObj_S2);
			p_LcdObj_S3->WriteString(0,0,(uint8_t *)"     0",&font_small,p_LcdObj_S3);
			break;
		case dp_0_0:
			p_LcdObj_S2->WriteString(0,0,(uint8_t *)"    0.0",&font_small,p_LcdObj_S1);
			p_LcdObj_S2->WriteString(0,0,(uint8_t *)"    0.0",&font_small,p_LcdObj_S2);
			p_LcdObj_S3->WriteString(0,0,(uint8_t *)"    0.0",&font_small,p_LcdObj_S3);
			break;
		case dp_0_00:
			p_LcdObj_S1->WriteString(0,0,(uint8_t *)"   0.00",&font_small,p_LcdObj_S1);
			p_LcdObj_S2->WriteString(0,0,(uint8_t *)"   0.00",&font_small,p_LcdObj_S2);
			p_LcdObj_S3->WriteString(0,0,(uint8_t *)"   0.00",&font_small,p_LcdObj_S3);
			break;
		case dp_0_000:
			p_LcdObj_S1->WriteString(0,0,(uint8_t *)"  0.000",&font_small,p_LcdObj_S1);
			p_LcdObj_S2->WriteString(0,0,(uint8_t *)"  0.000",&font_small,p_LcdObj_S2);
			p_LcdObj_S3->WriteString(0,0,(uint8_t *)"  0.000",&font_small,p_LcdObj_S3);
			break;
		case dp_0_0000:
			p_LcdObj_S1->WriteString(0,0,(uint8_t *)" 0.0000",&font_small,p_LcdObj_S1);
			p_LcdObj_S2->WriteString(0,0,(uint8_t *)" 0.0000",&font_small,p_LcdObj_S2);
			p_LcdObj_S3->WriteString(0,0,(uint8_t *)" 0.0000",&font_small,p_LcdObj_S3);
			break;
	}
	
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
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
bool APP_GetMeasure(float *_weight,MENU_Params *p_MenuParam){
	bool stable=false;
	int tempVal =0;
	*_weight = 12.3456; 
	float x=0;
	stable=true;
	
	switch(p_MenuParam->decimalPoint){
		case dp_0:
			break;
		case dp_0_0:
			tempVal = (*_weight)*10;
			x = tempVal*0.1;
			break;
		case dp_0_00:
			tempVal = (*_weight)*100;
			x = tempVal*0.01;
			break;
		case dp_0_000:
			tempVal = (*_weight)*1000;
			x = tempVal*0.001;
			break;
		case dp_0_0000:
			tempVal = (*_weight)*10000;
			x =  tempVal*0.0001;
			break;
	}
	*_weight = x;
	return stable;

	
	
}



//#############################################################################################
//                                           -------- 
//#############################################################################################

bool APP_Show_Weight(float *_weight,MENU_Params *p_MenuParam){
	uint8_t array[10]="";
	bool stable=false;
	uint8_t buffer[7]="";
	int len = 0;
	stable = APP_GetMeasure(_weight,p_MenuParam);
	
	switch(p_MenuParam->decimalPoint){
		case dp_0:
			if((*_weight) > 999999){(*_weight) =999999;}
			len = sprintf((char*)(&array[0]),"%d",(int)(*_weight));len+=1;
			break;
		case dp_0_0:
			if((*_weight) > 99999){(*_weight) =99999;}
			len = sprintf((char*)(&array[0]),"%.1f",(*_weight));
			break;
		case dp_0_00:
			if((*_weight) > 9999){(*_weight) =9999.9999;}
			len = sprintf((char*)(&array[0]),"%.2f",(*_weight));
			break;
		case dp_0_000:
			if((*_weight) > 999){(*_weight) =999.999;}
			len = sprintf((char*)(&array[0]),"%.3f",(*_weight));
			break;
		case dp_0_0000:
			if((*_weight) > 99){(*_weight) =99.9999;}
			len = sprintf((char*)(&array[0]),"%.4f",(*_weight));
			break;
	}
	for(int i=0;i<(7-len);i++){
		buffer[i]  =0x20; // add padding
	}
	strncat((char *)buffer,(const char *)array,len);

	p_LcdObj_S1->WriteString(0,0,(uint8_t *)buffer,&font_small,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	if(stable){
		p_LcdObj_S1->Spoint(16,1,p_LcdObj_S1); // stable icon on 
	  p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	}
	else{
		p_LcdObj_S1->Spoint(16,0,p_LcdObj_S1); // stable icon off 
	  p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	}
	
	return stable;
}


uint32_t _pow(uint32_t x,uint32_t y){
	uint32_t retVal=1;
	for(int i=0;i<y;i++){
		retVal *= x;
	}
	return retVal;
}


	
//#############################################################################################
//                                           END
//#############################################################################################