#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "PWM.h"
#include "Delay.h"

int main(void)
{
	
	OLED_Init_H();
	PWM_Init();
	
	uint16_t i;

	while(1)
	{
		for(i = 0; i < 100; i ++) {
			PWM_SetCompare2(i);
			Delay_ms(10);
		}
		for(i = 0; i < 100; i ++) {
			PWM_SetCompare2(100 - i);
			Delay_ms(10);
		}
	}
}
