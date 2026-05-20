#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 一般设置为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	while(1)
	{
//		Delay_ms(500);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);		
//		Delay_ms(500);
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);		
	}
}
