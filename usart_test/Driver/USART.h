#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <stdio.h>

#define DMA_USART1_TX_MAX_SIZE 100
#define DMA_USART1_RX_MAX_SIZE 100

void USART1_Init(uint32_t Baud);

void DMA_USART1_Init(void);
void DMA_Send_Data_Proc(DMA_Stream_TypeDef *DMA_Streamx,uint16_t ndtr);
void DMA_USART1_Send_One_Byte(char byte);
void DMA_USART1_Send_Bytes(char* buffer, uint16_t size);

int fputc(int ch, FILE *f);
#endif

