#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "Serial.h"
#include "LED.h"
#include <string.h>		// 调用字符串比较函数

int main(void)
{
	LED_Init();
	OLED_Init_H();
	Serial_Init();
	
	OLED_ShowString_H(1, 1, "TxPacket");
	OLED_ShowString_H(3, 1, "RxPacket");

	while(1)
	{
		// 如果Serial_RxFlag为1，说明收到数据包，开始接收
		if(Serial_RxFlag == 1) {
			// 先清除低4行，防止之前更长字符串残留
			OLED_ShowString_H(4, 1, "                ");	// 16个空格实现清空效果
			
			OLED_ShowString_H(4, 1, Serial_RxPacket);
			
			if(strcmp(Serial_RxPacket, "LED_ON") == 0) {
				// 如果收到的字符串是LED_ON，点亮LED
				LED_On(Pin_1);
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString_H(2, 1, "                ");
				OLED_ShowString_H(2, 1, "LED_ON_OK");
			} else if(strcmp(Serial_RxPacket, "LED_OFF") == 0) {
				// 如果收到的字符串是LED_OFF，关闭LED
				LED_Off(Pin_1);
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString_H(2, 1, "                ");
				OLED_ShowString_H(2, 1, "LED_OFF_OK");
			} else {
				Serial_SendString("ERROR_COMMAND!\r\n");
				OLED_ShowString_H(2, 1, "                ");
				OLED_ShowString_H(2, 1, "ERROR_COMMAND!");
			}
			// 所有接收完成后，Serial_RxFlag置为0
			Serial_RxFlag = 0;
		}
	}
}
