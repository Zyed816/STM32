#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	// 使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 选择内部时钟源
	TIM_InternalClockConfig(TIM2);
	
	// 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 滤波模块时钟配置，影响不大
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 99 - 1;		// ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;		// PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 配置输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);		// 设置默认值，后续只修改必要的参数
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		// 输出比较模式：PWM1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// 输出比较极性：高极性ref不翻转；低极性翻转
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;		// 输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;		// 设置CCR的值
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); 	// 由于PA0松动，选择TIM2的OC2引脚即CH2，复用在PA1上
	
	// 使能定时器（运行控制）
	TIM_Cmd(TIM2, ENABLE);
	
	// 初始化引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// 复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);
}
