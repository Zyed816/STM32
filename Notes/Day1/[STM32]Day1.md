# [STM32]Day1

## 新建工程

### 新建裸项目

打开Keil，Project -> New Project新建项目

![屏幕截图 2026-05-17 132450](.\screenShots\屏幕截图 2026-05-17_132450.png)

选择项目存放的路径，项目内容由文件夹的名称说明，文件名填写Project

![屏幕截图 2026-05-17 132712](.\screenShots\屏幕截图 2026-05-17 132712.png)

在弹出的Select Device选项卡里选择STMicroelectronics -> STM32F1 Series -> STM32F103 -> STM32F103C8点击确定，接下来弹出的Manage Run-Time Environment选项卡可以直接关闭

![image-20260517134210996](.\screenShots\屏幕截图 2026-05-17 134028.png)

## 添加必要的工程文件

找到标准库STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm\下的启动文件，在项目文件夹新建一个Start\文件夹，将启动文件放入其中

![image-20260517135016424](.\screenShots\屏幕截图 2026-05-17 135012.png)

返回上层目录到STM32F10x\，将该目录下的.c和.h文件放入Start\

![image-20260517135302154](.\screenShots\屏幕截图 2026-05-17 135228.png)

将STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\CMSIS\CM3\CoreSupport\下的两个文件放入Start\

![image-20260517135716151](.\screenShots\屏幕截图 2026-05-17 135703.png)

修改Target 1下组名为Start，双击或右键 -> Add Existing Files to Group "Start"，进入Start\文件夹后，设置“文件类型”为All files，选中startup_stm32f10x_md.s以及其他所有的.c和.h文件，点击Add

![image-20260517140438527](.\screenShots\屏幕截图 2026-05-17 140419.png)

启动文件startup_stm32f10x_md.s的选择是根据芯片flash容量确定的，不同flash大小的芯片选择不同的启动文件，参考如下

![image-20260517184422326](.\screenShots\屏幕截图 2026-05-17 184419.png)

点击魔术棒按钮 -> C/C++ -> Include Paths -> 新建按钮，然后选择Start\并确定

![image-20260517141314734](.\screenShots\屏幕截图 2026-05-17 141308.png)

## 测试工程是否创建成功

在项目文件夹中新建一个User文件夹，然后在Target 1下新建一个Group命名为User，用于存放用户代码

![image-20260517141653839](.\screenShots\屏幕截图 2026-05-17 141650.png)

魔术棒 -> 包含路径添加User\

![image-20260517145542001](.\Day1\screenShots\屏幕截图 2026-05-17 145539.png)

右键User -> Add New Item to Group 'User' -> C File(.c) -> Name为main -> location为User\路径

![image-20260517141929090](.\screenShots\屏幕截图 2026-05-17 141744.png)

打开main.c，右键插入头文件

![image-20260517142133105](.\screenShots\屏幕截图 2026-05-17 142017.png)

编写一个main函数，点击build按钮编译

![image-20260517142235811](.\screenShots\屏幕截图 2026-05-17 142233.png)

没有错误和警告，说明工程创建成功

## 一些设置

魔术棒 -> Debug选择ST-Link Debugger，

![image-20260517143221221](.\screenShots\屏幕截图 2026-05-17 143207.png)

点击右侧Settings按钮 ->Flash Download -> 勾选 Reset and Run

![image-20260517143410955](.\screenShots\屏幕截图 2026-05-17 143340.png)

魔术棒 -> Output -> 勾选生成hex文件，方便在Proteus仿真

![image-20260517143528166](.\screenShots\屏幕截图 2026-05-17 143433.png)

## 添加库函数

之前的项目只能实现基于寄存器的开发，还没有添加库函数

在项目文件夹下新建Library\文件夹，将STM32F10x_StdPeriph_Lib_V3.5.0\Libraries\STM32F10x_StdPeriph_Driver\下inc\和src\下的所有.c和.h文件放入Library

![image-20260517144238886](.\screenShots\屏幕截图 2026-05-17 144236.png)

在Keil中新建Library组并添加元素，然后添加路径，与Start组类似

将STM32F10x_StdPeriph_Lib_V3.5.0\Project\STM32F10x_StdPeriph_Template\下的三个.c或.h文件放到User\下，并更新Group User元素

![image-20260517144823561](.\screenShots\屏幕截图 2026-05-17 144818.png)

打开stm32f10x.h，找到末尾的判断语句，复制字符串

![image-20260517145234092](.\screenShots\屏幕截图 2026-05-17 145205.png)

魔术棒 -> C/C++ 定义这个字符串

![image-20260517145344952](.\screenShots\屏幕截图 2026-05-17 145324.png)

至此，基于库函数开发的项目框架就已经搭建完成了，接下来实现点灯操作并在Proteus中仿真

## 点亮LED

在`main.c`中写入以下代码并编译(Build)

```c
#include "stm32f10x.h"                  // Device header

int main(void)
{
	// 开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 配置端口模式
	GPIO_InitTypeDef GPIO_InitStruct;	// 定义GPIO初始化结构体
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	// 推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// 设置引脚
	GPIO_SetBits(GPIOB, GPIO_Pin_13);	// 设置引脚为高电平
	// GPIO_ResetBits(GPIOB, GPIO_Pin_13);		// 设置引脚为低电平
	
	while(1)
	{
		
	}
}

```

打开Proteus，新建工程，然后一路Next即可

![image-20260517151957020](.\screenShots\屏幕截图 2026-05-17 151947.png)

![image-20260517152110494](.\screenShots\屏幕截图 2026-05-17 152059.png)

双击DEVICES空白处添加设备，搜索关键词STM32，选择STM32F103C8，确定

![image-20260517152243777](.\screenShots\屏幕截图 2026-05-17 152215.png)

搜索LED，选择LED-BLUE，添加一个蓝色LED灯，确定

![image-20260517152349283](.\screenShots\屏幕截图 2026-05-17 152317.png)

绘制电路图，注意LED的连接方式，代码中目前设置PB13为高电平，如果希望运行时LED亮，就需要设置LED的点亮方式为高电平点亮，点亮方式由LED连接方式决定，三角形的边代表正极，角代表负极，负极接地时为高电平点亮，因此LED的连接方式应如图

![image-20260517152848904](.\screenShots\屏幕截图 2026-05-17 152837.png)

双击STM32F103C8编辑元件属性，Program File选择STM32 Project项目中的STM32Project\2-1newProject\Objects\Project.hex，OSC Frequency设置为72MHz

![image-20260517180229869](.\screenShots\屏幕截图 2026-05-17 180227.png)

点击左下角按钮开始仿真，可以观察到蓝色LED常亮

![image-20260517180815205](.\screenShots\屏幕截图 2026-05-17 180751.png)

