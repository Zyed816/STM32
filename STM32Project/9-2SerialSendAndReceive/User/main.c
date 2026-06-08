#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "Serial.h"

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
	}
}
