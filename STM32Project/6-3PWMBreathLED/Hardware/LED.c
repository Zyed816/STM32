#include "stm32f10x.h"                  // Device header

typedef enum{Pin_1 = 1, Pin_2 = 2} LED_ID;

void LED_Init(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 设置为高电平确保初始化完成LED灭
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

void LED_On(LED_ID id)
{
	if(id == Pin_1) {
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	} else if(id == Pin_2) {
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}

void LED_Off(LED_ID id)
{
	if(id == Pin_1) {
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	} else if(id == Pin_2) {
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
}

void LED_Switch(LED_ID id)
{
	if(id == Pin_1) {
		if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) {
			LED_Off(Pin_1);
		} else {
			LED_On(Pin_1);
		}
	} else if(id == Pin_2) {
		if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0) {
			LED_Off(Pin_2);
		} else {
			LED_On(Pin_2);
		}
	}
}
