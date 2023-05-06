#include "Inc/keypad.h"
#include<stdlib.h>

#include "scale_v1.h"

//#############################################################################################
//                               GLOBAL VARIABLE & DEFINITONS
//#############################################################################################

KeyPad_t	KeyPad;


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
	
	p->Init				       = &Init;
	p->Scan				       = &Scan;
	p->SetAllColumnPins  = &setAllColumnPins;
	p->ResetColumnPin	   = &resetColumnPin;
	p->ReadRowPin	       = &readRowPin;
	
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
static uint32_t Scan(void){
	 volatile uint32_t  key=0,counter=0;
  for(uint8_t c=0 ; c<KeyPad.ColumnSize ; c++)
  {
    setAllColumnPins();
    resetColumnPin(c);
    for(uint8_t r=0 ; r<KeyPad.RowSize ; r++)
    {
      if(readRowPin(r) == 0)
      {
        _KEYPAD_DELAY(_KEYPAD_DEBOUNCE_TIME_MS);
        if(readRowPin(r) == 0)
        {
          key |= 1<<c;
          key |= 1<<(r+8);
          while(readRowPin(r) == 0){
						counter++;
						if(counter>100000){
							key = key | 0x10000000;
							break;
						}
					}
          return key;
        }
      }
    }
  }
  return key;
}



//#############################################################################################
static void setAllColumnPins(void){
    column_P0 = 1;
    column_P1 = 1;
    column_P2 = 1;
    column_P3 = 1;
    column_P4 = 1;
}
//#############################################################################################
static void resetColumnPin(uint8_t _sel){
    switch(_sel){
    case 0:
        column_P0 = 0;
        break;
    case 1:
        column_P1 = 0;
        break;
    case 2:
        column_P2 = 0;
        break;
    case 3:
        column_P3 = 0;
        break;
    case 4:
        column_P4 = 0;
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
