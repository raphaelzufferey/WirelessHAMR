/*
main.c
Contains HAMR main program
Raphael Zufferey 06/2015

				main.c
					|
		---------------------------
		|				|		  |
	HW_Interface		RF		UART
		|				|		  |
	    ---------------------------
		|
	Defines.h
		
		
*/

#include <asf.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "main.h"
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
	//setup();
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
		while ((UCSR0A & (1 << RXC0)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
		ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
		led_control(LED_R, ON);		
		rfWrite(ReceivedByte);
				
		while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
		UDR0 = ReceivedByte; // Echo back the received byte back to the computer
		led_control(LED_R, OFF);		
		
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
	static int tick = 0;
	// 1 tick should be 1ms
	if (tick == 99) {tick = 0;}	else {tick += 1;}

	static int movement_state[3] = {FLT, FLT, FLT};
	int bsr_hex_command = 0x0;
	int actuators_changed = TRUE; // NOT static ! Needs to be reset to TRUE
	
	/* Gait pattern */
	switch(tick)
	{
		case 0 : movement_state[LIFT]	= FLT;	movement_state[SWING_F] = GND;	movement_state[SWING_R] = HV;	break;
		case 24: movement_state[LIFT]	= GND;																	break;
		case 30:								movement_state[SWING_F] = FLT;	movement_state[SWING_R] = FLT;	break;
		case 49:								movement_state[SWING_F] = HV;	movement_state[SWING_R] = GND;	break;	
		case 54: movement_state[LIFT]	= FLT;																	break;
		case 74: movement_state[LIFT]	= HV;																	break;
		case 80:								movement_state[SWING_F] = FLT;	movement_state[SWING_R] = FLT;	break;
		case 99: led_control(LED_G, SWAP);																		break;
		default: actuators_changed = FALSE;
	}
		
	if(actuators_changed == TRUE)
	{
		bsr_hex_command = convert_legs_behavior_to_bsr(movement_state);
		USART_Send_String("BSR_Hex_command:");
		USART_Send(bsr_hex_command);
		BSR_write(bsr_hex_command);
	}
}

// This interrupt service routine pulses the DC-DC converter switch when the analog comparator reports undervoltage
ISR(ANALOG_COMP_vect)
{
	// 	// simply returns state of aco if low or someth else
	// 	while(bit_is_set(ACSR,ACO))
	// 	{
	// 		// Pulse the switch
	// 		PORTD |= (1<<PORTD5);
	// 		_delay_loop_1(2); //prev: __builtin_avr_delay_cycles(2);
	// 		PORTD &= (0<<PORTD5);
	//
	// 		// Wait a bit to give things time to adjust
	// 		_delay_loop_1(20); //prev:__builtin_avr_delay_cycles(20);
	// 	}
}

