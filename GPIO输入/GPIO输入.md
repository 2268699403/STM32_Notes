# GPIO输入

## 实现过程

1. 使能GPIO端口时钟
2. 初始化GPIO目标引脚为输入模式

编写函数获取输入信息
```
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum;
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
		Delay_ms(20);		
		KeyNum = 1;
	}
	
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);
		Delay_ms(20);		
		KeyNum = 2;
	}
	
	
	return KeyNum;
}

```
>触点式按键输入要考虑消抖

## 函数解释

`uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`
读取指定引脚的输入电平
返回值 Bit_SET(1) 或 Bit_RESET(0)

`uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)`
读取整个端口的输入电平
返回值 读取整个端口的输入电平

`uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`
读取指定引脚的输出锁存器ODR状态
返回值 Bit_SET(1) 或 Bit_RESET(0)

`uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)`
读取整个端口的输出锁存器状态
返回值 16位数据，每位代表一个引脚的输出状态

|特性对比|GPIO_ReadOutputDataBit|GPIO_ReadInputDataBit|
|---|---|----|
|读取目标|输出数据寄存器 (ODR)|输出数据寄存器 (ODR)|
|数据来源|MCU希望引脚输出的电平（软件设置的意图）|引脚上实际测量到的物理电压电平|
|核心概念|读取的是“想法”|读取的是“现实”|
|典型应用场景|查询之前代码设置的输出状态，用于逻辑判断（如状态翻转）|检测外部信号的真实状态（如按键、传感器）|

>如果你的引脚设置为输出，但连接的负载过重（如直接驱动一个大功率LED而无三极管），或者外部有强上拉/下拉电阻，可能导致引脚的实际电压（IDR读取值）无法达到MCU期望输出的电压（ODR的值）。例如，ODR设置为高电平（1），但外部电路将其强行拉低，此时IDR读到的可能就是低电平（0）。