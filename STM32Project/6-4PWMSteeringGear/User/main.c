#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "Servo.h"
#include "Delay.h"
#include "Button.h"

uint8_t ButtonNum;
float Angle = 0;

int main(void)
{
	
	OLED_Init_H();
	Servo_Init();
	Button_Init();
	
	OLED_ShowString_H(1, 1, "Angle:");

	while(1)
	{
		ButtonNum = Button_Read(Pin_11);
		if(ButtonNum == 1) {
			Angle += 30;
			if(Angle > 180) {
				Angle = 0;
			}
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum_H(1, 7, Angle, 3);
	}
}
