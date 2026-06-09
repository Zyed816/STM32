#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//#define SCL_Port 	GPIOB
//#define SCL_Pin		GPIO_Pin_10
//#define SDA_Port 	GPIOB
//#define SDA_Pin		GPIO_Pin_11

// 封装对SCL和SDA设置高低电平的操作
void MyI2C_W_SCL(uint8_t BitVal)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitVal);
	Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitVal)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitVal);
	Delay_us(10);
}

// 从SDA读数据的函数
uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitVal;
	BitVal = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(10);
	return BitVal;
}

// 软件实现I2C初始化：调用后SCL和SDA两个引脚被设置为开漏输出并且为高电平
void MyI2C_Init()
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// 配置GPIO，SCL -> PB10，SDA ->PB11
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	// 开漏输出模式，为什么不是复用开漏？
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// 设置SCL和SDA为高电平
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

// 产生开始信号
void MyI2C_Start(void)
{
	// 释放SCL，SDA，注意先释放SDA，如果顺序调换可能产生停止信号
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	// 产生开始信号
	MyI2C_W_SDA(0);		// SCL高电平时，SDA下降沿
	MyI2C_W_SCL(0);		// SCL下降沿		
}

// 产生停止信号
void MyI2C_Stop(void)
{
	// 先拉低SDA，由于不知道传输的最后一个bit位是0还是1
	// 如果是1并且不提前拉低SDA，那么拉高SCL之后将无法产生SDA上升沿，无法结束
	MyI2C_W_SDA(0);
	// 再产生停止信号
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

// 发送一个字节
void MyI2C_SendByte(uint8_t Byte)
{
	// 进入函数时SCL为低电平
	uint8_t i;
	for(i = 0; i < 8; i ++) {
		// 趁SCL此时为低电平，先把Byte最高位放在SDA上
		MyI2C_W_SDA(Byte & (0x80 >> i));
		// 度过一个时钟，在这个时钟高电平时接收方读取SDA，然后拉低SCL进入下一个时钟
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

// 接收一个字节
uint8_t MyI2C_ReceiveByte(void)
{
	// 存放结果
	uint8_t Byte = 0x00;
	uint8_t i;
	// 主机要先释放SDA
	MyI2C_W_SDA(1);
	
	for(i = 0; i < 8; i ++) {
		// 发送方先把数据放到SDA，然后接受方拉高SCL，读取数据
		MyI2C_W_SCL(1);
		if(MyI2C_R_SDA() == 1) {
			Byte |= (0x80 >> i);
		}
		MyI2C_W_SCL(0);		// 拉低SCL，进入下一个时钟
	}
	return Byte;
}

// 发送应答
void MyI2C_SendAck(uint8_t AckBit)
{
	// 函数进来时SCL为低电平，把AckBit放到SDA上
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);		// SCL高电平共接收方读取
	MyI2C_W_SCL(0);		// SCL拉低进入下一个时钟
}

// 接收应答
uint8_t MyI2C_ReceiveAck(void)
{
	// 存放结果
	uint8_t AckBit;
	// 主机先释放SDA
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	
	return AckBit;
}

