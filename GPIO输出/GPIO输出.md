# GPIO输出

## 编程要点

1. 使能GPIO时钟。
2. 初始化GPIO目标引脚输出模式。

### 使能GPIO时钟

调用库函数`RCC_APB2PeriphClockCmd`来使能GPIO端口时钟
`RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);`

### 初始化GPIO引脚

使用`GPIO_InitTypeDef`定义GPIO初始化结构体变量，用于存储GPIO配置。
`GPIO_InitTypeDef GPIO_InitStructure;`

向 GPIO 初始化结构体赋值，把引脚初始化成推挽输出模式
```
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
```

使用以上初始化结构体的配置，调用 GPIO_Init 函数向寄存器写入参数，完成 GPIO 的初始
化。
`GPIO_Init(GPIOA,&GPIO_InitStructure);`

### 编写简单测试程序

```
#include <stm32f10x.h>                
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	while(1)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		Delay_ms(500);
	}
}

```

## 函数解释

`void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)`
启用连接到APB2高速总线上的外设时钟
>STM32微控制器为了降低功耗，在外设不使用时，其时钟是默认关闭的。因此，在使用任何外设之前，​必须首先开启其时钟。

`void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`
将指定的一或多个引脚设置为高电平

`void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`
将指定的一或多个引脚设置为低电平
>它们的 GPIO_Pin参数支持使用按位或运算符 |来组合多个引脚。例如，GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_5)可以同时将PA0和PA5置为高电平。

`void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)`
设置单个引脚为高电平或低电平
>与 GPIO_SetBits不同，GPIO_WriteBit的 GPIO_Pin参数通常只能指定单个引脚，不能使用 |组合多个引脚

`void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)`
一次性设置整个端口（16个引脚）的所有输出状态
>此函数直接向ODR（输出数据寄存器）写入一个16位的值，会直接设置整个端口所有16个引脚的输出状态。使用时需要特别注意，因为它会覆盖所有引脚的当前状态。