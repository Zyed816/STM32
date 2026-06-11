#include "stm32f10x.h"                  // Device header

// 封装对SS的操作
void MySPI_W_SS(uint8_t BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitVal);		// SPI通信非常快所以不用加延时
}

// 封装对SCK的操作
void MySPI_W_SCK(uint8_t BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitVal);
}

// 封装对MOSI的操作
void MySPI_W_MOSI(uint8_t BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitVal);
}

// 封装对MISO的操作
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySPI_Init(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 输出引脚配置推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 输入引脚配置上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// 设置默认电平
	MySPI_W_SS(1);		// SS默认高电平
	MySPI_W_SCK(0);			// 模式0下SCK默认低电平
	
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
	uint8_t i, ByteReceive = 0x00;
	
	for(i = 0; i < 8; i ++) {
		// 开始条件产生后，主机左移并把最高位写到MOSI
		MySPI_W_MOSI(ByteSend & (0x80 >> i));
		// SCK上升沿到来后主机读取MISO
		MySPI_W_SCK(1);
		if(MySPI_R_MISO() == 1) {
			ByteReceive |= (0x80 >> i);
		}
		// 产生下降沿
		MySPI_W_SCK(0);
	}
	
	return ByteReceive;
}
