#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "Timer.h"

uint16_t num;

int main(void)
{
	
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1, 1, "Count:");


	while(1)
	{
		OLED_ShowNum(1, 7, num, 6);

	}
}
