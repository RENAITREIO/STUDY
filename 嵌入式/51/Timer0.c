#include <REGX52.H>

void Timer0_Init(void)
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TL0 = 0;
	TH0 = 0;
	TF0 = 0;
	TR0 = 0;
}

void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}

unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;
}

void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}