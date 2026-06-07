#include "stm32f10x.h"                  // Device header

void ADConverter_Init(void)
{
	// 开启时钟：GPIO，ADC，配置ADC预分频器
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// 模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置ADC
	ADC_InitTypeDef ADC_InitStructure;
	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		// 单次
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		// 不使用外部触发源
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	// 单个ADC
	ADC_InitStructure.ADC_NbrOfChannel = 1;		// 使用1个通道
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;		// 非扫描模式
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// ADC使能
	ADC_Cmd(ADC1, ENABLE);
	
	// ADC校准
	ADC_ResetCalibration(ADC1);		// 复位校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);		// 等待复位完成
	ADC_StartCalibration(ADC1);		// 开始校准
	while(ADC_GetCalibrationStatus(ADC1) == SET);		// 等待校准完成
}

uint16_t ADConverter_GetVal(uint8_t ADC_Channel)
{
	// 配置多路选择器
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	
	// 软件启动转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	// 等待转换完成
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
	
	// 读取规则组数据寄存器的值
	return ADC_GetConversionValue(ADC1);
}
