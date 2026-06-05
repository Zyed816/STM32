#include "stm32f10x.h"                  // Device header

int16_t RotaryEncoder_Count;

void RotaryEncoder_Init(void)
{
	// 配置GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		// 上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置时基单元
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;
	TIM_TimeBaseInitStructure.TIM_Period = 1 - 1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		计数方向由编码器决定，无需设置
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	// 配置输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	// 通道1
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;		// 不代表上升沿，而是说明不反相
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	// 通道2
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;		// 不代表上升沿，而是说明不反相
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	// 配置编码器接口，
	// TIM_ICPolarity_Rising, TIM_ICPolarity_Rising两个参数与上面配置通道的极性选择配置的是同一个寄存器
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	// 使能计数器
	TIM_Cmd(TIM3, ENABLE);
}

int16_t RotaryEncoder_Get(void)
{
//	return TIM_GetCounter(TIM3);		// 显示位置
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);		// 清零CNT
	return Temp;
}
