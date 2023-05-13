#ifndef __COSTUMLCD_H__
#define __COSTUMLCD_H__



#include <stdint.h>
#include "Inc/font.h"


//#############################################################################################
//                               GLOBAL VARIABLE & DEFINITONS
//#############################################################################################

#define WIDTH		19
#define HEIGHT		 4
#define BUFF_SIZE   (WIDTH*HEIGHT/4)




//#############################################################################################
//                                     TYPEDEF DEFINITION
//#############################################################################################

typedef struct FontDef{
	const uint8_t FontWidth;  
	uint8_t FontHeight;    
	const uint16_t *data; 
} FontDef;

typedef struct Ai_position{
	uint8_t x_pos; 
	uint8_t y_pos; // dont use 
	
}Ai_position;

typedef struct Params{
	void (*Cs)(uint8_t);
	void (*Reset)(uint8_t);
	void (*A0)(uint8_t);
	uint8_t ramB[BUFF_SIZE];
}Params;

typedef struct AIP{
	
	void (*Init)(struct AIP *);
	void (*WriteData)(uint8_t *,uint8_t,struct AIP *);
	void (*WriteCommand)(uint8_t,struct AIP *);
	void (*ClearScreen)(struct AIP *);
	void (*UpdateScreen)(struct AIP *);
	void (*DrawPixel)(uint8_t,uint8_t,uint8_t,struct AIP *);
	uint8_t (*WriteChar) (uint8_t *,FontDef *,struct AIP *);
	void (*SetCursor)(uint8_t,uint8_t,struct AIP *);
	void (*WriteString)(uint8_t, uint8_t,uint8_t *, FontDef *,struct AIP *);
	void (*WriteStringLen)(uint8_t, uint8_t,uint8_t *, FontDef *,struct AIP *,uint8_t);
	void (*Spoint)(uint8_t,uint8_t,struct AIP *);
	void (*WriteNumber) (uint8_t,uint8_t,FontDef *,struct AIP *);
	void (*Cs)(uint8_t);
	void (*Reset)(uint8_t);
	void (*A0)(uint8_t);
	uint8_t * ptrRam;
	Ai_position AIP_currentPos;

}AIP;

//#############################################################################################
//                                    USER FUNCTIONS
//#############################################################################################

AIP *newLCDObj(Params *_params);
static uint8_t spi_transfer(uint8_t *_data);
static void AIP_Init(AIP *p);
static void AIP_writeData(uint8_t *data,uint8_t len,AIP *p);
static void AIP_writeCommand(uint8_t _cmd,AIP *p);
static void AIP_ClearScreen(AIP *p);
static void AIP_UpdateScreen(AIP *p);
static void AIP_draw_pixel(uint8_t x,uint8_t y,uint8_t color,AIP *p);
static uint8_t AIP_writeChar(uint8_t *_chr,FontDef *Font,AIP *p);
static void AIP_SetCursor(uint8_t _x,uint8_t _y,AIP *p);
static void AIP_WriteString(uint8_t x, uint8_t y,uint8_t * str, FontDef *Font,AIP *p);
static void AIP_WriteStringLen(uint8_t x, uint8_t y,uint8_t * str, FontDef *Font,AIP *p,uint8_t _len) ;
static void AIP_Spoint(uint8_t _id,uint8_t _val,AIP *p);
static void AIP_writeNumber(uint8_t _number,uint8_t _state,FontDef *Font,AIP *p);

void  SCREEN_1_AIP_ResetPin(uint8_t _val);
void  SCREEN_1_AIP_A0Pin(uint8_t _val);
void  SCREEN_1_AIP_CSPin(uint8_t _val);
void  SCREEN_2_AIP_ResetPin(uint8_t _val);
void  SCREEN_2_AIP_A0Pin(uint8_t _val);
void  SCREEN_2_AIP_CSPin(uint8_t _val);
void  SCREEN_3_AIP_ResetPin(uint8_t _val);
void  SCREEN_3_AIP_A0Pin(uint8_t _val);
void  SCREEN_3_AIP_CSPin(uint8_t _val);

//#############################################################################################
//                                           END
//#############################################################################################

#endif