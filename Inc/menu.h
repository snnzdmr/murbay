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
	sp_slow=0,
	sp_medium,
	sp_fast
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

typedef struct RS232_Params{
	uint32_t baudrate;
	uint8_t parity;
	uint8_t stop;
	uint8_t word;
}RS232_Params;
	
typedef struct MENU_Params{
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
#endif