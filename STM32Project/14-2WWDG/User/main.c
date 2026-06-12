#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "Delay.h"
#include "Button.h"

int main(void)
{
	
	OLED_Init();
	Button_Init();
	
	OLED_ShowString(1, 1, "WWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET) {
		// 窗口看门狗引起的复位
		OLED_ShowString(2, 1, "WWDGRST");
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
	
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	// 设置预分频和窗口值
	WWDG_SetPrescaler(WWDG_Prescaler_8);	// 分频系数8，分频系数55 -> 超时时间50ms
	WWDG_SetWindowValue(21 | 0x40);		// 窗口值21 -> 30ms以后才可喂狗
	
	// 使能WWDG并写入控制寄存器
	WWDG_Enable(54 | 0x40);

	while(1)
	{
		Button_Read(Pin_11);
			
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(20);  
		OLED_ShowString(4, 1, "    ");
		Delay_ms(20);
		
		// 喂狗，放在下面避免喂狗过早
		WWDG_SetCounter(54 | 0x40);
	}
}
