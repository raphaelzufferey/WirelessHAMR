/*
 * Defines.h
 *
 * Created: 05-May-15 11:29:14 AM
 *  Author: Raph
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_


#define USART_BAUDRATE 9600
#define F_CPU	8000000
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define SUCCESS 1
#define FAILURE 0
#define OFF 0
#define ON 1
#define SWAP 2

#define LED_G 3
#define LED_B 4
#define LED_R 2


#define FLSH 1 
#define FLSL 1
#define FLLH 1
#define FLLL 1

#define BSR_SRCLK	PORTF1 //TO BE CHECKED
#define BSR_RCLK	PORTF2
#define BSR_SER		PORTF0
#define BSR_PORT	PORTF // IS THAT A VALID SYNTAX?
#define NB_BSR		2 //How many of the shift registers are daisy-chained


#define T11	0x2
#define T12	0x3
#define T21	0x6
#define T22	0x7
#define T31	0x1
#define T32	0x0
#define T41	0x4
#define T42	0x5
#define T51	14
#define T52	15
#define T61	13
#define T62	12
#define T71	9
#define T72	8
#define T81	10
#define T82	11

#define LFL 6
#define LFR 1
#define LRL 8
#define LRR 4
#define SFL 7
#define SFR 2
#define SRL 5
#define SRR 3

#define GND 0
#define HV	1
#define FLT 2

#define LIFT 0
#define SWING_F 1
#define SWING_R 2

#define NOW	0
#define NEXT	1
#define FLOAT_V 0
#define HV_OR_GND 1
#define TRUE 1
#define FALSE 0

// /*
// typedef enum tal_trx_status_tag {
// 	/** Constant P_ON for sub-register @ref SR_TRX_STATUS */
// 	P_ON =                              (0x00),
// 
// 	/** Constant BUSY_RX for sub-register @ref SR_TRX_STATUS */
// 	BUSY_RX =                           (0x01),
// 
// 	/** Constant BUSY_TX for sub-register @ref SR_TRX_STATUS */
// 	BUSY_TX =                           (0x02),
// 
// 	/** Constant RX_ON for sub-register @ref SR_TRX_STATUS */
// 	RX_ON =                             (0x06),
// 
// 	/** Constant TRX_OFF for sub-register @ref SR_TRX_STATUS */
// 	TRX_OFF =                           (0x08),
// 
// 	/** Constant PLL_ON for sub-register @ref SR_TRX_STATUS */
// 	PLL_ON =                            (0x09),
// 
// 	/** Constant TRX_SLEEP for sub-register @ref SR_TRX_STATUS */
// 	TRX_SLEEP =                         (0x0F),
// 
// 	/** Constant BUSY_RX_AACK for sub-register @ref SR_TRX_STATUS */
// 	BUSY_RX_AACK =                      (0x11),
// 
// 	/** Constant BUSY_TX_ARET for sub-register @ref SR_TRX_STATUS */
// 	BUSY_TX_ARET =                      (0x12),
// 
// 	/** Constant RX_AACK_ON for sub-register @ref SR_TRX_STATUS */
// 	RX_AACK_ON =                        (0x16),
// 
// 	/** Constant TX_ARET_ON for sub-register @ref SR_TRX_STATUS */
// 	TX_ARET_ON =                        (0x19),
// 
// 	/** Constant RX_ON_NOCLK for sub-register @ref SR_TRX_STATUS */
// 	RX_ON_NOCLK =                       (0x1C),
// 
// 	/** Constant RX_AACK_ON_NOCLK for sub-register @ref SR_TRX_STATUS */
// 	RX_AACK_ON_NOCLK =                  (0x1D),
// 
// 	/** Constant BUSY_RX_AACK_NOCLK for sub-register @ref SR_TRX_STATUS */
// 	BUSY_RX_AACK_NOCLK =                (0x1E),
// 
// 	/** Constant STATE_TRANSITION_IN_PROGRESS for sub-register @ref
// 	 *SR_TRX_STATUS */
// 	STATE_TRANSITION_IN_PROGRESS =      (0x1F)
// }  tal_trx_status_t;
// */
#endif /* DEFINES_H_ */