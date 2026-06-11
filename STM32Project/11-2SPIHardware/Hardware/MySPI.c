#include "stm32f10x.h"                  // Device header

// 封装对SS的操作，保留软件模拟
void MySPI_W_SS(uint8_t BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitVal);		// SPI通信非常快所以不用加延时
}

void MySPI_Init(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// 输出引脚配置复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 输入引脚配置上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 输SS配置推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置SPI外设
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;		// 设置为0
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		// 设置为0
	SPI_InitStructure.SPI_CRCPolynomial = 7;		// CRC校验位，设为默认
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		// 双线全双工
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		// 高位先行
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		// 主机模式
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		// 软件SS
	SPI_Init(SPI1, &SPI_InitStructure);
	
	// 开启SPI
	SPI_Cmd(SPI1, ENABLE);
	
	// 设置SS为高电平，不选中从机
	MySPI_W_SS(1);
}

// 产生起始条件
void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

// 产生终止条件
void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

// 交换一个字节
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	// 等待TXE变为1
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	// 待发送数据写入TDR
	SPI_I2S_SendData(SPI1, ByteSend);
	// 等待RXNE变为1
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);
	// 读取RDR中结果
	uint8_t ByteReceive;
	ByteReceive = SPI_I2S_ReceiveData(SPI1);
	return ByteReceive;
}
