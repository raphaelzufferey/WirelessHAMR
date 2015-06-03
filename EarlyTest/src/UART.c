/*
 * UART.c
 *
 * Created: 12-May-15 4:21:50 PM
 *  Author: Raph
 */ 

#include <asf.h>
#include "Defines.h"
#include "UART.h"
//#include "HW_Interface.h"
#include <util/delay.h>

void USART_Init(void)
{
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes

	UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	
	USART_Send_String("USART initiated");
} // USART_Init

int USART_Send(char sendByte)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = sendByte;
	return SUCCESS;
}

void USART_Send_String(char *command){

	while(*command != 0x00){
		USART_Send(*command);
	command++;}
}
