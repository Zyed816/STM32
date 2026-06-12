#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "InfraredSensor.h"
#include "Delay.h"

int main(void)
{
	
	OLED_Init();
	InfraredSensor_Init();
	
	// 开启PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	OLED_ShowString(1, 1, "Count:");

	while(1)
	{
		OLED_ShowNum(1, 7, InfraredSensor_GetNum(), 5);
		
		OLED_ShowString(2, 1, "Running");
		Delay_ms(100);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		SystemInit();		// 重新设置HSE为时钟（停止模式唤醒后时钟为HSI:8MHz）
	}
}
