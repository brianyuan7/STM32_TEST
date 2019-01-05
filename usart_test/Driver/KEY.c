#include "led.h"


void KEY_Init()
{
  GPIO_InitTypeDef     GPIO_InitStructure;    
  EXTI_InitTypeDef     EXTI_InitStructure;
  NVIC_InitTypeDef     NVIC_InitStructure; 

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5  | GPIO_Pin_9;	//主板2个
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource5); //设置pinsource
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //低电平有效，  falling
  EXTI_Init(&EXTI_InitStructure);	

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource9); //设置pinsource
  EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //低电平有效，  falling
  EXTI_Init(&EXTI_InitStructure);	

	NVIC_InitStructure.NVIC_IRQChannel= EXTI9_5_IRQn;   //EXTI9_5  EXTI15_10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;
	NVIC_Init(&NVIC_InitStructure); 		 
}
