#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "myDMA.h"
#include "Delay.h"

uint8_t A[] = {0x01, 0x02, 0x03, 0x04};
uint8_t B[] = {0, 0, 0, 0};

int main(void)
{
	
	OLED_Init_H();
	myDMA_Init((uint32_t)A, (uint32_t)B, 4);
	OLED_ShowString_H(1, 1, "AddrA:");
	OLED_ShowString_H(3, 1, "AddrB:");
	OLED_ShowHexNum_H(1, 8, (uint32_t)A, 8);
	OLED_ShowHexNum_H(3, 8, (uint32_t)B, 8);

	while(1)
	{
		A[0] ++;
		A[1] ++;
		A[2] ++;
		A[3] ++;
		
		OLED_ShowHexNum_H(2, 1, A[0], 2);
		OLED_ShowHexNum_H(2, 4, A[1], 2);
		OLED_ShowHexNum_H(2, 7, A[2], 2);
		OLED_ShowHexNum_H(2, 10, A[3], 2);
		OLED_ShowHexNum_H(4, 1, B[0], 2);
		OLED_ShowHexNum_H(4, 4, B[1], 2);
		OLED_ShowHexNum_H(4, 7, B[2], 2);
		OLED_ShowHexNum_H(4, 10, B[3], 2);
		Delay_ms(1000);
		
		myDMA_Transfer();
		
		OLED_ShowHexNum_H(2, 1, A[0], 2);
		OLED_ShowHexNum_H(2, 4, A[1], 2);
		OLED_ShowHexNum_H(2, 7, A[2], 2);
		OLED_ShowHexNum_H(2, 10, A[3], 2);
		OLED_ShowHexNum_H(4, 1, B[0], 2);
		OLED_ShowHexNum_H(4, 4, B[1], 2);
		OLED_ShowHexNum_H(4, 7, B[2], 2);
		OLED_ShowHexNum_H(4, 10, B[3], 2);
		Delay_ms(1000);
	}
}
