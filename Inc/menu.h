#ifndef __TEST_H__
#define __TEST_H__

typedef struct node
{
 void (*DoWorkDisplay)(void);
 struct node *enter;
 struct node *exit;
 struct node *up;
 struct node *down;
}node;


void shw_mainScreen();
void shw_calibration();
void shw_capacity();
void shw_decimalPoint();
void shw_resolution();
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
void shw_f2a_3();
void shw_f2b_6();
void shw_f2c_15();
void shw_f2d_30();
void shw_f3a();
void shw_f3b();
void shw_f3c();
void shw_f3d();
void shw_f3e();
void shw_f4a_fix();
void shw_f4b_flot();
void shw_f5a_slow();
void shw_f5b_normal();
void shw_f5c_fast();
void shw_f6a_1();
void shw_f6b_2();
void shw_f6c_5();
void shw_f6d_10();
void shw_f7a_on();
void shw_f7b_off();
#endif