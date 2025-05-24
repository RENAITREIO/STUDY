#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "Key.h"
#include "Store.h"

uint8_t KeyNum = 2;

int main()
{
	OLED_Init();
	OLED_ShowHexNum(4,1,Store_Data[1],4);
	Store_Init();
	OLED_ShowHexNum(3,1,Store_Data[1],4);
	while(1)
	{
		//KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			OLED_ShowString(1,9,"R");
			Store_Data[1]++;
			Store_Save();
		}
		else if(KeyNum == 2)
		{
			//OLED_ShowString(1,9,"R");
			Store_Clear();
			KeyNum = 0;
		}
		
		OLED_ShowHexNum(1,1,Store_Data[1],4);
		OLED_ShowHexNum(2,1,Store_Data[2],4);
	}
}
