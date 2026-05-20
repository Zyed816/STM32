#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 一般设置为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 先设置所有引脚输出高电平，所有LED熄灭
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);

	while(1)
	{
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);		
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);	
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
	}
}
