#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "scale_v2.h"
#include "Inc/app.h"
#include "Inc/menu.h"
#define SAVE_EEPROOM_COMPANENT_SIZE											20
#define PLU_LEN																					100
#define EEPROM_ADDRESS_START                            0x19404
#define EEPROM_PLU_SAVE_ADDRESS                         0x1a404


#define FAC_VAL_RESOLUTION								r3000
#define FAC_VAL_CAPACITY									c3kg
#define FAC_VAL_DECIMAL_POINT		 		   		dp_0_0
#define FAC_VAL_FIXFLOAT									ff_fix
#define FAC_VAL_SPEED   									sp_medium
#define FAC_VAL_MINCOIN 									mc_1
#define FAC_VAL_MULTITARE									mt_on
#define FAC_VAL_ISN     									1234567
#define FAC_VAL_GRAVITY 									9.789
#define FAC_VAL_LIGHT 									  light_off
#define FAC_VAL_MODEL 									  model_2
#define FAC_VAL_RS232_BAUD 						 	  b_115200
#define FAC_VAL_RS232_MODE 							  lp50
#define FAC_VAL_RS232_PR 							    pr_8n1








void eeprom_write_array(uint32_t _address,uint32_t _array[],uint8_t _len);
bool eeprom_read_array(uint32_t _address,uint32_t _buffer[],uint8_t lngth);
void writeFlashMemoryInformation(MENU_Params *p_MenuParam);
void readFlashMemoryInformation(MENU_Params *p_MenuParam);
void InitFactorySetting(MENU_Params *p_MenuParam);


void writePluArray(uint32_t *_array);
void readPluArray(uint32_t *_array);

#endif