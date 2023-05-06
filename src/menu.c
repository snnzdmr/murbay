#include "Inc/menu.h"


//#############################################################################################
//															Menü ROOT Fonks
//#############################################################################################

void Menu_Enter(node **currentNode) { // Scale--->tare
   if((*currentNode)->enter != 0){
   		(*currentNode) = (*currentNode)->enter;
   		(*currentNode)->DoWorkDisplay();
   }
}

void Menu_Exit(node **currentNode) { // Scale--->ero 
  if((*currentNode)->exit != 0){
 	 (*currentNode) = (*currentNode)->exit;
   	 (*currentNode)->DoWorkDisplay();
  	
  }
}

void Menu_Up(node **currentNode){    // Scale--->M+
  if((*currentNode)->up != 0){
  	(*currentNode) = (*currentNode)->up;
   	(*currentNode)->DoWorkDisplay();
  	
  }
}

void Menu_Down(node **currentNode){  // Scale--->PLU 
  if( (*currentNode) ->down != 0){
 	(*currentNode) = (*currentNode)->down;
    (*currentNode)->DoWorkDisplay();
  	
  }
}

void buildMenu(node *currentNode,void (*_DoWorkDisplay)(void),node *_enter,node *_exit,node *_up,node *_down){
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
node f0_cal;
node f1_resolution, f1a_3000,f1b_6000,f1c_dual1,f1d_dual2;
node f2_capacity, f2a_3,f2b_6,f2c_15,f2d_30;
node f3_decimalPoint,f3a,f3b,f3c,f3d,f3e;
node f4_fixFloat,f4a_fix,f4b_flot;
node f5_speed,f5a_slow,f5b_normal,f5c_fast;
node f6_minCoin,f6a_1,f6b_2,f6c_5,f6d_10;
node f7_multiTare,f7a_on,f7b_off;
node f8;
node f9_gravity;
node f10_reset;
node f11_rs232;


void Menu_Init(){
	
	node * currentNode=&root;
	// enter exit   up down 
	// First layer
	buildMenu(&root,&shw_mainScreen,&f0_cal,0,0,0);
	buildMenu(&f0_cal,&shw_calibration,0,&root,&f11_rs232,&f1_resolution);
	buildMenu(&f1_resolution,&shw_resolution,&f1a_3000,&root,&f0_cal,&f2_capacity);
	buildMenu(&f2_capacity,&shw_capacity,&f2a_3,&root,&f1_resolution,&f3_decimalPoint);
	buildMenu(&f3_decimalPoint,&shw_decimalPoint,&f3a,&root,&f2_capacity,&f4_fixFloat);
	buildMenu(&f4_fixFloat,&shw_resolution,&f4a_fix,&root,&f3_decimalPoint,&f5_speed);
	buildMenu(&f5_speed,&shw_speed,&f5a_slow,&root,&f5a_slow,&f6_minCoin);
	buildMenu(&f6_minCoin,&shw_minCoin,&f6a_1,&root,&f4_fixFloat,&f7_multiTare);
	buildMenu(&f7_multiTare,&shw_multiTare,&f7a_on,&root,&f5_speed,&f8);
	buildMenu(&f8,&shw_f8,0,&root,&f6_minCoin,&f9_gravity);
	buildMenu(&f9_gravity,&shw_gravity,0,&root,&f7_multiTare,&f10_reset);
	buildMenu(&f10_reset,&shw_reset,0,&root,&f8,&f11_rs232);
	buildMenu(&f11_rs232,&shw_rs232,0,&root,&f9_gravity,&f0_cal);
	
	// enter exit   up down 
	// second layer 
	//  F0 branches

	//  F1 branches
	buildMenu(&f1a_3000,&shw_f1a_3000,0,&f1_resolution,&f1d_dual2,&f1b_6000);
	buildMenu(&f1b_6000,&shw_f1b_6000,0,&f1_resolution,&f1a_3000,&f1c_dual1);
	buildMenu(&f1c_dual1,&shw_f1c_dual1,0,&f1_resolution,&f1b_6000,&f1d_dual2);
	buildMenu(&f1d_dual2,&shw_f1d_dual2,0,&f1_resolution,&f1c_dual1,&f1a_3000);
	//  F2 branches
	buildMenu(&f2a_3,&shw_f2a_3,0,&f2_capacity,&f2d_30,&f2b_6);
	buildMenu(&f2b_6,&shw_f2b_6,0,&f2_capacity,&f2a_3,&f2c_15);
	buildMenu(&f2c_15,&shw_f2c_15,0,&f2_capacity,&f2b_6,&f2d_30);
	buildMenu(&f2d_30,&shw_f2d_30,0,&f2_capacity,&f2c_15,&f2a_3);
	//  F3 branches   
	buildMenu(&f3a,&shw_f3a,0,&f3_decimalPoint,&f3e,&f3b);
	buildMenu(&f3b,&shw_f3b,0,&f3_decimalPoint,&f3a,&f3c);
	buildMenu(&f3c,&shw_f3c,0,&f3_decimalPoint,&f3b,&f3d);
	buildMenu(&f3d,&shw_f3d,0,&f3_decimalPoint,&f3c,&f3e);
	buildMenu(&f3e,&shw_f3e,0,&f3_decimalPoint,&f3d,&f3a);
	//  F4 branches   
	buildMenu(&f4a_fix,&shw_f4a_fix,0,&f4_fixFloat,&f4b_flot,&f4b_flot);
	buildMenu(&f4b_flot,&shw_f4b_flot,0,&f4_fixFloat,&f4a_fix,&f4a_fix);
	//  F5 branches   
	buildMenu(&f5a_slow,&shw_f5a_slow,0,&f5_speed,&f5c_fast,&f5b_normal);
	buildMenu(&f5b_normal,&shw_f5b_normal,0,&f5_speed,&f5a_slow,&f5c_fast);
	buildMenu(&f5c_fast,&shw_f5c_fast,0,&f5_speed,&f5b_normal,&f5a_slow);
	//  F6 branches    	 
	buildMenu(&f6a_1,&shw_f6a_1,0,&f6_minCoin,&f6d_10,&f6b_2);
	buildMenu(&f6b_2,&shw_f6b_2,0,&f6_minCoin,&f6a_1,&f6c_5);
	buildMenu(&f6c_5,&shw_f6c_5,0,&f6_minCoin,&f6b_2,&f6d_10);
	buildMenu(&f6d_10,&shw_f6d_10,0,&f6_minCoin,&f6c_5,&f6a_1);
	//  F7 branches      
	buildMenu(&f7a_on,&shw_f7a_on,0,&f7_multiTare,&f7b_off,&f7b_off);
	buildMenu(&f7b_off,&shw_f7b_off,0,&f7_multiTare,&f7a_on,&f7a_on);
	

}


void shw_mainScreen(){
	printf("main screen\n");
}
void shw_calibration(){
	printf("shw_calibration \n");
}
void shw_resolution(){
	printf("shw_resolution \n");
}
void shw_capacity(){
	printf("shw_capacity \n");
}
void shw_decimalPoint(){
	printf("shw_decimalPoint \n");
}
void shw_fixFloat(){
	printf("shw_fixFloat \n");
}
void shw_speed(){
	printf("shw_speed \n");
}
void shw_minCoin(){
	printf("shw_minCoin \n");
}
void shw_multiTare(){
	printf("shw_multiTare \n");
}
void shw_f8(){
	printf("shw_f8 \n");
}
void shw_gravity(){
	printf("shw_gravity \n");
}
void shw_reset(){
	printf("shw_reset \n");
}
void shw_rs232(){
	printf("shw_rs232 \n");
}
void shw_f1a_3000(){
	printf("shw_f1a_3000 \n");
}
void shw_f1b_6000(){
	printf("shw_f1b_6000 \n");
}
void shw_f1c_dual1(){
	printf("shw_f1c_dual1 \n");
}
void shw_f1d_dual2(){
	printf("shw_f1d_dual2 \n");
}
void shw_f2a_3(){
	printf("shw_f2a_3 \n");
}
void shw_f2b_6(){
	printf("shw_f2b_6 \n");
}
void shw_f2c_15(){
	printf("shw_f2c_15 \n");
}
void shw_f2d_30(){
	printf("shw_f2d_30 \n");
}
void shw_f3a(){
	printf("shw_f3a \n");
}
void shw_f3b(){
	printf("shw_f3b \n");
}
void shw_f3c(){
	printf("shw_f3c \n");
}
void shw_f3d(){
	printf("shw_f3d \n");
}
void shw_f3e(){
	printf("shw_f3e \n");
}
void shw_f4a_fix(){
	printf("shw_f4a_fix \n");
}
void shw_f4b_flot(){
	printf("shw_f4b_flot \n");
}
void shw_f5a_slow(){
	printf("shw_f5a_slow \n");
}
void shw_f5b_normal(){
	printf("shw_f5b_normal \n");
}
void shw_f5c_fast(){
	printf("shw_f5c_fast \n");
}
void shw_f6a_1(){
	printf("shw_f6a_1 \n");
}
void shw_f6b_2(){
	printf("shw_f6b_2 \n");
}
void shw_f6c_5(){
	printf("shw_f6c_5 \n");
}
void shw_f6d_10(){
	printf("shw_f6d_10 \n");
}
void shw_f7a_on(){
	printf("shw_f7a_on \n");
}
void shw_f7b_off(){
	printf("shw_f7b_off \n");
}

