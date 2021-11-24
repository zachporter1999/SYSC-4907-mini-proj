#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <MKL25Z4.H>
#include "queue.h"

#define USE_UART_INTERRUPTS (1)

#define UART_OVERSAMPLE (16)
#define BUS_CLOCK 			(24e6)
void UART0_Transmit_Poll(uint8_t data);
void Init_UART1(uint32_t baud_rate);
void UART1_Transmit_Poll(uint8_t data);
uint8_t UART1_Receive_Poll(void);
void Send_String(uint8_t * str);
uint32_t Get_Num_Rx_Chars_Available(void);
uint8_t	Get_Char(void);


extern Q_T Tx_Data, Rx_Data;

#endif
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
