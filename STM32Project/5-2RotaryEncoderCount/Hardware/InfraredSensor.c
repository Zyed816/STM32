#include "stm32f10x.h"                  // Device header

// 定义一个记录次数的变量
uint16_t InfraredSensor_Count;

void InfraredSensor_Init(void)
{
	// 配置GPIO_Pin_14
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 推荐为上拉/下拉/浮空输入，这里选择上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 配置AFIO，相关函数位于stm32f10x_gpio.h
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// 配置EXTI
	// EXTI虽然是片上外设，但时钟是常开的，不用使能
	// 将GPIOB的Pin_14连接到EXTI14
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		// 中断模式
	EXTI_InitStructure.EXTI_Trigger  = EXTI_Trigger_Falling;	// 下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	// 配置NVIC
	// NVIC是内核外设，时钟是常开的，不用使能
	// 设置中断优先级分组，整个芯片只能采用一种分组方式，写在模块内要统一，也可以写在主函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 2位抢占优先级，2位响应优先级
	NVIC_InitTypeDef NVIC_InitStructure;
	// 使能EXTI15_10
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	// 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// 指定通道的抢占优先级和响应优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
	// 检查是否是PB14发出的中断
	if(EXTI_GetITStatus(EXTI_Line14) == SET) {
		InfraredSensor_Count ++;
		// 响应完中断后要清除标志位，避免持续申请中断
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

uint16_t InfraredSensor_GetNum(void)
{
	return InfraredSensor_Count;
}
