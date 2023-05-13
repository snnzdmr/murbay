#ifndef __KEYPAD_H__
#define __KEYPAD_H__


#include <stdint.h>
#include <stdbool.h>


//#############################################################################################
//                               GLOBAL VARIABLE & DEFINITONS
//#############################################################################################

#define KEYPAD_COLUMN_SIZE      5
#define KEYPAD_ROW_SIZE         4

#define   _KEYPAD_DEBOUNCE_TIME_MS        20
#define 	_KEYPAD_DELAY(x)      					CLK_SysTickDelay(x*1000); 

#define column_P0     PA7     // OUTPUT
#define column_P1     PC6      // OUTPUT
#define column_P2     PC2      // OUTPUT
#define column_P3     PD3      // OUTPUT
#define column_P4     PD2      // OUTPUT


#define row_P0        PC0
#define row_P1        PD1
#define row_P2        PD0
#define row_P3        PA12


//#############################################################################################
//                                     TYPEDEF DEFINITION
//#############################################################################################


typedef struct
{
	uint8_t   ColumnSize;
	uint8_t   RowSize;
	uint16_t  LastKey;

}KeyPad_t;

typedef struct KEYPAD{
	void (*Init)(uint8_t,uint8_t);
	int16_t (*Scan)(uint8_t *);
	void (*setColumnPin)(uint8_t);
	void (*resetAllColumnPins)(void);
	int8_t (*ReadRowPin)(uint8_t);
}KEYPAD;



//#############################################################################################
//                                    USER FUNCTIONS
//#############################################################################################


KEYPAD *newKeyPadObj();
static void Init(uint8_t _columnSize,uint8_t _rowSize);
static int16_t Scan(uint8_t *_longPress);
// uint16_t  KeyPad_WaitForKey(uint32_t	Timeout_ms);
//char KeyPad_WaitForKeyGetChar(uint32_t	Timeout_ms);

static void setColumnPin(uint8_t _sel);
static void resetAllColumnPins(void);
static int8_t readRowPin(uint8_t _sel);





//#############################################################################################
//                                           END
//#############################################################################################
#endif
