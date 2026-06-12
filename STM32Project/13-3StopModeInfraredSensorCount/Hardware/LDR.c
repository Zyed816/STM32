#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void LDR_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// 返回值为1说明光照弱，返回值为0说明光照强
uint8_t LDR_Read(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
