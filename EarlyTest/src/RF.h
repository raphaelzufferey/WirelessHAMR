#ifndef _RF_H
#define _RF_H

/* TRX STATE*/
#define PLL_ON		9
#define RX_ON		6
#define TRX_OFF		8

//  Initializes the radio on a channel between 11 and 26.
uint8_t rfBegin(uint8_t channel);

uint8_t rfInitStd802_15_4(void);

//Sends a byte over the radio
void rfWrite(uint8_t b);

//Sends a string over the radio
// void rfPrint(String toPrint);

//Returns number of characters currently in receive buffer, ready to be read.
unsigned int rfAvailable(void);

//Reads a character out of the buffer
char rfRead(void);

#endif //_RF_H