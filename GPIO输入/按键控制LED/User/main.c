#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"


int main(void)
{
	
	LED_Init();
	Key_Init();

uint8_t KeyNum = 0;
	
	
	while(1)
	{
		KeyNum = Key_GetNum();

		
		if(KeyNum == 0)
		{
			LED1_OFF();
			LED2_OFF();
		}
		
		if(KeyNum == 1)
		{
			LED1_ON();
			LED2_OFF();
		}
		
		if(KeyNum == 2)
		{
			LED1_OFF();
			LED2_ON();
		}
	}
}
