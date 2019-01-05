#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

void SysTick_Init(void);
void delay_ms(u32 mTime);
void delay_us(u32 uTime);
void TimingDelay_Decrement(void);

#endif

