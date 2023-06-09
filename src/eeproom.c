#include "Inc/eeproom.h"
#include <stdint.h>
#include <stdbool.h>


#define FAC_VAL_RESOLUTION								r3000
#define FAC_VAL_CAPACITY									c3kg
#define FAC_VAL_DECIMAL_POINT		 		   		dp_0_0
#define FAC_VAL_FIXFLOAT									ff_fix
#define FAC_VAL_SPEED   									sp_medium
#define FAC_VAL_MINCOIN 									mc_1
#define FAC_VAL_MULTITARE									mt_on
#define FAC_VAL_ISN     									1234567
#define FAC_VAL_GRAVITY 									9.789
#define FAC_VAL_ZERO_OFSET								0
#define FAC_VAL_CAL_FAC										216903

void eeprom_write_array(uint32_t _address,uint32_t _array[],uint8_t _len){
    uint8_t i=0;
	
		SYS_UnlockReg();
		FMC_Open();
		FMC_EnableAPUpdate();
		FMC_Erase(_address);   	
	  FMC_Write(_address,_len);
    for(i=0;i<_len;i++){
				_address+=4;
        FMC_Write(_address,_array[i]);
#if (PRINT_ON_OF)
			//	printf("EEPROM WRITE ADDRESS : %d, VALUE : ->0x%x<-\n",_address,(int)_array[i]);// 
#endif
    }
		FMC_DisableAPUpdate();
		FMC_Close();
		SYS_LockReg();
}
bool eeprom_read_array(uint32_t _address,uint32_t _buffer[],uint8_t lngth){
	
		SYS_UnlockReg();
		FMC_Open();
		FMC_EnableAPUpdate();
    uint32_t _len=FMC_Read(_address);
#if (PRINT_ON_OF)
	  printf("lennnnnnnnnnnnnn : %d\n",(int)_len);
#endif
		if(_len != lngth){
			return false;
		}
    uint8_t i=0;
    for ( i = 0; i < _len; i++)
    {
			_address+=4;
			_buffer[i] = FMC_Read(_address);
#if (PRINT_ON_OF)
			printf("EEPROM_READ ADDRESS : %d, VALUE :->0x%x<-\n",_address,_buffer[i]);
#endif
    }
		FMC_Close();

		return true;
}


void writeFlashMemoryInformation(MENU_Params *p_MenuParam){
	uint32_t _buffer[SAVE_EEPROOM_COMPANENT_SIZE+1];
	_buffer[0]  = p_MenuParam->resolution;
	_buffer[1]  = p_MenuParam->capacity;
	_buffer[2]  = p_MenuParam->decimalPoint; 
	_buffer[3]  = p_MenuParam->FixFloat;
	_buffer[4]  = p_MenuParam->speed;
	_buffer[5]  = p_MenuParam->minCoin;
	_buffer[6]  = p_MenuParam->multiTare;
	_buffer[7]  = p_MenuParam->isn;
	_buffer[8]  = p_MenuParam->gravity;
	_buffer[9]  = p_MenuParam->calibrationFactor;
	_buffer[10] =	p_MenuParam->ZeroOffset;
	
	_buffer[11] =	p_MenuParam->light;
	_buffer[12] =	p_MenuParam->model;
	_buffer[13] =	p_MenuParam->rs232Param.baudrate;
	_buffer[14] =	p_MenuParam->rs232Param.mode;
	_buffer[15] =	p_MenuParam->rs232Param.parity;
  eeprom_write_array((uint32_t)EEPROM_ADDRESS_START,&_buffer[0],SAVE_EEPROOM_COMPANENT_SIZE);
}
void readFlashMemoryInformation(MENU_Params *p_MenuParam){
	uint32_t _buffer[SAVE_EEPROOM_COMPANENT_SIZE+1];
	if(eeprom_read_array((uint32_t)EEPROM_ADDRESS_START,&_buffer[0],SAVE_EEPROOM_COMPANENT_SIZE) == true){
		p_MenuParam->resolution        = _buffer[0];
		p_MenuParam->capacity          = _buffer[1];
		p_MenuParam->decimalPoint      = _buffer[2];
		p_MenuParam->FixFloat          = _buffer[3];
		p_MenuParam->speed             = _buffer[4];
		p_MenuParam->minCoin           = _buffer[5];
		p_MenuParam->multiTare         = _buffer[6];
		p_MenuParam->isn               = _buffer[7];
		p_MenuParam->gravity           = _buffer[8];
		p_MenuParam->calibrationFactor = _buffer[9];
		p_MenuParam->ZeroOffset        = _buffer[10];
		p_MenuParam->light             = _buffer[11];
		p_MenuParam->model             = _buffer[12];
		p_MenuParam->rs232Param.baudrate             = _buffer[13];
		p_MenuParam->rs232Param.mode                 = _buffer[14];
		p_MenuParam->rs232Param.parity               = _buffer[15];
		
	}
	else{
		InitFactorySetting(p_MenuParam);
	}
}
void InitFactorySetting(MENU_Params *p_MenuParam){
		p_MenuParam->resolution        = FAC_VAL_RESOLUTION;
		p_MenuParam->capacity          = FAC_VAL_CAPACITY;
		p_MenuParam->decimalPoint      = FAC_VAL_DECIMAL_POINT;
		p_MenuParam->FixFloat          = FAC_VAL_FIXFLOAT;
		p_MenuParam->speed             = FAC_VAL_SPEED;
		p_MenuParam->minCoin           = FAC_VAL_MINCOIN;
		p_MenuParam->multiTare         = FAC_VAL_MULTITARE;
		p_MenuParam->isn               = FAC_VAL_ISN;
		p_MenuParam->gravity           = FAC_VAL_GRAVITY;
		p_MenuParam->calibrationFactor = FAC_VAL_CAL_FAC;
		p_MenuParam->ZeroOffset        = FAC_VAL_ZERO_OFSET;
		p_MenuParam->light             = FAC_VAL_LIGHT;
		p_MenuParam->model             = FAC_VAL_MODEL;
		p_MenuParam->rs232Param.baudrate             = FAC_VAL_RS232_BAUD;
		p_MenuParam->rs232Param.mode                 = FAC_VAL_RS232_MODE;
		p_MenuParam->rs232Param.parity               = FAC_VAL_RS232_PR;
	
	
		writeFlashMemoryInformation(p_MenuParam);
}



void writePluArray(uint32_t *_array){
	eeprom_write_array(EEPROM_PLU_SAVE_ADDRESS,_array,PLU_LEN);
}
void readPluArray(uint32_t *_array){
	eeprom_read_array(EEPROM_PLU_SAVE_ADDRESS,_array,PLU_LEN);
}


