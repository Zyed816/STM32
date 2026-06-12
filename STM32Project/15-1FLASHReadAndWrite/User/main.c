#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "Store.h"
#include "Button.h"

uint8_t ButtonVal1;
uint8_t ButtonVal2;

int main(void)
{
	
	OLED_Init();
	Button_Init();
	Store_Init();
	
	OLED_ShowString(1, 1, "Flag:");
	OLED_ShowString(2, 1, "Data:");

	while(1)
	{
		ButtonVal1 = Button_Read(Pin_11);
		ButtonVal2 = Button_Read(Pin_12);
		if(ButtonVal1 == 1) {
			Store_Data[1] ++;
			Store_Data[2] += 2;
			Store_Data[3] += 3;
			Store_Data[4] += 4;
			Store_Save();
		}
		if(ButtonVal2 == 1) {
			Store_Clear();
		}
		
		OLED_ShowHexNum(1, 6, Store_Data[0], 4);
		OLED_ShowHexNum(3, 1, Store_Data[1], 4);
		OLED_ShowHexNum(3, 6, Store_Data[2], 4);
		OLED_ShowHexNum(4, 1, Store_Data[3], 4);
		OLED_ShowHexNum(4, 6, Store_Data[4], 4);
	}
}
