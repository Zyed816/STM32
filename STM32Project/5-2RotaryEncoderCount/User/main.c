#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "RotaryEncoder.h"

int main(void)
{
	
	OLED_Init();
	RotaryEncoder_Init();
	
	OLED_ShowString(1, 1, "Count:");

	while(1)
	{
		OLED_ShowNum(1, 7, RotaryEncoder_GetNum(), 5);
	}
}
