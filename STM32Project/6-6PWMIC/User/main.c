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
	
	PWM_SetPrescaler(720 - 1);
	PWM_SetCompare2(50);

	while(1)
	{
		OLED_ShowNum_H(1, 6, IC_GetFreq(), 5);
	}
}
