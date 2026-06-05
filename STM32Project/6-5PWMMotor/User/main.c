#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "Moter.h"
#include "Delay.h"
#include "Button.h"

uint8_t ButtonNum;
int16_t Speed = 0;

int main(void)
{
	
	OLED_Init_H();
	Moter_Init();
	Button_Init();
	
	OLED_ShowString_H(1, 1, "Speed:");
	
	while(1)
	{
		ButtonNum = Button_Read(Pin_11);
		if(ButtonNum == 1) {
			Speed += 20;
			if(Speed > 100) {
				Speed = -100;
			}
		}
		Moter_SetSpeed(Speed);
		OLED_ShowSignedNum_H(1, 7, Speed, 3);
	}
}
