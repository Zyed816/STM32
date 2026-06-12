#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "Delay.h"
#include "Button.h"

int main(void)
{
	
	OLED_Init();
	Button_Init();
	
	OLED_ShowString(1, 1, "IWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET) {
		// 独立看门狗引起的复位
		OLED_ShowString(2, 1, "IWDGRST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		RCC_ClearFlag();
	} else {
		OLED_ShowString(3, 1, "RST");
		Delay_ms(500);  
		OLED_ShowString(3, 1, "   ");
		Delay_ms(100);
	}
	
	// 解除预分频器和重装寄存器写保护
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	// 向预分频器和重装寄存器写入，T_LSI = 0.025ms，设置超时时间为1000ms
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499);
	
	// 先喂一次狗，确保重装寄存器中的值为2499
	IWDG_ReloadCounter();
	
	// 启动看门狗
	IWDG_Enable();

	while(1)
	{
		Button_Read(Pin_11);
		
		IWDG_ReloadCounter();
		
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(200);  
		OLED_ShowString(4, 1, "    ");
		Delay_ms(600);
	}
}
