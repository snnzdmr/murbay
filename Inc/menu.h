#ifndef __TEST_H__
#define __TEST_H__


#include <stdint.h>



typedef struct node
{
 void (*DoWorkDisplay)(void);
 struct node *enter;
 struct node *exit;
 struct node *up;
 struct node *down;
}node;


typedef struct MENU{
	void (*Init)();
	void (*Enter)(node **);
	void (*Exit)(node **);
	void (*Up)(node **);
	void (*Down)(node **);
	node *currentNode;
}MENU;

typedef enum RESOLUTION{
	r3000=0,
	r6000,
	rDual1,
	rDual2
}RESOLUTION;

typedef enum CAPACITY{
	c3kg=0,
	c6kg,
	c15kg,
	c30kg
}CAPACITY;

typedef enum DECIMAL_POINT{
	dp_0=0,
	dp_0_0,
	dp_0_00,
	dp_0_000,
	dp_0_0000
}DECIMAL_POINT;
typedef enum FIX_FLOAT{
	ff_fix=0,
	ff_float,
}FIX_FLOAT;
typedef enum SPEED{
	sp_fast=1,
	sp_medium,
	sp_slow
}SPEED;
typedef enum MIN_COIN{
	mc_1=0,
	mc_2,
	mc_5,
	mc_10
}MIN_COIN;
typedef enum MULTI_TARE{
	mt_on=0,
	mt_off
}MULTI_TARE;

typedef enum LIGHT{
	light_on=0,
	light_off,
	light_auto
}LIGHT;


typedef enum MODEL{
	model_1=0,
	model_2,
	model_3
}MODEL;

typedef enum RS232_MODE{
	printer=0,
	tpup,
	lp50,
	pos,
	off,
	cont,
	stc,
	toledo,
	nciecr,
	ncigen,
	tec,
	easy
}RS232_MODE;

typedef enum RS232_BAUD{
	b_1200=0,
	b_2400,
	b_4800,
	b_9600,
	b_19200,
	b_38400,
	b_115200
}RS232_BAUD;
typedef enum RS232_PR{
	pr_8n1 =0,
	pr_7E1,
	pr_7o1
}RS232_PR;
typedef struct RS232_Params{
	RS232_BAUD baudrate;
	RS232_PR parity;
	RS232_MODE mode;
}RS232_Params;
	
typedef struct MENU_Params{
	float calibrationFactor;
	int32_t ZeroOffset;
	uint8_t resolution;
	uint8_t capacity;
	uint8_t decimalPoint;
	uint8_t FixFloat;
	uint8_t speed;
	uint8_t minCoin;
	uint8_t multiTare;
	uint32_t isn;
	float gravity;
	uint8_t factoryReset;
	RS232_Params rs232Param;
	uint8_t light;
	uint8_t model;
}MENU_Params;

MENU *newMenuObj();
static void Enter(node **currentNode); // Scale--->tare
static void Exit(node **currentNode); // Scale--->ero 
static void Up(node **currentNode);    // Scale--->M+
static void Down(node **currentNode);
static void Menu_Init();

void shw_mainScreen();
void shw_calibration();
void shw_resolution();
void shw_capacity();
void shw_decimalPoint();
void shw_fixFloat();
void shw_speed();
void shw_minCoin();
void shw_multiTare();
void shw_f8();
void shw_gravity();
void shw_reset();
void shw_rs232();

void shw_f0_unload();
void shw_f0_capload();
void f0_Saved();



void shw_f1a_3000();
void shw_f1b_6000();
void shw_f1c_dual1();
void shw_f1d_dual2();
void f1_Saved();
void shw_f2a_3();
void shw_f2b_6();
void shw_f2c_15();
void shw_f2d_30();
void f2_Saved();
void shw_f3a();
void shw_f3b();
void shw_f3c();
void shw_f3d();
void shw_f3e();
void f3_Saved();
void shw_f4a_fix();
void shw_f4b_flot();
void f4_Saved();
void shw_f5a_slow();
void shw_f5b_normal();
void shw_f5c_fast();
void f5_Saved();
void shw_f6a_1();
void shw_f6b_2();
void shw_f6c_5();
void shw_f6d_10();
void f6_Saved();
void shw_f7a_on();
void shw_f7b_off();
void f7_Saved();
void shw_f9a();
void shw_f10a();


void shw_light();
void shw_f12a_auto();
void shw_f12b_on();
void shw_f12c_off();
void f12_Saved();

void shw_model();
void shw_f13a();
void shw_f13b();
void shw_f13c();
void f13_Saved();

void shw_f11a_mode();
void shw_f11b_baud();
void shw_f11c_pr();
		
void shw_f11a1printer();
void shw_f11a2tpup();
void shw_f11a3lp50();
void shw_f11a4pos();
void shw_f11a5off();
void shw_f11a6cont();
void shw_f11a7stc();
void shw_f11a8toledo();
void shw_f11a9nciecr();
void shw_f11a10ncigen();
void shw_f11a11tec();
void shw_f11a12easy();
		
void shw_f11b1_1200();
void shw_f11b2_2400();
void shw_f11b3_4800();
void shw_f11b4_9600();
void shw_f11b5_19200();
void shw_f11b6_38400();
void shw_f11b7_115200();

void shw_f11c1_8n1();
void shw_f11c2_7e1();
void shw_f11c3_701();
	
void f11a_mode_Saved();
void f11b_baud_Saved();
void f11c_pr_Saved();

#endif