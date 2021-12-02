#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>
#include "queue.h"

typedef struct 
{
	size_t bytes_per_data;
	Q_T TxQ;
	Q_T RxQ;
} uart_transeiver_t;

#define USE_UART_INTERRUPTS (1)

#define UART_OVERSAMPLE (16)
#define BUS_CLOCK 			(24e6)

void Init_UART1(uint32_t baud_rate, size_t data_bytes, uart_transeiver_t* transeiver);
void Init_UART2(uint32_t baud_rate, size_t data_bytes, uart_transeiver_t* transeiver);

// poling
void UART0_Transmit_Poll(uint8_t data);
void UART1_Transmit_Poll(uint8_t data);

uint8_t UART1_Receive_Poll(void);

// interrupts
void Send_String(uint8_t * str);
uint32_t Get_Num_Rx_Chars_Available(void);
uint8_t	Get_Char(void);


extern Q_T TxQ, RxQ;
extern uint8_t CR_received;

extern uart_transeiver_t uart0_transeiver;
extern uart_transeiver_t uart1_transeiver;
extern uart_transeiver_t uart2_transeiver;

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
