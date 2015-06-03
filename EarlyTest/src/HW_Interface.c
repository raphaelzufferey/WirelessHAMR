//#include <avr/io.h>

#include <asf.h>
#include "HW_Interface.h"
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
	
	DDRF |= 1<<BSR_SER;
	DDRF |= 1<<BSR_SRCLK;
	DDRF |= 1<<BSR_RCLK;
	
	PORTD |= (1<<LED_R);
	PORTD |= (1<<LED_B);
	PORTD |= (1<<LED_G);
		
	//while(1);	
	// Timer0 configuration
	// CLEAR ON OCRA, PRESCALER TO 64, CTC ON, OCR0A TO 124, OCR0A INT ENABLE
	TCCR1B |= (1 << WGM12); // WaveformGenerationMode13:10 = 0x4
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	OCR1A = 1000;
	//TCCR0A = 0b00000010; //timer control register A and B
	//TCCR1B |= ((1 << CS10) | (1 << CS11)); // ClockSelect12:10 = 0x03 = 64 Prescaler
	TCCR1B |= (1 << CS11); // ClockSelect12:10 = 0x03 = 8 Prescaler -> BASE TIMER FREQ IS 1 MHZ
	sei(); //enable global interrupt
	
}

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

//unsigned int : 2 bytes = 16 bits
void BSR_write(unsigned int data)
{
	BSR_PORT &= ~(1 << BSR_RCLK); 						// Set the register-clock pin low
	for (int i = 0; i < (8 * NB_BSR); i++)				// Now we are entering the loop to shift out 8+ bits
	{
		BSR_PORT &= ~(1 << BSR_SRCLK); 					// Set the serial-clock pin low
		BSR_PORT |= (((data&(0x01<<i))>>i) << BSR_SER );// Go through each bit of data and output it
		BSR_PORT |= (1 << BSR_SRCLK); 					// Set the serial-clock pin high
		BSR_PORT &= ~(((data&(0x01<<i))>>i) << BSR_SER);// Set the data pin low again
	}
	BSR_PORT |= (1 << BSR_RCLK);						// Set the register-clock pin high to update the output of the shift-register
}


int convert_legs_behavior_to_bsr(int* movement_state)
{
	int actuator_state[9] = {FLT};
	int transistor_state[16] = {0}; // NOT static !
	int bsr_array[16] = {0};
	int bsr_hex_command = 0x0;
	int i;
	
	/* Coupling movements to actuators */
	actuator_state[LFL] = movement_state[LIFT];
	actuator_state[LFR] = movement_state[LIFT];
	actuator_state[LRL] = movement_state[LIFT];
	actuator_state[LRR] = movement_state[LIFT];
	
	actuator_state[SFL] = movement_state[SWING_F];
	actuator_state[SFR] = movement_state[SWING_F];
	
	actuator_state[SRL] = movement_state[SWING_R];
	actuator_state[SRR] = movement_state[SWING_R];
	
	//  TEST PURPOSE //////////////////////////////////////////////
	//	OSCILLATING BETWEEN HV AND GND FOR SFL
	// 	static int phase = 0;
	// 	if(phase == 0) {actuator_state[LFR] = GND; phase = 1; }
	// 	else if(phase == 1) {actuator_state[LFR] = HV; phase = 0; }
	
	
	/* Matching actuator state to transistors switching*/
	for(i= 1; i<= 8 ; i++)
	{
		if(actuator_state[i] == GND) {transistor_state[2*i-1] = 1; }
		else if(actuator_state[i] == HV) {transistor_state[2*(i-1)] = 1; }
		else if(actuator_state[i] == FLT) {}// Leave both transistors at 0 default
	}
	
	/* Matching transistors state to correct BSR bits */
	bsr_array[T11] = transistor_state[0];
	bsr_array[T12] = transistor_state[1];
	bsr_array[T21] = transistor_state[2];
	bsr_array[T22] = transistor_state[3];
	bsr_array[T31] = transistor_state[4];
	bsr_array[T32] = transistor_state[5];
	bsr_array[T41] = transistor_state[6];
	bsr_array[T42] = transistor_state[7];
	bsr_array[T51] = transistor_state[8];
	bsr_array[T52] = transistor_state[9];
	bsr_array[T61] = transistor_state[10];
	bsr_array[T62] = transistor_state[11];
	bsr_array[T71] = transistor_state[12];
	bsr_array[T72] = transistor_state[13];
	bsr_array[T81] = transistor_state[14];
	bsr_array[T82] = transistor_state[15];
	
	/* convert the 8 actuator state values to 16 bit transistor BSR */
	
	bsr_hex_command = 0x00; // 1 int = 2 bytes. Reset register, defaults to float state
	for(i = 0; i <= 15 ; i++)
	{
		bsr_hex_command |= bsr_array[i] << (15 - i);
	}
	
	uint8_t bsr_hex_low = (uint8_t)bsr_hex_command;
	uint8_t bsr_hex_high = (uint8_t)(bsr_hex_command >> 8);
	
	//USART_Send(bsr_hex_low);
	//USART_Send(bsr_hex_high);
	
	return bsr_hex_command;
}