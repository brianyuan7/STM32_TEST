#include "usart.h"
#include "stm32f4xx_dma.h"


char dma_usart1_tx_buffer[DMA_USART1_TX_MAX_SIZE];
char dma_usart1_rx_buffer[DMA_USART1_RX_MAX_SIZE];

void USART1_Init(uint32_t Baud)
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
      
  //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
  USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//Enable IDLE interrupt for DMA reveive
	 
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);	    
}

/* DMA init for USART1
USART1 TX: DMA2 channel4 stream 7
USART1 RX: DMA2 channel4 stream 5
*/
void DMA_USART1_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	//Configure DMA TX
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); 
	DMA_DeInit(DMA2_Stream7);
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE);
	
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;  
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)dma_usart1_tx_buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;    
  DMA_InitStructure.DMA_BufferSize = DMA_USART1_TX_MAX_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;   
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;   
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;     
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;   //disable FIFO     
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;  
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
  DMA_Init(DMA2_Stream7, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel= DMA2_Stream7_IRQn;  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;  
	NVIC_Init(&NVIC_InitStructure);
	
  DMA_ITConfig(DMA2_Stream7, DMA_IT_TC,ENABLE); //enable DMA transfer complete interrupt
  DMA_Cmd(DMA2_Stream7, ENABLE);    
    
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);//enable USART DMA TX    
	
		//Configure DMA RX
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); 
	DMA_DeInit(DMA2_Stream5);
	while (DMA_GetCmdStatus(DMA2_Stream5) != DISABLE);
	
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;  
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)dma_usart1_rx_buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;    
  DMA_InitStructure.DMA_BufferSize = DMA_USART1_RX_MAX_SIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;   
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;   
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;     
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;   //disable FIFO     
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;  
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
  DMA_Init(DMA2_Stream5, &DMA_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel= DMA2_Stream5_IRQn;  
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;  
	NVIC_Init(&NVIC_InitStructure);
	
  DMA_Cmd(DMA2_Stream5, ENABLE);    
    
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);//enable USART DMA RX  
}


 
void DMA_Send_Data_Proc(DMA_Stream_TypeDef *DMA_Streamx,uint16_t ndtr)
{
	DMA_Cmd(DMA_Streamx, DISABLE);                      
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE);	 	
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);         
	DMA_Cmd(DMA_Streamx, ENABLE);                     
}

void DMA_USART1_Send_One_Byte(char byte)
{
	char *pBuf = NULL;
	
	pBuf = dma_usart1_tx_buffer;
	*pBuf++ = byte;
 
	DMA_Send_Data_Proc(DMA2_Stream7,1);	  
}

void DMA_USART1_Send_Bytes(char* buffer, uint16_t size)
{
	uint16_t i = 0;
	char *pBuf = NULL;

	pBuf = dma_usart1_tx_buffer;
 
	for (i = 0; i < size; i++)
	{
		*pBuf++ = buffer[i];
	}

	DMA_Send_Data_Proc(DMA2_Stream7,size);   
}


int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);
	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
	return (ch);
}

