#include "main.h"
#include "delay.h"
#include "KEY.h"
#include "USART.h"
#include "LED.h"
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
	
//  KEY_Init();//中断模式需要进行EXTI配置 优先级01
	
	USART1_Init(115200);//串口发送数据 优先级02		
	
  int a = -5;
	int c = 0;
	printf("\nhello world!");
	
	while(1)
	{
		LED_YELLOW_ON;
		c++;
		USART_SendData(USART1, c);
		while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);	
		delay_ms(1000);
				
		LED_YELLOW_OFF;
		delay_ms(1000);
		a++;
		printf("\r\nThe next num is: %d\r\n",a);
	}
	
}

