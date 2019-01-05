#include "delay.h"

void delay_us(u32 uTime) 
{ 
  u32 temp;
  SysTick->LOAD = 16*uTime/8;//HCLK��1/8
  SysTick->VAL = 0x00;//���
	SysTick->CTRL = 0x01;//ʹ��
	do
	{
	 temp = SysTick->CTRL;//��ȡ��ǰ����ʱֵ
	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	  
	SysTick->CTRL = 0x00;//�رռ�����
	SysTick->VAL = 0x00;//���
}

void delay_ms(u32 mTime)
{
  u32 temp;
  SysTick->LOAD = 16*1000*mTime/8;
  SysTick->VAL = 0x00;//���
	SysTick->CTRL = 0x01;//ʹ��
	do
	{
	 temp = SysTick->CTRL;//��ȡ��ǰ����ʱֵ
	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	  
	SysTick->CTRL = 0x00;//�رռ�����
	SysTick->VAL = 0x00;//��
}
