#include "Inc/menu.h"
#include "Inc/costumLcd.h"
#include "scale_v2.h"
#include <stdlib.h>
#include <stdio.h>
#include "Inc/app.h"
#include "Inc/keypad.h"
#include "Inc/SparkFun_NAU7802.h"
#include "Inc/eeproom.h"

extern AIP     * p_LcdObj_S1;
extern AIP     * p_LcdObj_S2;
extern AIP     * p_LcdObj_S3;
extern KEYPAD  * p_KeypadObj;
extern FontDef *p_CurrentFont;
extern MENU_Params m_Param;
extern SCALE  *p_ScaleObj;


RESOLUTION 		currentResolution;
CAPACITY   		currentCapacity;
DECIMAL_POINT currentDecimalPoint;
FIX_FLOAT			currnetFixFloat;
SPEED					currentSpeed;
MIN_COIN			currentMinCoin;
MULTI_TARE		currentMultiTare;

//#############################################################################################
//															Menü ROOT Fonks
//#############################################################################################

static void Enter(node **currentNode) { // Scale--->tare
   if((*currentNode)->enter != 0){
   		(*currentNode) = (*currentNode)->enter;
   		(*currentNode)->DoWorkDisplay();
   }
}

static void Exit(node **currentNode) { // Scale--->ero 
  if((*currentNode)->exit != 0){
 	 (*currentNode) = (*currentNode)->exit;
   	 (*currentNode)->DoWorkDisplay();
  	
  }
}

static void Up(node **currentNode){    // Scale--->M+
  if((*currentNode)->up != 0){
  	(*currentNode) = (*currentNode)->up;
   	(*currentNode)->DoWorkDisplay();
  	
  }
}

static void Down(node **currentNode){  // Scale--->PLU 
  if( (*currentNode) ->down != 0){
 	(*currentNode) = (*currentNode)->down;
    (*currentNode)->DoWorkDisplay();
  	
  }
}

void build(node *currentNode,void (*_DoWorkDisplay)(void),node *_enter,node *_exit,node *_up,node *_down){
	currentNode->enter = _enter;	
	currentNode->exit = _exit;	
	currentNode->up = _up;	
	currentNode->down = _down;	
	currentNode->DoWorkDisplay = _DoWorkDisplay;
	
}


//#############################################################################################
//															Menü Costum Fx
//#############################################################################################


node root;
node f0_cal,f0_save;
node f1_resolution, f1a_3000,f1b_6000,f1c_dual1,f1d_dual2,f1_save;
node f2_capacity, f2a_3,f2b_6,f2c_15,f2d_30,f2_save;
node f3_decimalPoint,f3a,f3b,f3c,f3d,f3e,f3_save;
node f4_fixFloat,f4a_fix,f4b_flot,f4_save;
node f5_speed,f5a_slow,f5b_normal,f5c_fast,f5_save;
node f6_minCoin,f6a_1,f6b_2,f6c_5,f6d_10,f6_save;
node f7_multiTare,f7a_on,f7b_off,f7_save;
node f8;
node f9_gravity,f9a;
node f10_reset,f10a;
node f11_rs232;


MENU *newMenuObj(){
	MENU *p = (MENU *)malloc(sizeof(MENU));
	if(p == NULL){
#if (LOG_STATE)
printf("Memory Allocation Failed (KEYPAD)\n");
#endif
		while(1);
	}else{
#if (LOG_STATE)
printf("Memory Allocation Successful. (KEYPAD) %d bytes used ! \n",sizeof(KEYPAD));
#endif
		
	}
	
	p->Init				          = &Menu_Init;
	p->Enter                =&Enter;
	p->Exit                 =&Exit;
	p->Up                   =&Up;
	p->Down                 =&Down;
	p->currentNode          =&root;
	return p;
	
}
static void Menu_Init(){

	// enter exit   up down 
	// First layer
	build(&root,&shw_mainScreen,&f0_cal,0,0,0);
	build(&f0_cal,&shw_calibration,&f0_save,&root,&f11_rs232,&f1_resolution);
	build(&f1_resolution,&shw_resolution,&f1a_3000,&root,&f0_cal,&f2_capacity);
	build(&f2_capacity,&shw_capacity,&f2a_3,&root,&f1_resolution,&f3_decimalPoint);
	build(&f3_decimalPoint,&shw_decimalPoint,&f3a,&root,&f2_capacity,&f4_fixFloat);
	build(&f4_fixFloat,&shw_fixFloat,&f4a_fix,&root,&f3_decimalPoint,&f5_speed);
	build(&f5_speed,&shw_speed,&f5a_slow,&root,&f4_fixFloat,&f6_minCoin);
	build(&f6_minCoin,&shw_minCoin,&f6a_1,&root,&f5_speed,&f7_multiTare);
	build(&f7_multiTare,&shw_multiTare,&f7a_on,&root,&f6_minCoin,&f8);
	build(&f8,&shw_f8,0,&root,&f7_multiTare,&f9_gravity);
	build(&f9_gravity,&shw_gravity,&f9a,&root,&f8,&f10_reset);
	build(&f10_reset,&shw_reset,&f10a,&root,&f9_gravity,&f11_rs232);
	build(&f11_rs232,&shw_rs232,0,&root,&f10_reset,&f0_cal);
	
	// enter exit   up down 
	// second layer 
	//  F0 branches
	build(&f0_save,&f0_Saved,0,&f0_cal,0,0);

	//  F1 branches
	build(&f1a_3000,&shw_f1a_3000,&f1_save,&f1_resolution,&f1d_dual2,&f1b_6000);
	build(&f1b_6000,&shw_f1b_6000,&f1_save,&f1_resolution,&f1a_3000,&f1c_dual1);
	build(&f1c_dual1,&shw_f1c_dual1,&f1_save,&f1_resolution,&f1b_6000,&f1d_dual2);
	build(&f1d_dual2,&shw_f1d_dual2,&f1_save,&f1_resolution,&f1c_dual1,&f1a_3000);
	build(&f1_save,&f1_Saved,0,&f1_resolution,0,0);
	//  F2 branches
	build(&f2a_3,&shw_f2a_3,&f2_save,&f2_capacity,&f2d_30,&f2b_6);
	build(&f2b_6,&shw_f2b_6,&f2_save,&f2_capacity,&f2a_3,&f2c_15);
	build(&f2c_15,&shw_f2c_15,&f2_save,&f2_capacity,&f2b_6,&f2d_30);
	build(&f2d_30,&shw_f2d_30,&f2_save,&f2_capacity,&f2c_15,&f2a_3);
	build(&f2_save,&f2_Saved,0,&f2_capacity,0,0);
	//  F3 branches   
	build(&f3a,&shw_f3a,&f3_save,&f3_decimalPoint,&f3e,&f3b);
	build(&f3b,&shw_f3b,&f3_save,&f3_decimalPoint,&f3a,&f3c);
	build(&f3c,&shw_f3c,&f3_save,&f3_decimalPoint,&f3b,&f3d);
	build(&f3d,&shw_f3d,&f3_save,&f3_decimalPoint,&f3c,&f3e);
	build(&f3e,&shw_f3e,&f3_save,&f3_decimalPoint,&f3d,&f3a);
	build(&f3_save,&f3_Saved,0,&f3_decimalPoint,0,0);
	//  F4 branches   
	build(&f4a_fix,&shw_f4a_fix,&f4_save,&f4_fixFloat,&f4b_flot,&f4b_flot);
	build(&f4b_flot,&shw_f4b_flot,&f4_save,&f4_fixFloat,&f4a_fix,&f4a_fix);
	build(&f4_save,&f4_Saved,0,&f4_fixFloat,0,0);
	//  F5 branches   
	build(&f5a_slow,&shw_f5a_slow,&f5_save,&f5_speed,&f5c_fast,&f5b_normal);
	build(&f5b_normal,&shw_f5b_normal,&f5_save,&f5_speed,&f5a_slow,&f5c_fast);
	build(&f5c_fast,&shw_f5c_fast,&f5_save,&f5_speed,&f5b_normal,&f5a_slow);
	build(&f5_save,&f5_Saved,0,&f5_speed,0,0);
	//  F6 branches    	 
	build(&f6a_1,&shw_f6a_1,&f6_save,&f6_minCoin,&f6d_10,&f6b_2);
	build(&f6b_2,&shw_f6b_2,&f6_save,&f6_minCoin,&f6a_1,&f6c_5);
	build(&f6c_5,&shw_f6c_5,&f6_save,&f6_minCoin,&f6b_2,&f6d_10);
	build(&f6d_10,&shw_f6d_10,&f6_save,&f6_minCoin,&f6c_5,&f6a_1);
	build(&f6_save,&f6_Saved,0,&f6_minCoin,0,0);
	//  F7 branches      
	build(&f7a_on,&shw_f7a_on,&f7_save,&f7_multiTare,&f7b_off,&f7b_off);
	build(&f7b_off,&shw_f7b_off,&f7_save,&f7_multiTare,&f7a_on,&f7a_on);
	build(&f7_save,&f7_Saved,0,&f7_multiTare,0,0);
	//  F9 branches      
	build(&f9a,&shw_f9a,0,&f9_gravity,0,0);
	//  F10 branches      
	build(&f10a,&shw_f10a,0,&f10_reset,0,0);
	
}
void shw_mainScreen(){
#if (LOG_STATE)
	printf("main screen\n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"000000",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"000000",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"000000",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	
}
void shw_calibration(){
	char array[10]="";
#if (LOG_STATE)
	printf("shw_calibration \n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F0",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"   CAL",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	sprintf((char*)(&array[0]),"%f",m_Param.calibrationFactor);
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)array,p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	
}
void shw_resolution(){
#if (LOG_STATE)
	printf("shw_resolution \n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F1",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"   rES",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	
	// enter exit   up down 	
	switch(m_Param.resolution){
		case r3000:
			build(&f1_resolution,&shw_resolution,&f1a_3000,&root,&f0_cal,&f2_capacity);
			break;
		case r6000:
			build(&f1_resolution,&shw_resolution,&f1b_6000,&root,&f0_cal,&f2_capacity);
			break;
		case rDual1:
			build(&f1_resolution,&shw_resolution,&f1c_dual1,&root,&f0_cal,&f2_capacity);
			break;
		case rDual2:
			build(&f1_resolution,&shw_resolution,&f1d_dual2,&root,&f0_cal,&f2_capacity);
			break;
	}
}
void shw_capacity(){
#if (LOG_STATE)
	printf("shw_capacity \n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F2",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"   CAP",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	
		
	switch(m_Param.capacity){
		case c3kg:
			build(&f2_capacity,&shw_capacity,&f2a_3,&root,&f1_resolution,&f3_decimalPoint);
			break;
		case c6kg:
			build(&f2_capacity,&shw_capacity,&f2b_6,&root,&f1_resolution,&f3_decimalPoint);
			break;
		case c15kg:
			build(&f2_capacity,&shw_capacity,&f2c_15,&root,&f1_resolution,&f3_decimalPoint);
			break;
		case c30kg:
			build(&f2_capacity,&shw_capacity,&f2d_30,&root,&f1_resolution,&f3_decimalPoint);
			break;
	}
}
void shw_decimalPoint(){
#if (LOG_STATE)
	printf("shw_decimalPoint \n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F3",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" PdECi",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);		
	switch(m_Param.decimalPoint){
		case dp_0:
			build(&f3_decimalPoint,&shw_decimalPoint,&f3a,&root,&f2_capacity,&f4_fixFloat);
			break;
		case dp_0_0:
			build(&f3_decimalPoint,&shw_decimalPoint,&f3b,&root,&f2_capacity,&f4_fixFloat);
			break;
		case dp_0_00:
			build(&f3_decimalPoint,&shw_decimalPoint,&f3c,&root,&f2_capacity,&f4_fixFloat);
			break;
		case dp_0_000:
			build(&f3_decimalPoint,&shw_decimalPoint,&f3d,&root,&f2_capacity,&f4_fixFloat);
			break;
		case dp_0_0000:
			build(&f3_decimalPoint,&shw_decimalPoint,&f3e,&root,&f2_capacity,&f4_fixFloat);
			break;
	}
}
void shw_fixFloat(){
#if (LOG_STATE)
	printf("shw_fixFloat \n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F4",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" PdESC",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	switch(m_Param.FixFloat){
		case ff_fix:
			build(&f4_fixFloat,&shw_fixFloat,&f4a_fix,&root,&f3_decimalPoint,&f5_speed);
			break;
		case ff_float:
			build(&f4_fixFloat,&shw_fixFloat,&f4b_flot,&root,&f3_decimalPoint,&f5_speed);
			break;
	}
}
void shw_speed(){
#if (LOG_STATE)
	printf("shw_speed \n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F5",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" SPEEd",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	switch(m_Param.speed){
		case sp_slow:
			build(&f5_speed,&shw_speed,&f5a_slow,&root,&f4_fixFloat,&f6_minCoin);
			break;
		case sp_medium:
			build(&f5_speed,&shw_speed,&f5b_normal,&root,&f4_fixFloat,&f6_minCoin);
			break;
		case sp_fast:
			build(&f5_speed,&shw_speed,&f5c_fast,&root,&f4_fixFloat,&f6_minCoin);
			break;
	}
}
void shw_minCoin(){
#if (LOG_STATE)
	printf("shw_minCoin \n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F6 Min",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"coin",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	switch(m_Param.minCoin){
		case mc_1:
			build(&f6_minCoin,&shw_minCoin,&f6a_1,&root,&f5_speed,&f7_multiTare);
			break;
		case mc_2:
			build(&f6_minCoin,&shw_minCoin,&f6b_2,&root,&f5_speed,&f7_multiTare);
			break;
		case mc_5:
			build(&f6_minCoin,&shw_minCoin,&f6c_5,&root,&f5_speed,&f7_multiTare);
			break;
		case mc_10:
			build(&f6_minCoin,&shw_minCoin,&f6d_10,&root,&f5_speed,&f7_multiTare);
			break;
	}
}
void shw_multiTare(){
#if (LOG_STATE)
	printf("shw_multiTare \n");
#endif
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F7",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"tare",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	switch(m_Param.multiTare){
		case mc_1:
			build(&f7_multiTare,&shw_multiTare,&f7a_on,&root,&f6_minCoin,&f8);
			break;
		case mc_2:
			build(&f7_multiTare,&shw_multiTare,&f7b_off,&root,&f6_minCoin,&f8);
			break;
	}
}
void shw_f8(){
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F8",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"   ISN",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
}
void shw_gravity(){
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F9",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"   GrA",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
}
void shw_reset(){
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F10",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" rESEt",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
}
void shw_rs232(){
	p_LcdObj_S1->WriteString(0,0,(uint8_t *)"F11",p_CurrentFont,p_LcdObj_S1);
	p_LcdObj_S1->UpdateScreen(p_LcdObj_S1);
	
	
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)"rS232",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	
	p_LcdObj_S3->ClearScreen(p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
}

void f0_Saved(){
  p_ScaleObj->calculateCalibrationFactor(1.00, 64);
	m_Param.calibrationFactor = p_ScaleObj->getCalibrationFactor();
	p_ScaleObj->calibrateAFE();
	writeFlashMemoryInformation(&m_Param);
}

void shw_f1a_3000(){
			p_LcdObj_S3->WriteString(0,0,(uint8_t *)"  3000",p_CurrentFont,p_LcdObj_S3);
			p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
			currentResolution = r3000;
}
void shw_f1b_6000(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"  6000",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
			currentResolution = r6000;
}
void shw_f1c_dual1(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)" dual1",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
			currentResolution = rDual1;
}
void shw_f1d_dual2(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)" dual2",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
			currentResolution = rDual2;
}
void f1_Saved(){
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" SAVEd ",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	m_Param.resolution = currentResolution;
	
}

void shw_f2a_3(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"   3KG",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentCapacity = c3kg;
}
void shw_f2b_6(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"   6KG",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentCapacity = c6kg;
}
void shw_f2c_15(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"  15KG",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentCapacity = c15kg;
}
void shw_f2d_30(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"  30KG",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentCapacity = c30kg;
}
void f2_Saved(){
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" SAVEd ",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	m_Param.capacity = currentCapacity;
	
}
void shw_f3a(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"     0",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentDecimalPoint = dp_0;
}
void shw_f3b(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"    0.0",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentDecimalPoint = dp_0_0;
}
void shw_f3c(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"   0.00",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentDecimalPoint = dp_0_00;
}
void shw_f3d(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"  0.000",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentDecimalPoint = dp_0_000;
}
void shw_f3e(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)" 0.0000",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentDecimalPoint = dp_0_0000;
}
void f3_Saved(){
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" SAVEd ",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	m_Param.decimalPoint = currentDecimalPoint;
	
}
void shw_f4a_fix(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"   FIX",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currnetFixFloat=ff_fix;
}
void shw_f4b_flot(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)" FLOAT",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currnetFixFloat=ff_float;
}

void f4_Saved(){
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" SAVEd ",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	m_Param.FixFloat = currnetFixFloat;
	
}
void shw_f5a_slow(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"  Slow",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentSpeed=sp_slow;
}
void shw_f5b_normal(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"Medium",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentSpeed=sp_medium;
}
void shw_f5c_fast(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"  Fast",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentSpeed=sp_fast;
}
void f5_Saved(){
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" SAVEd ",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	m_Param.speed = currentSpeed;
	
}
void shw_f6a_1(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"     1",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentMinCoin=mc_1;
}
void shw_f6b_2(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"     2",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentMinCoin=mc_2;
}
void shw_f6c_5(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"     5",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentMinCoin=mc_5;
}
void shw_f6d_10(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"    10",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentMinCoin=mc_10;
}
void f6_Saved(){
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" SAVEd ",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	m_Param.minCoin = currentMinCoin;
	
}
void shw_f7a_on(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"    ON",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentMultiTare = mt_on;
}
void shw_f7b_off(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"   OFF",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	currentMultiTare = mt_off;
}

void f7_Saved(){
	p_LcdObj_S2->WriteString(0,0,(uint8_t *)" SAVEd ",p_CurrentFont,p_LcdObj_S2);
	p_LcdObj_S2->UpdateScreen(p_LcdObj_S2);
	m_Param.multiTare = currentMultiTare;
	
}
void shw_f9a(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"9.8474",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
	int16_t pressedKey=0;
	uint8_t longPres=0;
	float ret=0;
	while(1){
		pressedKey = p_KeypadObj->Scan(&longPres);
		if(pressedKey > -1){
			ret =customValueInput(pressedKey,p_LcdObj_S3); // Bu fx girilen degeri float return ediyor !  
			if(pressedKey == 't'){
				 m_Param.gravity = ret;
				return; // kaydet ve cik !! 
			}
		}
	}
}
void shw_f10a(){
	p_LcdObj_S3->WriteString(0,0,(uint8_t *)"rest",p_CurrentFont,p_LcdObj_S3);
	p_LcdObj_S3->UpdateScreen(p_LcdObj_S3);
}

















