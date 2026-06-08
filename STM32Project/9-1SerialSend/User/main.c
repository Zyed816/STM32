#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "Serial.h"

int main(void)
{
	
	OLED_Init_H();
	Serial_Init();
	
//	Serial_SendByte(0x41);
	
//	uint8_t A[] = {0x42, 0x43, 0x44, 0x45};
//	Serial_SendArray(A, 4);
	
//	Serial_SendNumber(15769, 5);
	
	Serial_SendString("Hello, World!");

	while(1)
	{
		
	}
}
