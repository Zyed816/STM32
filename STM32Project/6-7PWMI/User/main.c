#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "PWM.h"
#include "Delay.h"
#include "IC.h"

int main(void)
{
	
	OLED_Init_H();
	PWM_Init();
	IC_Init();
	
	OLED_ShowString_H(1, 1, "Freq:00000Hz");
	OLED_ShowString_H(2, 1, "Duty:00%");
	
	PWM_SetPrescaler(7200 - 1);
	PWM_SetCompare2(80);

	while(1)
	{
		OLED_ShowNum_H(1, 6, IC_GetFreq(), 5);
		OLED_ShowNum_H(2, 6, IC_GetDuty(), 2);
	}
}
