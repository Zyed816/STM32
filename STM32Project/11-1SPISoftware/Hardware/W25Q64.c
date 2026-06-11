#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Instructions.h"

void W25Q64_Init(void)
{
	MySPI_Init();
}

// 获取ID指令
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();
	// 主机向W25Q64发送读指令		抛玉引砖
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	// 主机接收W25Q64的返回			抛砖引玉
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);		// DID低8位
	*DID <<= 8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);		// DID高8位
	MySPI_Stop();
}

// 写使能指令
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

// 等待忙：调用后检查当前是否Busy，系统不忙时结束
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout = 100000;
	MySPI_Start();
	// 发送指令
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	// 接收状态寄存器的值，取出最低为检查是否Busy，如果忙就等待
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 1) {
		Timeout --;
		if(Timeout == 0) {
			break;
		}
	}		
	MySPI_Stop();
}

// 页编程指令：往指定地址写入Count个字节数据，Count最大为256
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count) 
{
	// 写入指令前必须先写使能
	W25Q64_WriteEnable();
	
	MySPI_Start();
	// 发送页编程指令
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	// 发送地址
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);		// 转成uint8_t类型参数高位会被舍弃
	// 发送写入的数据
	uint16_t i;
	for(i = 0; i < Count; i ++) {
		MySPI_SwapByte(DataArray[i]);	
	}
	MySPI_Stop();
	
	// 事后等待
	W25Q64_WaitBusy();
}

// 实现扇区擦除指令
void W25Q64_SectorErase(uint32_t Address)
{
	// 写入指令前必须先写使能
	W25Q64_WriteEnable();
	
	MySPI_Start();
	// 发送扇区擦除指令
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	// 发送地址
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);		// 转成uint8_t类型参数高位会被舍弃
	MySPI_Stop();
	
	// 事后等待
	W25Q64_WaitBusy();
}

// 读取数据指令，Count值无限制
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	MySPI_Start();
	// 发送读取指令
	MySPI_SwapByte(W25Q64_READ_DATA);
	// 发送地址
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);		// 转成uint8_t类型参数高位会被舍弃
	// 接收读取数据
	uint32_t i;
	for(i = 0; i < Count; i ++) {
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
}
