#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "MyRTC.h"
#include "Delay.h"

int main(void)
{
	
	OLED_Init();
	MyRTC_Init();
	
	// 开启PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	OLED_ShowString(1, 1, "CNT  :");
	OLED_ShowString(2, 1, "ALR  :");			// 闹钟值
	OLED_ShowString(3, 1, "ALRF :");			// 闹钟标志位
	
	// 使能Wakeup上升沿唤醒
	PWR_WakeUpPinCmd(ENABLE);
	
	// 设置闹钟，由于Alarm是只写寄存器，在写入前记录写入值
	uint32_t Alarm = RTC_GetCounter() + 10;
	RTC_SetAlarm(Alarm);
	OLED_ShowNum(2, 6, Alarm, 10);

	while(1)
	{
		
		OLED_ShowNum(1, 6, RTC_GetCounter(), 10);		// 显示当前计数值
		OLED_ShowNum(3, 6, RTC_GetITStatus(RTC_IT_ALR), 1);		// 显示闹钟标志位
		
		OLED_ShowString(4, 1, "Running");
		Delay_ms(100);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(100);
		
		OLED_ShowString(4, 9, "Standby");
		Delay_ms(1000);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(1000);
		
		// 模拟关闭其他外设
		OLED_Clear();
		
		// 进入待机模式，唤醒后程序从头开始执行，自动设置主频为72MHz
		PWR_EnterSTANDBYMode();
	}
}
