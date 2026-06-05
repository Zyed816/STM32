#include "stm32f10x.h"                  // Device header

extern int16_t num;

void Timer_Init(void)
{
	// 使能时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 选择时钟源
	TIM_InternalClockConfig(TIM2);
	
	// 配置时基单元，主要是计数模式，PSC和ARR的值，CNT未设置，可通过其他函数设置CNT起始值
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 决定输入滤波等模块用多快的采样时钟，影响不大
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;		// 设置ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;		// 设置PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		// 高级定时器才有的功能
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	// 使能更新中断，连接更新中断到NVIC
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// 配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;		// 选择中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 		// 子优先级，响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	// 使能定时器（运行控制）
	TIM_Cmd(TIM2, ENABLE);
}


