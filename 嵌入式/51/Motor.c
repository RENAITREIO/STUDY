#include <REGX52.H>
#include "Timer1.h"

sbit Motor=P1^0;

unsigned char Counter,Compare;

void Motor_Init(void)
{
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char Speed)
{
	Compare=Speed;
}

void Timer1_Routine() interrupt 3
{
	TL1 = 0x9C;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	Counter++;
	Counter%=100;	//计数值变化范围限制在0~99
	if(Counter<Compare)	//计数值小于比较值
	{
		Motor=1;		//输出1
	}
	else				//计数值大于比较值
	{
		Motor=0;		//输出0
	}
}
