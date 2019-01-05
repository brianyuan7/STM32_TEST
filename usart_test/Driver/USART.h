#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <stdio.h>

void USART1_Init(u32 Baud);
int fputc(int ch, FILE *f);

#endif

