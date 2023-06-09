#include "Inc/keypad.h"
#include<stdlib.h>

#include "scale_v2.h"

//#############################################################################################
//                               GLOBAL VARIABLE & DEFINITONS
//#############################################################################################

KeyPad_t	KeyPad;

char keyboardMatris[KEYPAD_ROW_SIZE][KEYPAD_COLUMN_SIZE] = {
  {'0','.','c','z','t'},
  {'1','2','3','q','s'},
  {'4','5','6','p','u'},
  {'7','8','9','m','h'},
};

//#############################################################################################
//                                    USER FUNCTIONS
//#############################################################################################

KEYPAD *newKeyPadObj(){
	KEYPAD *p = (KEYPAD *)malloc(sizeof(KEYPAD));
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
	
	p->Init				        = &Init;
	p->Scan				        = &Scan;
	p->setColumnPin       = &setColumnPin;
	p->resetAllColumnPins = &resetAllColumnPins;
	p->ReadRowPin	        = &readRowPin;
	
	return p;
	
}
//#############################################################################################
static void Init(uint8_t _columnSize,uint8_t _rowSize){
  KeyPad.ColumnSize = _columnSize;
  KeyPad.RowSize = _rowSize;
#if (LOG_STATE)
     printf("KeyPad Initialized \n\n");
#endif

}
//#############################################################################################
static int16_t Scan(uint8_t *_longPress){
	char ret;
	uint32_t longPresCounter=0;
	*_longPress=0;
  for(uint8_t c=0 ; c<KeyPad.ColumnSize ; c++)
  {
    resetAllColumnPins();
    setColumnPin(c);
    for(uint8_t r=0 ; r<KeyPad.RowSize ; r++)
    {
      if(readRowPin(r) == 1)
      {
        _KEYPAD_DELAY(_KEYPAD_DEBOUNCE_TIME_MS);
        if(readRowPin(r) == 1){
					ret = keyboardMatris[r][c];
					while(readRowPin(r)){
						longPresCounter++;
						if(longPresCounter > 500000){
							*_longPress=1;
							return ret;
						}
					}
					return ret;
        }
      }
    }
  }
  return -1;
}



//#############################################################################################
static void resetAllColumnPins(void){
    column_P0 = 0;
    column_P1 = 0;
    column_P2 = 0;
    column_P3 = 0;
    column_P4 = 0;
}
//#############################################################################################
static void setColumnPin(uint8_t _sel){
    switch(_sel){
    case 0:
        column_P0 = 1;
        break;
    case 1:
        column_P1 = 1;
        break;
    case 2:
        column_P2 = 1;
        break;
    case 3:
        column_P3 = 1;
        break;
    case 4:
        column_P4 = 1;
        break;
    }
}
//#############################################################################################
static int8_t readRowPin(uint8_t _sel){
    switch(_sel){
    case 0:
        return row_P0;
    case 1:
        return row_P1;
    case 2:
        return row_P2;
    case 3:
        return row_P3;
    }
		return -1;
}

//#############################################################################################










//#############################################################################################
//                                           END
//#############################################################################################
