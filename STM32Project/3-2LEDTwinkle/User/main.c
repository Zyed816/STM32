#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	// 开漏输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 一般设置为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	// 设置引脚电平
//	GPIO_SetBits(GPIOB, GPIO_Pin_13);	// 设置GPIOB13号引脚为高电平
//	GPIO_ResetBits(GPIOB, GPIO_Pin_13);	// 设置GPIOB13号引脚为低电平
//	GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);		// 设置GPIOB13号引脚为高电平
//	GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);	// 设置GPIOB13号引脚为低电平

	while(1)
	{
		Delay_ms(500);
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);		// 13号引脚输出低电平
		Delay_ms(500);
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);		// 13号引脚输出高电平
	}
}
