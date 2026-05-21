#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Button.h"

int main(void)
{
	LED_Init();
	Button_Init();

	while(1)
	{
		if(Button_Read(Pin_11) == 1) {
			LED_Switch(Pin_1);
		}
		if(Button_Read(Pin_12) == 1) {
			LED_Switch(Pin_2);
		}
	}
}
