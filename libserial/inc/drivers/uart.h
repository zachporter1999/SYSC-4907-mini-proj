#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>
#include "queue.h"

// TODO Allow users to define the baud rate.
// TODO Or have preset macros
#define UART_BAUDRATE 300

#define UART_OVERSAMPLE (16)
#define BUS_CLOCK 		(24e6)

// NOTE this is from the old way of sending. May go back to that.
extern uint8_t CR_received;

/*
 * Config data for uart Transceiver
 *
 * Elements:
 * - bytes_per_data : The number of bytes per message to send.
 * - TxQ            : The transmission queue.
 * - RxQ            : The receiption queue.
*/
typedef struct
{
	// TODO Review how data is transmitted, may be able to remove bytes_per_data
	size_t bytes_per_data;
	volatile Q_T TxQ;
	volatile Q_T RxQ;
} uart_transceiver_t;

/*
 * Initialization of UART ports 1 and 2.
 * TODO Implement UART 0
 * TODO INIT has smelly code. How to cleanup?
 *      - PORT PCR, NVIC IRQn, NVIC Priority Vary for different UART
 *
 * Args:
 * - baud_rate   : The baud rate the uart port sends/receives at.
 * - data_bytes  : The number of bits to send/receive per message.
 *
 * Return:
 * - The config structure for the uart port.
*/
uart_transceiver_t Init_UART1(uint32_t baud_rate, size_t data_bytes);
uart_transceiver_t Init_UART2(uint32_t baud_rate, size_t data_bytes);

/*
 * Send data to transmission queue
 *
 * Args:
 * - transceiver : The config structure for the uart port.
 * - data        : The data to be sent.
*/
void send_data(uart_transceiver_t *transeiver, void* data);

/*
 * Read data from receive queue
 *
 * Args:
 * - transceiver : The config structure for the uart port.
 *
 * Return:
 * - The data read from the queue
*/
uint32_t get_data(uart_transceiver_t* transeiver);

/*
 * Gets the size of the receive queue
 *
 * Return:
 * - The number of bytes stored in the queue
*/
uint32_t Get_Num_Rx_Chars_Available(uart_transceiver_t *transceiver);

#endif
