#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LDR.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	Buzzer_Init();
	LDR_Init();

	while(1)
	{
		if(LDR_Read() != 0) {
			Buzzer_On();
		} else {
			Buzzer_Off();
		}
		
//		Delay_ms(500);
//		Buzzer_On();
//		Delay_ms(500);
//		Buzzer_Off();
	}
}
