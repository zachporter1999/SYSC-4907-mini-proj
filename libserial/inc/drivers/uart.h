#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>
#include "queue.h"

// TODO Allow users to define the baud rate.
// TODO Or have preset macros
#define UART_BAUDRATE_300    300
#define UART_BAUDRATE_9600   9600
#define UART_BAUDRATE_115200 115200

void uart1_init(unsigned baud_rate);
void uart1_start(void);
void uart1_stop(void);
void uart1_send(char* msg);
void uart1_read(char* msg);
//void uart1_update(void);

void uart2_init(unsigned baud_rate);
void uart2_start(void);
void uart2_stop(void);
void uart2_send(char* msg);
void uart2_read(char* msg);

#endif
