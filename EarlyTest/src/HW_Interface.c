#include <avr/io.h>
#include "HW_Interface.h"
#include "Defines.h"

void led_control(int color, int state)
{
	if((color == LED_B) || (color == LED_R) || (color == LED_G))
	{
		switch(state)
		{
			
			case ON :	PORTD &= ~(1<<color); break;
			case OFF :	PORTD |= (1<<color); break;
			case SWAP :	PORTD ^= (1<<color); break;
		}
			
	}

}