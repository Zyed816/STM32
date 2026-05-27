#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"

int main(void)
{
	
	OLED_Init_H();
	OLED_ShowChar_H(1, 1, 'A');
	OLED_ShowString_H(1, 3, "I2C_Hardware!");
	OLED_ShowNum_H(2, 1, 1234, 4);
	OLED_ShowSignedNum_H(2, 6, -50, 3);
	OLED_ShowHexNum_H(3, 1, 8, 4);
	OLED_ShowBinNum_H(4, 1, 8, 4);
	

	while(1)
	{
		
	}
}
