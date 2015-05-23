/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Defines.h"
#include <util/delay.h>
#include "EarlyTest.h"
#include "HW_Interface.h"
#include "RF.h"

#include "UART.h"



void setup(void);

void setup(void)
{
	int i = 0;
	for(i=0; i<10; i++)
	{
		led_control(6,i%2);
		led_control(7,(i+1)%2);
		_delay_ms(100);
	}
	
	// RF Configuration
	if(rfBegin(11) == SUCCESS)
		USART_Send_String("RF SUCCESS");
	else
		USART_Send_String("RF SUCCESS");
}



int main (void)
{
	/* Initialize the board.
	 * The board-specific conf_board.h file contains the configuration of
	 * the board initialization.
	 */
	board_init();
	USART_Init();
	setup();
	
	char ReceivedByte;
	char rf_receive_char;
			
	for (;;) // Loop forever
	{
		
		/* Send characters from USART */
 		while ((UCSR0A & (1 << RXC0)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
 		ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
		
		rfWrite(ReceivedByte);
		
		
		
// 		while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
// 		UDR0 = ReceivedByte; // Echo back the received byte back to the computer
		//_delay_ms(100);
		
		
		/* WRITE PART */
// 		rfWrite(0x77);
// 		_delay_ms(300);
// 		rfWrite('a');
// 		_delay_ms(300);
// 		rfWrite('b');
// 		_delay_ms(300);
// 		led_control(6,SWAP);
// 		led_control(7,SWAP);
// 		
		
		/* READ PART */
// 		if(rfAvailable())
// 		{
// 			USART_Send_String("Char available:");
// 			rf_receive_char = rfRead();
// 			while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
// 			UDR0 = rf_receive_char; // Echo back the received byte back to the computer
// 			_delay_ms(1);
// 			USART_Send_String("\n");
// 			
// 		}
// 		led_control(6,SWAP);
// 		led_control(7,SWAP);
// 		_delay_ms(10);
	}
}


ISR(TIMER1_COMPA_vect) // replace all spaces with underscores, and append "_vect" to the end of the vector's name.
{
// 	static int mem = 0;
// 	if(mem)
// 	{
// 		led_control(7,0);
// 		mem = 0;
// 	}
// 	else
// 	{
// 		led_control(7,1);
// 		mem = 1;
// 	}
}
