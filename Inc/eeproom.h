#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "scale_v2.h"
#include "Inc/app.h"
#include "Inc/menu.h"
#define SAVE_EEPROOM_COMPANENT_SIZE				20
#define EEPROM_ADDRESS_START                            0x19404


#define FAC_VAL_RESOLUTION								r3000
#define FAC_VAL_CAPACITY									c3kg
#define FAC_VAL_DECIMAL_POINT		 		   		dp_0_0
#define FAC_VAL_FIXFLOAT									ff_fix
#define FAC_VAL_SPEED   									sp_medium
#define FAC_VAL_MINCOIN 									mc_1
#define FAC_VAL_MULTITARE									mt_on
#define FAC_VAL_ISN     									1234567
#define FAC_VAL_GRAVITY 									9.789











void eeprom_write_array(uint32_t _address,uint32_t _array[],uint8_t _len);
bool eeprom_read_array(uint32_t _address,uint32_t _buffer[]);
void writeFlashMemoryInformation(MENU_Params *p_MenuParam);
void readFlashMemoryInformation(MENU_Params *p_MenuParam);
void InitFactorySetting(MENU_Params *p_MenuParam);

#endif