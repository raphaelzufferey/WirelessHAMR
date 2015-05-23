/*
 * UART.h
 *
 * Created: 12-May-15 4:22:01 PM
 *  Author: Raph
 */ 


#ifndef UART_H_
#define UART_H_


void USART_Init(void);
int USART_Send(char sendByte);
void USART_Send_String(char *command);


#endif /* UART_H_ */