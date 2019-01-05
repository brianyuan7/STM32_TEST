#include "usart.h"

void USART1_Init(u32 Baud)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
  USART_InitTypeDef  USART_InitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
  /* Configure USART tx pins */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10; //TX RX都为AF_PP即可
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);       	
	
	NVIC_InitStructure.NVIC_IRQChannel= USART1_IRQn;  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;  
	NVIC_Init(&NVIC_InitStructure);   //nvic_init必须每个都有	
	
	USART_InitStruct.USART_BaudRate = Baud;//921600;//1825200;//460800
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
  /* Enable UART clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
  /* USART configuration */
  USART_Init(USART1, &USART_InitStruct);
      
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //必须在cmd之前打开     
       
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);	    
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
	return (ch);
}

