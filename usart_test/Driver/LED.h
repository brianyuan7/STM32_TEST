#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"

void LED_Init(void);
#define LED_RED_ON		            GPIO_SetBits(GPIOC, GPIO_Pin_9)//paras: GPIOx, GPIO_Pinx
#define LED_RED_OFF 	            GPIO_ResetBits(GPIOC, GPIO_Pin_9)
#define LED_YELLOW_ON		          GPIO_SetBits(GPIOC, GPIO_Pin_8)
#define LED_YELLOW_OFF 	          GPIO_ResetBits(GPIOC, GPIO_Pin_8)
#define LED_YELLOW_GREEN_ON		    GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define LED_YELLOW_GREEN_OFF 	    GPIO_ResetBits(GPIOC, GPIO_Pin_7)
#define LED_BLUE_ON		            GPIO_SetBits(GPIOC, GPIO_Pin_6)
#define LED_BLUE_OFF 	            GPIO_ResetBits(GPIOC, GPIO_Pin_6)

#endif

