/* 
 * File:   usart.h
 * Author: Hesham
 *
 * Created on October 8, 2024, 6:51 AM
 */

#ifndef USART_H
#define	USART_H

#include"../../MCAL_Layer/interrupt/internal_interrupt.h"

/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_08BIT_BAUDRATE_GEN  		0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0

/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

typedef struct{
    Interrupt_Priority_Levels usart_tx_int_priority;
	u8 usart_tx_enable : 1;
	u8 usart_tx_interrupt_enable : 1;
	u8 usart_tx_9bit_enable : 1;
    u8 usart_tx_reserved : 5;
}usart_tx_cfg_t;

typedef struct{
    Interrupt_Priority_Levels usart_rx_int_priority;
	u8 usart_rx_enable : 1;
	u8 usart_rx_interrupt_enable : 1;
	u8 usart_rx_9bit_enable : 1;
    u8 usart_rx_reserved : 5;
}usart_rx_cfg_t;

typedef union{
	struct{
		u8 usart_tx_reserved : 6;
		u8 usart_ferr : 1; //framing error
		u8 usart_oerr : 1;//overrun error
	};
	u8 status;
}usart_error_status_t;

typedef struct{
    u32 baudrate;
    baudrate_gen_t baudrate_gen_gonfig;
    usart_tx_cfg_t usart_tx_cfg;
	usart_rx_cfg_t usart_rx_cfg;
	usart_error_status_t error_status;
	void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}usart_t;

Return_Status Uart_Init(usart_t* uart_obj);
Return_Status Uart_DeInit(usart_t* uart_obj);
Return_Status Uart_ReadByteBlocking(u8 *data);
Return_Status Uart_ReadByteNonBlocking(u8 *data);
Return_Status Uart_WriteByteBlocking(u8 data);
Return_Status Uart_WriteStringBlocking(u8 *data);
#endif	/* USART_H */

