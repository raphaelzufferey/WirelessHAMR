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
//#include "EarlyTest.h"
#include "HW_Interface.h"
#include "RF.h"

#include "UART.h"

void setup(void);

void setup(void)
{
	int i = 0;
	for(i=0; i<10; i++)
	{
		led_control(LED_B, SWAP);
		_delay_ms(400);
	}
}

int main (void)
{
	board_init();
	setup();
	USART_Init();
	
	if(rfBegin(11) == SUCCESS)
		USART_Send_String("RF Started with success\n");
	else 
		USART_Send_String("Houston, we have a problem. RF NOT WORKING\n");
	
	char ReceivedByte;
	USART_Send_String("Echo mode ON :\n");	
		
	for (;;) // Loop forever
	{
		
		/* Read characters from USART */
		//while ((UCSR0A & (1 << RXC0)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
		ReceivedByte = '\n'; // Fetch the received byte value into the variable "ByteReceived"
		led_control(LED_R, ON);		
		rfWrite(ReceivedByte);
				
		while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
		UDR0 = ReceivedByte; // Echo back the received byte back to the computer
		led_control(LED_R, OFF);		

		_delay_ms(100);		
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
	led_control(LED_G, SWAP);
	
	static int tick = 0;
	// 1 tick should be 1ms
	if (tick == 99) 
	{ 
		tick = 0; 
	}
	else 
	{ 
		tick = tick + 1; 
	}

	if (tick == 0) { pulse();	PORTC |= 0b00100001; }	// Pulse SF lo, SR hi
	if (tick == 30) {			PORTC &= 0b11011110; }	// End pulse
	if (tick == 24) { pulse();	PORTC |= 0b00001000; }	// Pulse LIFTS lo
	if (tick == 49) {			PORTC &= 0b11110111; }	// End pulse
	if (tick == 50) { pulse();	PORTC |= 0b00010010; }	// Pulse SR lo, SF hi
	if (tick == 80) {			PORTC &= 0b11101101; }	// End pulse
	if (tick == 74) { pulse();	PORTC |= 0b00000100; }	// Pulse LIFTS hi
	if (tick == 98) {			PORTC &= 0b11111011; }	// End pulse

}

// This interrupt service routine pulses the DC-DC converter switch when the analog comparator reports undervoltage
ISR(ANALOG_COMP_vect) 
{
	// simply returns state of aco if low or someth else
	while(bit_is_set(ACSR,ACO)) {
	// Pulse the switch
	PORTD |= (1<<PORTD5);
	__builtin_avr_delay_cycles(2);
	PORTD &= (0<<PORTD5);

	// Wait a bit to give things time to adjust
	__builtin_avr_delay_cycles(20);
	}
}
