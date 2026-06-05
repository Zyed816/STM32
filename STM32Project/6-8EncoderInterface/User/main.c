#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED_Software.h"
#include "RotaryEncoder.h"
#include "Timer.h"

int16_t Speed;

int main(void)
{
	
	OLED_Init();
	Timer_Init();
	RotaryEncoder_Init();
	
	OLED_ShowString(1, 1, "Speed:");

	while(1)
	{
		
		OLED_ShowSignedNum(1, 7, Speed, 5);
//		Delay_ms(1000);		// 容易阻塞主程序
	}
}

// 重写中断函数
void TIM2_IRQHandler(void)
{
	// 检查标志位
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		Speed = RotaryEncoder_Get();
		// 清除标志位
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
