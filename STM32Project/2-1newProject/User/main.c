#include "stm32f10x.h"                  // Device header

int main(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 配置端口模式
	GPIO_InitTypeDef GPIO_InitStruct;	// 定义GPIO初始化结构体
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	// 推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// 设置引脚
	GPIO_SetBits(GPIOB, GPIO_Pin_13);	// 设置引脚为高电平
	// GPIO_ResetBits(GPIOB, GPIO_Pin_13);		// 设置引脚为低电平
	
	while(1)
	{
		
	}
}
