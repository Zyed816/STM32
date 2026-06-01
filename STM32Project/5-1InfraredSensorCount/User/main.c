#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "InfraredSensor.h"

int main(void)
{
	
	OLED_Init();
	InfraredSensor_Init();
	
	OLED_ShowString(1, 1, "Count:");

	while(1)
	{
		OLED_ShowNum(1, 7, InfraredSensor_GetNum(), 5);
	}
}
