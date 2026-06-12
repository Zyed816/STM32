#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "Serial.h"
#include "Delay.h"

uint8_t RxData;		// 存放接收到的数据

int main(void)
{
	
	OLED_Init_H();
	Serial_Init();
	
	OLED_ShowString_H(1, 1, "RxData:");

	while(1)
	{
		if(Serial_GetRxFlag() == 1) {
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum_H(1, 8, RxData, 2);
		}
		
		OLED_ShowString_H(2, 1, "Running");
		Delay_ms(100);
		OLED_ShowString_H(2, 1, "       ");
		Delay_ms(100);
	}
	
	// 使用WFI进入睡眠模式，可以被任意中断唤醒
	__WFI();
}
