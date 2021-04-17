#include "stm32l031lib.h"
int main()
{
	char ch;
	initSerial();
	while(1)
	{
		ch=egetchar();
		ch = ch | 32;  // force lower case for letters
		switch (ch) 
		{
			case 'a' : 
			{
				eputs("you pressed A\r\n");
				break;
			}
			case 'b' : 
			{
				eputs("you pressed B\r\n");
				break;
			}
			case 'c' : 
			{
				eputs("you pressed C\r\n");
				break;
			}
			case 'd' : 
			{
				eputs("you pressed D\r\n");
				break;
			}
			case 'e' : 
			{
				eputs("you pressed E\r\n");
				break;
			}
			case 'f' : 
			{
				eputs("you pressed F\r\n");
				break;
			}
		}
	}
	
}
