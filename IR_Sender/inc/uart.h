#ifndef UART_H
#define UART_H

#include <MKL25Z4.h>

#include "user_defs.h"

void Init_uart(void);

// Use Polling
void uart_send(uint8_t data);
uint8_t uart_receive(void);

#endif
