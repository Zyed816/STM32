#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED_Hardware.h"
#include "ADConverter.h"

uint16_t ADVal;
float Voltage;

int main(void)
{
	
	OLED_Init_H();
	ADConverter_Init();
	OLED_ShowString_H(1, 1, "ADValue:");
	OLED_ShowString_H(1, 1, "Voltage:0.00V");

	while(1)
	{
		ADVal = ADConverter_GetVal();
		Voltage = (float)ADVal / 4095 * 3.3;
		OLED_ShowNum_H(1, 9, ADVal, 4);
		OLED_ShowNum_H(2, 9, Voltage, 1);
		OLED_ShowNum_H(2, 11, (uint16_t)(Voltage * 100) % 100, 2);
		
		Delay_ms(100);
	}
}
