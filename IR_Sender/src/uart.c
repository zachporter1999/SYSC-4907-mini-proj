#include "uart.h"

#define USE_UART1 1

#if USE_UART1

#define UART_PORT UART1
#define TX_PIN 0
#define RX_PIN 1

#define TX_MUX 3
#define RX_MUX 3

#define UART_CLOCK_MASK SIM_SCGC4_UART1_MASK

#else

#define UART_PORT UART2

#define TX_PIN 22S
#define RX_PIN 23

#define TX_MUX 4
#define RX_MUX 4

#define UART_CLOCK_MASK SIM_SCGC4_UART2_MASK

#endif

#define BAUD_RATE 9600

void Init_uart()
{
	uint32_t divisor;
	
	// Set System Clock for UART0 and GPIO pins
	SIM->SCGC4 = UART_CLOCK_MASK;
	SIM->SCGC5 = SIM_SCGC5_PORTE_MASK;

	PORTE->PCR[TX_PIN] =  PORT_PCR_MUX(TX_MUX);
	PORTE->PCR[RX_PIN] =  PORT_PCR_MUX(RX_MUX);
	
	PTE->PDDR |= MASK(TX_PIN);
	
	UART_PORT->C2 &= ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
	
	// UART0 Config
	divisor = (uint32_t)(BUS_CLOCK / (BAUD_RATE * 16));	
	UART_PORT->BDH = (uint8_t)(divisor >> 8);
	UART_PORT->BDL = (uint8_t)divisor;
	
	// Set normal operation mode
	UART_PORT->C1 = 0;
	UART_PORT->C2 = 0;
	UART_PORT->C3 = 0;
	
	// enable transmit and receive
	UART_PORT->C2 = UARTLP_C2_TE_MASK;
}

void uart_send(uint8_t data)
{
	while(!(UART_PORT->S1 & UARTLP_S1_TDRE_MASK));
	UART_PORT->D = data;
}

uint8_t uart_receive(void)
{
	while(!(UART_PORT->S1 & UARTLP_S1_RDRF_MASK));
	return UART_PORT->D;
}
