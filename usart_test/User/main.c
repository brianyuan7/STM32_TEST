#include "main.h"
#include "delay.h"
#include "KEY.h"
#include "USART.h"
#include "LED.h"
#include "string.h"

extern uint8_t g_key1_flag;
extern uint8_t g_key2_flag;
extern uint8_t g_rx1_data_ready;
	
char str1_welcome[DMA_USART1_TX_MAX_SIZE] = {"KEY1, DMA2 CH4 Stream7!"};
char str2_welcome[DMA_USART1_TX_MAX_SIZE] = {"KEY2, DMA!"};

extern char dma_usart1_rx_buffer[DMA_USART1_RX_MAX_SIZE];

/*****************************************************************************
  * @brief  Main program.
  * @param  None
  * @retval None
  ***************************************************************************/
int main(void)
{
	SystemInit();	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	LED_Init();
	LED_RED_ON;
	delay_ms(1000);
	LED_RED_OFF;
	
	KEY_Init();//中断模式需要进行EXTI配置 优先级01
	
	USART1_Init(115200);//串口发送数据 优先级02		
	
	printf("\r\nhello world!\r\n");
	
	DMA_USART1_Init();
	
	while(1)
	{	
		if (1U == g_key1_flag)
		{
			printf("\r\nTX: ");
			DMA_USART1_Send_Bytes(str1_welcome, DMA_USART1_TX_MAX_SIZE);
			g_key1_flag = 0;
			LED_YELLOW_ON;
		}
		else if (1U == g_key2_flag)
		{
			printf("\r\nTX: ");
			DMA_USART1_Send_Bytes(str2_welcome, DMA_USART1_TX_MAX_SIZE);
			g_key2_flag = 0;
			LED_BLUE_ON;			
		}
		LED_YELLOW_OFF;
		LED_BLUE_OFF;
		
		if (1U == g_rx1_data_ready)
		{
			printf("\r\nRX: ");
			DMA_USART1_Send_Bytes(dma_usart1_rx_buffer, DMA_USART1_RX_MAX_SIZE);
			memset(dma_usart1_rx_buffer, 0, DMA_USART1_RX_MAX_SIZE);
		  g_rx1_data_ready = 0;
		}
		
	}
	
}

