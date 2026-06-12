#include "stm32f10x.h"                  // Device header
#include "Delay.h"

typedef enum{Pin_11 = 11, Pin_12 = 12} Button_ID;

void Button_Init(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 上拉输入模式，可以避免配置上拉电阻
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

// 读取GPIO_Pin_id引脚的按键动作，返回1说明该按键完成了一次“按下->释放”
uint8_t Button_Read(Button_ID id)
{
	uint8_t buttonVal = 0;
	
	if(id == Pin_11) {
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0) {
			Delay_ms(20);
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0);		// 按键按下未释放
			Delay_ms(20);
			buttonVal = 1;
		}
	} else if(id == Pin_12) {
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0) {
			Delay_ms(20);
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0);		// 按键按下未释放
			Delay_ms(20);
			buttonVal = 1;
		}
	}
	
	return buttonVal;
}
