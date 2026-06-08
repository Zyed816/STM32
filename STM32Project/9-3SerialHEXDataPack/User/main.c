#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "Serial.h"
#include "Button.h"

uint8_t ButtonVal;

int main(void)
{
	
	OLED_Init_H();
	Serial_Init();
	Button_Init();
	
	OLED_ShowString_H(1, 1, "TxPacket");
	OLED_ShowString_H(3, 1, "RxPacket");
	
	Serial_TxPacket[0] = 0x01;
	Serial_TxPacket[1] = 0x02;
	Serial_TxPacket[2] = 0x03;
	Serial_TxPacket[3] = 0x04;

	while(1)
	{
		ButtonVal = Button_Read(Pin_11);
		// 按键按下->松开，发送数据包
		if(ButtonVal == 1) {
			Serial_TxPacket[0] ++;
			Serial_TxPacket[1] ++;
			Serial_TxPacket[2] ++;
			Serial_TxPacket[3] ++;
			
			Serial_SendPacket();
			
			OLED_ShowHexNum_H(2, 1, Serial_TxPacket[0], 2);
			OLED_ShowHexNum_H(2, 4, Serial_TxPacket[1], 2);
			OLED_ShowHexNum_H(2, 7, Serial_TxPacket[2], 2);
			OLED_ShowHexNum_H(2, 10, Serial_TxPacket[3], 2);
		}
		
		// 如果收到数据包
		if(Serial_GetRxFlag() == 1) {
			OLED_ShowHexNum_H(4, 1, Serial_RxPacket[0], 2);
			OLED_ShowHexNum_H(4, 4, Serial_RxPacket[1], 2);
			OLED_ShowHexNum_H(4, 7, Serial_RxPacket[2], 2);
			OLED_ShowHexNum_H(4, 10, Serial_RxPacket[3], 2);
		}
	}
}


