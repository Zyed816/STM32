#include "stm32f10x.h"                  // Device header
#include "OLED_Software.h"
#include "Button.h"

uint16_t ArrayWrite[] = {0x1234, 0x5678};
uint16_t ArrayRead[2];

uint8_t ButtonVal;

int main(void)
{
	
	OLED_Init();
	Button_Init();
	
	OLED_ShowString(1, 1, "W:");
	OLED_ShowString(2, 1, "R:");
	
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	// 使能BKP和RTC，一个函数完成
	PWR_BackupAccessCmd(ENABLE);

	while(1)
	{
		ButtonVal = Button_Read(Pin_11);
		if(ButtonVal == 1) {
			// 写入BKP
			BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);
			BKP_WriteBackupRegister(BKP_DR2, ArrayWrite[1]);
			ArrayWrite[0] ++;
			ArrayWrite[1] ++;
			OLED_ShowHexNum(1, 3, ArrayWrite[0], 4);
			OLED_ShowHexNum(1, 9, ArrayWrite[1], 4);
		}
		
		// 从BKP读出
		ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
		ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);
		OLED_ShowHexNum(2, 3, ArrayRead[0], 4);
		OLED_ShowHexNum(2, 9, ArrayRead[1], 4);
	}
}
