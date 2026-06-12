#include "stm32f10x.h"                  // Device header

// FLASH读取字
uint32_t MyFLASH_ReadWord(uint32_t Address)
{
	return *((__IO uint32_t *)(Address));
}

// FLASH读取半字
uint16_t MyFLASH_ReadHalfWord(uint32_t Address)
{
	return *((__IO uint16_t *)(Address));
}

// FLASH读取字节
uint8_t MyFLASH_ReadByte(uint32_t Address)
{
	return *((__IO uint8_t *)(Address));
}

// FLASH全擦除
void MyFLASH_EraseAllPages(void)
{
	// 先解锁再擦除，最后上锁
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
}

// FLASH擦除页
void MyFLASH_ErasePage(uint32_t Page_Address)
{
	// 先解锁再擦除，最后上锁
	FLASH_Unlock();
	FLASH_ErasePage(Page_Address);
	FLASH_Lock();
}

// 页编程（页写入）：写入字
void MyFLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(Address, Data);
	FLASH_Lock();
}

// 页编程（页写入）：写入半字
void MyFLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address, Data);
	FLASH_Lock();
}

// 写入字节操作比较麻烦，暂时不用实现
