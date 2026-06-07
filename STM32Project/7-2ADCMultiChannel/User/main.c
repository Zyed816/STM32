#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED_Hardware.h"
#include "ADConverter.h"

uint16_t AD0, AD1, AD2, AD3;

int main(void)
{
	
	OLED_Init_H();
	ADConverter_Init();
	OLED_ShowString_H(1, 1, "AD0:");
	OLED_ShowString_H(2, 1, "AD1:");
	OLED_ShowString_H(3, 1, "AD2:");
	OLED_ShowString_H(4, 1, "AD3:");

	while(1)
	{
		AD0 = ADConverter_GetVal(ADC_Channel_0);
		AD1 = ADConverter_GetVal(ADC_Channel_1);
		AD2 = ADConverter_GetVal(ADC_Channel_2);
		AD3 = ADConverter_GetVal(ADC_Channel_3);
		
		OLED_ShowNum_H(1, 5, AD0, 4);
		OLED_ShowNum_H(1, 5, AD1, 4);
		OLED_ShowNum_H(1, 5, AD2, 4);
		OLED_ShowNum_H(1, 5, AD3, 4);
		
		Delay_ms(100);
	}
}
