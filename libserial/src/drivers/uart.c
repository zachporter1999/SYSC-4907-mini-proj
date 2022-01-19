#include "drivers/uart.h"
#include <stdint.h>

#define UART_OVERSAMPLE (16)
#define BUS_CLOCK 		(24e6)

/*
 * Config data for uart Transceiver
 *
 * Elements:
 * - TxQ            : The transmission queue.
 * - RxQ            : The receiption queue.
*/
typedef struct
{
	Q_T TxQ;
	Q_T RxQ;
	
	volatile uint8_t txFlag;
	volatile uint8_t rxFlag;	
} uart_transceiver_t;

typedef struct
{
	unsigned int uartSCGCMask;
	UART_Type* uartPort;
	
	unsigned pinSCGCMask;
	PORT_Type* gpioPort;
	uint8_t  pcrMux;
	unsigned txPin;
	unsigned rxPin;
	
	unsigned nvic_irq;
	unsigned priority;
} uart_cfg_t;

static uart_cfg_t uart1_cfg = {
	.uartSCGCMask = SIM_SCGC4_UART1_MASK,
	.uartPort = UART1,
	.pinSCGCMask = SIM_SCGC5_PORTE_MASK,
	.gpioPort = PORTE,
	.pcrMux = 3,
	.txPin = 0,
	.rxPin = 1,
	.nvic_irq = UART1_IRQn,
	.priority = 128
};

static uart_cfg_t uart2_cfg = {
	.uartSCGCMask = SIM_SCGC4_UART2_MASK,
	.uartPort = UART2,
	.pinSCGCMask = SIM_SCGC5_PORTE_MASK,
	.gpioPort = PORTE,
	.pcrMux = 4,
	.txPin = 22,
	.rxPin = 23,
	.nvic_irq = UART2_IRQn,
	.priority = 128
};

// Preconfigured settings for uart 1 and uart 2 devices
static uart_transceiver_t uart1_transceiver = {
	.txFlag = 0,
	.rxFlag = 0
};

static uart_transceiver_t uart2_transceiver = {
	.txFlag = 0,
	.rxFlag = 0
};

// Generic uart init function
static void __uart_init(
	uart_cfg_t* p_cfg, 
	uart_transceiver_t *p_transceiver, 
	uint32_t baud_rate)
{	
	uint32_t divisor;
	
	Q_Init(&p_transceiver->TxQ);
	Q_Init(&p_transceiver->RxQ);

	// enable clock to UART and Port E
	SIM->SCGC4 |= p_cfg->uartSCGCMask;
	SIM->SCGC5 |= p_cfg->pinSCGCMask;


	// select UART pins
	p_cfg->gpioPort->PCR[p_cfg->txPin] = PORT_PCR_MUX(p_cfg->pcrMux);
	p_cfg->gpioPort->PCR[p_cfg->rxPin] = PORT_PCR_MUX(p_cfg->pcrMux);
	
	p_cfg->uartPort->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
		
	// Set baud rate to baud rate
	divisor = (uint32_t)BUS_CLOCK/(baud_rate*16);
	p_cfg->uartPort->BDH = UART_BDH_SBR(divisor>>8);
	p_cfg->uartPort->BDL = UART_BDL_SBR(divisor);
	
	// No parity, 9 bits, two stop bits, other settings;
	p_cfg->uartPort->C1 = UART_C1_M_MASK | UART_C1_PE_MASK | UART_C1_PT_MASK; 
	p_cfg->uartPort->S2 = 0;
	p_cfg->uartPort->C3 = 0;
	
    // Enable transmitter and receiver but not interrupts
	p_cfg->uartPort->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;
	
	NVIC_SetPriority(p_cfg->nvic_irq, p_cfg->priority); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(p_cfg->nvic_irq); 
	NVIC_EnableIRQ(p_cfg->nvic_irq);

	p_cfg->uartPort->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK;
}
	
/*
 * Send message to uart transmit queue
 *
 * args:
 * 	*transceiver  ---- Structure containing the config for the uart device
 * 	*send_msg     ---- cstring to be sent via UART
 */
static void __uart_send(uart_transceiver_t *transceiver, char* send_msg)
{
	for (char* curr_char = send_msg;
		 *curr_char != NULL;
		 curr_char++)
	{
		// Wait while Queue is full.
		while(Q_Full(&transceiver->TxQ));
		Q_Enqueue(&transceiver->TxQ, (uint8_t)*curr_char);
	}
	Q_Enqueue(&transceiver->TxQ, (uint8_t)NULL);
	
	
	// Start transmitter if it isn't already running
	if (!(UART1->C2 & UART_C2_TIE_MASK)) {
		UART1->C2 |= UART_C2_TIE_MASK;
	}
}

/*
 * Read message from uart receive queue.
 *
 * args:
 * 	*transceiver  ---- Structure containing the config for the uart device
 * 	*send_msg     ---- cstring to be sent via UART
 */
static void __uart_read(uart_transceiver_t* transceiver, char* received_msg)
{
	for (char new_char = (char)Q_Dequeue(&transceiver->RxQ);
		new_char != NULL;
		new_char = (char)Q_Dequeue(&transceiver->RxQ))
	{
		// Wait while Queue is empty.
		while (Q_Empty(&transceiver->RxQ));
		*received_msg++ = new_char;
	}
	*received_msg = (char)NULL;
}

static uint32_t Get_Num_Rx_Chars_Available(uart_transceiver_t *transceiver) {
	return Q_Size(&transceiver->RxQ);
}

// Wrapper functions to make for a more intuitive interface.
void uart1_init(unsigned baud_rate)
{
	__uart_init(
		&uart1_cfg, 
		&uart1_transceiver, 
		baud_rate
	);
}

void uart2_init(unsigned baud_rate)
{
	__uart_init(
		&uart2_cfg, 
		&uart2_transceiver, 
		baud_rate
	);
}

void uart1_send(char* msg)
{
	__uart_send(&uart1_transceiver, msg);
}

void uart2_send(char* msg)
{
	__uart_send(&uart2_transceiver, msg);
}

void uart1_read(char* msg)
{
	__uart_read(&uart1_transceiver, msg);
}

void uart2_read(char* msg)
{
	__uart_read(&uart2_transceiver, msg);
}

#if 1

// NOTE Rewritting irq to allow for passing of transceiver_t.
// NOTE Implementing observer pattern

void UART1_IRQHandler(void) {
	uint8_t c;
	NVIC_ClearPendingIRQ(UART1_IRQn);
	if (UART1->S1 & UART_S1_TDRE_MASK) {
		// can send another character
		if (!Q_Empty(&uart1_transceiver.TxQ)) {
			UART1->D = Q_Dequeue(&uart1_transceiver.TxQ);
		} else {
			// queue is empty so disable transmitter
			UART1->C2 &= ~UART_C2_TIE_MASK;
		}
	}
	if (UART1->S1 & UART_S1_RDRF_MASK) {
		// received a character
		if (!Q_Full(&uart1_transceiver.RxQ)) {
			c = UART1->D;
			Q_Enqueue(&uart1_transceiver.RxQ, c);
			if (c == '\r') {
				//CR_received++;
			}
		} else {
			// error - queue full.
			while (1)
				;
		}
	}
	if (UART1->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | 
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// handle the error
			// clear the flag
			/*
			UART1->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | 
				UART_S1_FE_MASK | UART_S1_PF_MASK;
		 */
		}
}

void UART2_IRQHandler(void) {
	uint8_t c;
	NVIC_ClearPendingIRQ(UART2_IRQn);
	if (UART2->S1 & UART_S1_TDRE_MASK) {
		// can send another character
		if (!Q_Empty(&uart2_transceiver.TxQ)) {
			UART2->D = Q_Dequeue(&uart2_transceiver.TxQ);
		} else {
			// queue is empty so disable transmitter
			UART2->C2 &= ~UART_C2_TIE_MASK;
		}
	}
	if (UART2->S1 & UART_S1_RDRF_MASK) {
		// received a character
		if (!Q_Full(&uart2_transceiver.RxQ)) {
			c = UART2->D;
			Q_Enqueue(&uart2_transceiver.RxQ, c);
			if (c == '\r') {
				//CR_received++;
			}
		} else {
			// error - queue full.
			while (1)
				;
		}
	}
	if (UART2->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | 
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// handle the error
			// clear the flag
			/*
			UART2->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | 
				UART_S1_FE_MASK | UART_S1_PF_MASK;
		 */
		}
}
#else
void UART1_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART1_IRQn);
	if (UART1->S1 & UART_S1_TDRE_MASK) {
		uart1_transceiver.txFlag = 1;
		uart1_cfg.uartPort->C2 &= ~UART_C2_TIE_MASK;
	}
	if (UART1->S1 & UART_S1_RDRF_MASK) {
		uart1_transceiver.rxFlag = 1;
		uart1_cfg.uartPort->C2 &= ~UART_C2_RIE_MASK;
	}
	if (UART1->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | 
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// handle the error
			// clear the flag
			/*
			UART1->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | 
				UART_S1_FE_MASK | UART_S1_PF_MASK;
			*/
		}
}

void UART2_IRQHandler(void) {
	NVIC_ClearPendingIRQ(UART2_IRQn);
	if (UART2->S1 & UART_S1_TDRE_MASK) {
		uart2_transceiver.txFlag = 1;
		uart2_cfg.uartPort->C2 &= ~UART_C2_TIE_MASK;
	}
	if (UART2->S1 & UART_S1_RDRF_MASK) {
		uart2_transceiver.rxFlag = 1;
		uart1_cfg.uartPort->C2 |= UART_C2_RIE_MASK;
	}
	if (UART2->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK | 
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// handle the error
			// clear the flag
			/*
			UART2->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | 
				UART_S1_FE_MASK | UART_S1_PF_MASK;
			*/
		}
}

static void __uart_send_receive(uart_transceiver_t *p_transceiver)
{
	uint8_t c;
	if (uart1_transceiver.txFlag)
	{
		// Dequeue from tx queue and send
		// can send another character
		if (!Q_Empty(&uart1_transceiver.TxQ)) {
			UART1->D = Q_Dequeue(&uart1_transceiver.TxQ);
		} else {
			// queue is empty so disable transmitter
			UART1->C2 &= ~UART_C2_TIE_MASK;
		}
		uart1_cfg.uartPort->C2 |= UART_C2_TIE_MASK;
	}
	
	if (uart1_transceiver.rxFlag)
	{
		// Enqueue to rx queue
		// received a character
		if (!Q_Full(&p_transceiver->RxQ)) {
			c = UART1->D;
			Q_Enqueue(&p_transceiver->RxQ, c);
			//if (c == '\r') {
			//	CR_received++;
			//}
		} else {
			// error - queue full.
			while (1)
				;
		}
	}
}

void uart1_update()
{
	__uart_send_receive(&uart1_transceiver);
}
#endif
