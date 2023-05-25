#include"Inc/millis.h"
#include <stdint.h>


volatile int32_t s_u32TickCnt=0;

void wdt_tickCounter(void){
   s_u32TickCnt++;
}

volatile int64_t SysTickCounter(){
	return s_u32TickCnt*(0.417); // 38.4 khz wdt clock ayarlara bakarsan 417us de bir interrupta giriyor
}
int64_t millis(void){
	return SysTickCounter();
}