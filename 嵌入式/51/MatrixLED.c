#include <REGX52.H>
#include "Delay.h"

sbit RCK=P3^5;	//RCLK
sbit SCK=P3^6;	//SRCLK
sbit SER=P3^4;	//SER

void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);
		SCK=1;
		SCK=0;
	}
	RCK=1;
	RCK=0;
}

void MatrixLED_ShowColumn(unsigned char Column,Data)
{
	_74HC595_WriteByte(Data);
	P0=~(0x80>>Column);
	Delay(1);
	P0=0xFF;
}

void Matrix_Init()
{
	SCK=0;
	RCK=0;
}