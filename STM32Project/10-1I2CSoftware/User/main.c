#include "stm32f10x.h"                  // Device header
#include "OLED_Hardware.h"
#include "MPU6050.h"

int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{
	OLED_Init_H();
	MPU6050_Init();
	
	OLED_ShowString_H(1, 1, "ID:");
	OLED_ShowNum_H(1, 4, MPU6050_GetID(), 2);
	OLED_ShowString_H(1, 7, "Software");

	while(1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum_H(2, 1, AX, 5);
		OLED_ShowSignedNum_H(3, 1, AY, 5);
		OLED_ShowSignedNum_H(4, 1, AZ, 5);
		OLED_ShowSignedNum_H(2, 8, GX, 5);
		OLED_ShowSignedNum_H(3, 8, GX, 5);
		OLED_ShowSignedNum_H(4, 8, GX, 5);
	}
}
