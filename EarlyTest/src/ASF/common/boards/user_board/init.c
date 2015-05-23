/**
 * \file
 *
 * \brief User board initialization template
 *
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>
#include "Defines.h"

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */

	
	DDRD |= 1<<LED_R;
	DDRD |= 1<<LED_G;
	DDRD |= 1<<LED_B;
	
	PORTD = (1<<LED_R);
	PORTD |= (1<<LED_B);
	PORTD |= (1 << LED_G);
		
	//while(1);	
	// Timer0 configuration
	// CLEAR ON OCRA, PRESCALER TO 64, CTC ON, OCR0A TO 124, OCR0A INT ENABLE
	TCCR1B |= (1 << WGM12); // WaveformGenerationMode13:10 = 0x4
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	OCR1A = 15624;
	//TCCR0A = 0b00000010; //timer control register A and B
	TCCR1B |= ((1 << CS10) | (1 << CS11)); // ClockSelect12:10 = 0x03 = 64 Prescaler
	sei(); //enable global interrupt
	
}
