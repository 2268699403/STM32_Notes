#include "stm32f10x.h"                  // Device header
/**
  *函  数：初始化A1、A2
  *参  数：无
  *返回值：无
  */

void LED_Init(void)												//初始化A1、A2
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//配置时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;						//创建初始化结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			//配置引脚输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;		//配置引脚选中
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//配置引脚输出频率
	GPIO_Init(GPIOA,&GPIO_InitStructure);						//初始化GPIO
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}


/**
  *函  数：LED1开启
  *参  数：无
  *返回值：无
  */

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

/**
  *函  数：LED1关闭
  *参  数：无
  *返回值：无
  */

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

/**
  *函  数：LED2开启
  *参  数：无
  *返回值：无
  */

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

/**
  *函  数：LED2关闭
  *参  数：无
  *返回值：无
  */

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
