#include "delay.h"

void delay_us(u32 uTime) 
{ 
  u32 temp;
  SysTick->LOAD = 16*uTime/8;//HCLKµƒ1/8
  SysTick->VAL = 0x00;//«Âø’
	SysTick->CTRL = 0x01;// πƒ‹
	do
	{
	 temp = SysTick->CTRL;//∂¡»°µ±«∞µπº∆ ±÷µ
	}while((temp&0x01)&&(!(temp&(1<<16))));//µ»¥˝ ±º‰µΩ¥Ô
	  
	SysTick->CTRL = 0x00;//πÿ±’º∆ ˝∆˜
	SysTick->VAL = 0x00;//«Âø’
}

void delay_ms(u32 mTime)
{
  u32 temp;
  SysTick->LOAD = 16*1000*mTime/8;
  SysTick->VAL = 0x00;//«Âø’
	SysTick->CTRL = 0x01;// πƒ‹
	do
	{
	 temp = SysTick->CTRL;//∂¡»°µ±«∞µπº∆ ±÷µ
	}while((temp&0x01)&&(!(temp&(1<<16))));//µ»¥˝ ±º‰µΩ¥Ô
	  
	SysTick->CTRL = 0x00;//πÿ±’º∆ ˝∆˜
	SysTick->VAL = 0x00;//«Âø
}
