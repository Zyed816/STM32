#include "stm32f10x.h"                  // Device header
#include <time.h>

uint16_t MyRTC_Time[] = {2026, 6, 11, 15, 0, 30};

void MyRTC_SetTime(void);

void MyRTC_Init(void)
{
	// 开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	// 使能PWR和BKP
	PWR_BackupAccessCmd(ENABLE);
	
	// 通过BKP中得值判断是否备用电源断电，如果断电重置时钟，否则不重置
	if(BKP_ReadBackupRegister(BKP_DR1) != 0x3F3F) {
		// 开启LSE时钟并等待开启完成
		RCC_LSEConfig(RCC_LSE_ON);
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);
		
		// 选择时钟源并使能
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		// 等待同步、等待上一步操作完成
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		// 设置预分频器，自动进入和退出配置模式
		RTC_SetPrescaler(32768 - 1);
		RTC_WaitForLastTask();
		
		// 设置初始时间，设置CNT的值
	//	RTC_SetCounter(1672588795);
	//	RTC_WaitForLastTask();
		MyRTC_SetTime();
		
		// 设置BKP_DR1用作标志位
		BKP_WriteBackupRegister(BKP_DR1, 0x3F3F);
	} else {
		// 等待同步、等待上一步操作完成
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}

void MyRTC_SetTime(void) 
{
	time_t time_cnt;
	struct tm time_date;
	
	time_date.tm_year = MyRTC_Time[0] - 1900;
	time_date.tm_mon = MyRTC_Time[1] - 1;
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_hour = MyRTC_Time[3];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_sec = MyRTC_Time[5];
	
	// 将日期转为时间戳
	time_cnt = mktime(&time_date) - 8 * 60 * 60;
	
	// 写入cnt
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
}

void MyRTC_GetTime(void)
{
	time_t time_cnt;
	struct tm time_date;
	
	time_cnt = RTC_GetCounter() + 8 * 60 * 60;
	time_date = *localtime(&time_cnt);
	
	MyRTC_Time[0] = time_date.tm_year + 1900;
	MyRTC_Time[1] = time_date.tm_mon + 1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;
}
