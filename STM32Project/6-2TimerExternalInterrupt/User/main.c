#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "Timer.h"
#include "InfraredSensor.h"

uint16_t num;

int main(void)
{
	
	OLED_Init();
	Timer_Init();
	InfraredSensor_Init();
	
	OLED_ShowString(1, 1, "Num:");
	OLED_ShowString(2, 1, "Couter:");

	while(1)
	{
		OLED_ShowNum(1, 5, num, 3);
		OLED_ShowNum(2, 8, Timer_GetNum(), 3);
	}
}
