#include "stm32f10x.h"                  // Device header
#include <stdio.h>

// 缓存区数组,存储发送和接收的数据包
uint8_t Serial_TxPacket[4];
uint8_t Serial_RxPacket[4];
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		// 上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置USART
	USART_InitTypeDef USART_InitStructure;
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		// 不使用流控
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;		// 收发模式
	USART_InitStructure.USART_Parity = USART_Parity_No;		// 校验位设置：无校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	// 配置中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		// 开启RXNE到NVIC的输出
	// 配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	// 开启USART
	USART_Cmd(USART1, ENABLE);
}

// 发送一个字节数据
void Serial_SendByte(uint8_t Byte)
{
	// 将待发送数据写入TDR
	USART_SendData(USART1, Byte);
	// 等待TDR中数据被转运到移位寄存器
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
	// 不需要手动清零
}

// 发送数组
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for(i = 0; i < Length; i ++) {
		Serial_SendByte(Array[i]);
	}
}

// 发送字符串
void Serial_SendString(char *String)
{
	uint8_t i;
	for(i = 0; String[i] != '\0'; i ++) {			// '\0'为字符串结束字符
		Serial_SendByte(String[i]);
	}
}

// 参数X,Y，返回X的Y次方
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	
	uint32_t i;
	for(i = 0; i < Y; i ++) {
		Result *= X;
	}
	
	return Result;
}

// 发送数字，参数为12345时，接受方在文本模式下查看到12345
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for(i = 0; i < Length; i ++) {
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');		// 从高位到低位
	}
}

// 重定向fputc到串口，使得printf函数打印到串口
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

// 发送数据包函数
void Serial_SendPacket(void)
{
	// 发送包头
	Serial_SendByte(0xFF);
	
	// 发送数据载荷
	Serial_SendArray(Serial_TxPacket, 4);
	
	// 发送包尾
	Serial_SendByte(0xFE);
}

uint8_t Serial_GetRxFlag(void)
{
	if(Serial_RxFlag == 1) {
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}


// 重写中断函数:接收数据包
void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;		// static变量函数第一次进入时初始化一次，退出后仍然有效，类似全局变量，但只能在本函数使用
	static uint8_t pRxPacket = 0;	// 记录当前已经接收数据个数
	
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET) {
		// 读取接收到的数据
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if(RxState == 0) {
			if(RxData == 0xFF) {
				RxState = 1;
				pRxPacket = 0;
			}
		} else if(RxState == 1) {
			Serial_RxPacket[pRxPacket] = RxData;
			pRxPacket ++;
			if(pRxPacket >= 4) {
				RxState = 2;
			}
		} else if(RxState == 2) {
			if(RxData == 0xFE) {
				Serial_RxFlag = 1;
				RxState = 0;
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
