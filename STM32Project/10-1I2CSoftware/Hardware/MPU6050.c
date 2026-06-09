#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"
#include "MyI2C.h"

#define MPU6050_ADDRESS			0xD0

// 指定地址写
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

// 指定地址读
uint8_t MPU_6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	// 先修改MPU6050中当前地址指针
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	// 读寄存器
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);		// 读操作
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(0);
	MyI2C_Stop();
	return Data;
}

void MPU6050_Init(void)
{
	MyI2C_Init();
	
	// 配置电源管理寄存器1，解除睡眠模式
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	
	// 配置电源管理寄存器2
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	
	// 配置采样率分频
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	
	// 配置寄存器
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	
	// 陀螺仪配置寄存器
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	
	// 加速度计配置寄存器
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6050_GetID(void)
{
	return MPU_6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;
	
	DataH = MPU_6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU_6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	
	DataH = MPU_6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU_6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU_6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU_6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU_6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU_6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU_6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU_6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU_6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU_6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
