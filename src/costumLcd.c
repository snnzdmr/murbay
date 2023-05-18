
#include "Inc/costumLcd.h"
#include "scale_v2.h"
#include <stdlib.h>


//#############################################################################################
//                                    USER FUNCTIONS
//#############################################################################################


//#############################################################################################
__WEAK void  SCREEN_1_AIP_ResetPin(uint8_t _val){
	// Weak definitions
}
//#############################################################################################
__WEAK void  SCREEN_1_AIP_A0Pin(uint8_t _val){
	// Weak definitions
}

//#############################################################################################
__WEAK void  SCREEN_1_AIP_CSPin(uint8_t _val){
	// Weak definitions
}
//#############################################################################################
__WEAK void  SCREEN_2_AIP_ResetPin(uint8_t _val){
	// Weak definitions
}
//#############################################################################################
__WEAK void  SCREEN_2_AIP_A0Pin(uint8_t _val){
	// Weak definitions
}
//#############################################################################################

__WEAK void  SCREEN_2_AIP_CSPin(uint8_t _val){
	// Weak definitions
}
//#############################################################################################
__WEAK void  SCREEN_3_AIP_ResetPin(uint8_t _val){
	// Weak definitions
}
//#############################################################################################
__WEAK void  SCREEN_3_AIP_A0Pin(uint8_t _val){
	// Weak definitions
}
//#############################################################################################
__WEAK void  SCREEN_3_AIP_CSPin(uint8_t _val){
	// Weak definitions
}
//#############################################################################################
AIP *newLCDObj(Params *_params){
	AIP *p = (AIP *)malloc(sizeof(AIP));
	if(p == NULL){
#if (LOG_STATE)
printf("Memory Allocation Failed (AIP) \n");
#endif
		while(1);
	}else{
#if (LOG_STATE)
printf("Memory Allocation Successful. (AIP) %d bytes used ! \n",sizeof(AIP));
#endif
		
	}
	
	p->Init					        = &AIP_Init;
	p->WriteData	          = &AIP_writeData;
	p->WriteCommand	        = &AIP_writeCommand;
	p->ClearScreen	        = &AIP_ClearScreen;
	p->UpdateScreen	        = &AIP_UpdateScreen;
	p->DrawPixel		        = &AIP_draw_pixel;
	p->WriteChar		        = &AIP_writeChar;
	p->SetCursor		        = &AIP_SetCursor;
	p->WriteString 	        = &AIP_WriteString;
	p->WriteStringLen       = &AIP_WriteStringLen;
	p->Spoint 			        = &AIP_Spoint;
	p->WriteNumber 	        = &AIP_writeNumber;
	p->Cs                   = _params->Cs;
	p->A0		   	            = _params->A0;
	p->Reset   	 		        = _params->Reset;
	p->ptrRam			          = _params->ramB;
	return p;
}
//#############################################################################################


static uint8_t spi_transfer(uint8_t *_data){
	uint8_t _buf;
		SPI_WRITE_TX(SPI0,_data[0]);
    while (SPI_IS_BUSY(SPI0));	
		while (SPI_GET_RX_FIFO_EMPTY_FLAG(SPI0) == 0){
		_buf  = SPI_READ_RX(SPI0);
		}
	return _buf;
}

//#############################################################################################
static void AIP_Init(AIP *p){
	
		p->Reset(1);
		p->A0(1);
		AIP_writeCommand(0xe2,p);
		AIP_writeCommand(0x2f,p);
		AIP_writeCommand(0xa0,p);		//MX=0   	SEG0-SEG95
		AIP_writeCommand(0xc0,p);		//MY=0          COM0-COM4    	
		AIP_writeCommand(0xa4,p);		//0xA5 All point on
		AIP_writeCommand(0x9f,p);		//4V
		AIP_writeCommand(0xA6,p);		// normal display 
		AIP_writeCommand(0xB0,p);		// page address 0
		AIP_writeCommand(0xf1,p);		// enter extended command mode 
		AIP_writeCommand(0x5b,p);   // frame rate
		AIP_writeCommand(0x70,p);
		AIP_writeCommand(0x60,p);	//	1/4DUTY
		AIP_writeCommand(0xa4,p);	//	1/3BIAS
		AIP_writeCommand(0xf0,p);	//  exit external command mode 
		AIP_writeCommand(0xaf,p);	//	display on
	  AIP_writeCommand(0x00,p); //  low column address
    AIP_writeCommand(0x10,p); //   high column address
#if (LOG_STATE)
     printf("- SEG0-SEG95 \n"
            "- COM0-COM4 \n"
            "- 4Volt \n"
            "- Normal Display \n"
            "- Page Address 0 \n"
            "- Frame rate 140.2 Hz \n"
            "- 1/4 Duty \n"
            "- 1/3 Bias \n"
						"AIP Initialized. \n\n"
						);
#endif
}
//#############################################################################################


static void AIP_writeData(uint8_t *data,uint8_t len,AIP *p){
	p->A0(1);
	p->Cs(0);
	for(int i=0;i<len;i++){
		spi_transfer((data+i));
	}
	p->Cs(1);
		
}
//#############################################################################################
static void AIP_writeCommand(uint8_t _cmd,AIP *p){
	p->A0(0);
	p->Cs(0);
	spi_transfer(&_cmd);
	p->Cs(1);
}
//#############################################################################################

static void AIP_ClearScreen(AIP *p){
	memset(p->ptrRam,0x00,BUFF_SIZE);
  AIP_SetCursor(0,0,p);
}
//#############################################################################################

//#############################################################################################
static void AIP_UpdateScreen(AIP *p){
	

	AIP_writeCommand(0xB0,p); // ram page Address 0 , kac page var datasheette yazmiyor
	AIP_writeCommand(0x00,p); //---set low column address
	AIP_writeCommand(0x10,p); //---set high column address
	AIP_writeData(p->ptrRam,BUFF_SIZE,p); // hata alinirsa page kismina bak ,
	uint8_t _temp[20]="";
	for(int i =0;i<19;i++){
		_temp[i] = p->ptrRam[i];
	}
}
//#############################################################################################
static void AIP_draw_pixel(uint8_t x,uint8_t y,uint8_t color,AIP *p){
	if(x>=WIDTH || y >= HEIGHT ){
		return;
	}
    if(color == 1) {
        p->ptrRam[x] |= 1<<(y%4);
    } else {  
         p->ptrRam[x] &= ~(1<<(y%4)); 
    }
}
//#############################################################################################

static uint8_t AIP_writeChar(uint8_t *_chr,FontDef *Font,AIP *p){
		uint8_t c;
		if (*_chr < 32 || *_chr > 126){
        return 0;
    }
    if ((p->AIP_currentPos.x_pos + Font->FontWidth) > WIDTH)
    {
        return 0; // yer yok 
    }
	
	for(uint8_t i = 0; i < Font->FontWidth; i++) {
		c =  Font->data[(*_chr - 32) * Font->FontWidth + i];
		for(uint8_t j = Font->FontHeight; j>0; j--) {
			if(((c<<(j+1))&0x10)){ 
				AIP_draw_pixel( p->AIP_currentPos.x_pos+i,(Font->FontHeight-j),1,p);
			}
			else{
				AIP_draw_pixel( p->AIP_currentPos.x_pos+i,(Font->FontHeight-j),0,p);
			}
		}
	}
		p->AIP_currentPos.x_pos+=Font->FontWidth;	
	return 1;
}
//#############################################################################################
	
static void AIP_SetCursor(uint8_t _x,uint8_t _y,AIP *p){
    p->AIP_currentPos.x_pos = _x;
    p->AIP_currentPos.y_pos = _y;
}
//#############################################################################################
static void AIP_WriteString(uint8_t x, uint8_t y,uint8_t * str, FontDef *Font,AIP *p) {
	uint8_t counter=0;
	 AIP_ClearScreen(p);
	 AIP_SetCursor(x,y,p);
    while (*str) {
			counter++;
			if(*str == '.'){
				AIP_Spoint((counter*2)+1,1,p);
        str++;
				continue;
			}
				AIP_writeChar(str, Font,p);
        str++;
    }
}
static void AIP_WriteStringLen(uint8_t x, uint8_t y,uint8_t * str, FontDef *Font,AIP *p,uint8_t _len) {
	uint8_t counter=0;
	 AIP_ClearScreen(p);
	 AIP_SetCursor(x,y,p);
	 for(uint8_t x=0;x<_len;x++){
			counter++;
			if(str[x] == '.'){
				AIP_Spoint((counter*2)+1,1,p);
				continue;
			}
				AIP_writeChar(&str[x], Font,p);
	 }
}
//#############################################################################################
static void AIP_Spoint(uint8_t _id,uint8_t _val,AIP *p){
	switch(_id){
		case 1:
			AIP_draw_pixel(2,3,_val,p);
			break;
		case 2:
			AIP_draw_pixel(1 ,3,_val,p);
			break;
		case 3:
			AIP_draw_pixel(0 ,3,_val,p);
			break;
		case 4:
			AIP_draw_pixel(0 ,0,_val,p);
			break;
		case 5:
			AIP_draw_pixel(2 ,0,_val,p);
			break;
		case 6:
			AIP_draw_pixel(3 ,0,_val,p);
			break;
		case 7:
			AIP_draw_pixel(5 ,0,_val,p);
			break;
		case 8:
			AIP_draw_pixel(6 ,0,_val,p);
			break;
		case 9:
			AIP_draw_pixel(8 ,0,_val,p);
			break;
		case 10:
			AIP_draw_pixel(9 ,0,_val,p);
			break;
		case 11:
			AIP_draw_pixel(11 ,0,_val,p);
			break;
		case 12:
			AIP_draw_pixel(12 ,0,_val,p);
			break;
		case 13:
			AIP_draw_pixel(14 ,0,_val,p);
			break;
		case 14:
			AIP_draw_pixel(15 ,0,_val,p);
			break;
		case 15:
			AIP_draw_pixel(17 ,0,_val,p);
			break;
		case 16:
			AIP_draw_pixel(18 ,0,_val,p);
			break;
		case 17:
			AIP_draw_pixel(18 ,1,_val,p);
			break;
		
	}
}
//#############################################################################################

static void AIP_writeNumber(uint8_t _number,uint8_t _state,FontDef *Font,AIP *p){ // 0-9 , 0-5 digit
  p->AIP_currentPos.x_pos = _state*3;
   p->AIP_currentPos.y_pos = 0;
	uint8_t _chrVal = _number + '0';
	AIP_writeChar(&_chrVal,Font,p);
}





//#############################################################################################
//                                           END
//#############################################################################################