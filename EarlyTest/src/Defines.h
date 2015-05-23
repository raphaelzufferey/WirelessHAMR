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