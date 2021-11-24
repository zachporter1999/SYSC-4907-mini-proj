#include "UART.h"

Q_T TxQ, RxQ;
uint8_t CR_received = 0;

void Init_UART1(uint32_t baud_rate) {
	uint32_t divisor;
	
	// enable clock to UART and Port E
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;


	// select UART pins
	PORTE->PCR[1] = PORT_PCR_MUX(3);
	PORTE->PCR[0] = PORT_PCR_MUX(3);
	
	UART1->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
		
	// Set baud rate to baud rate
	divisor = BUS_CLOCK/(baud_rate*16);
	UART1->BDH = UART_BDH_SBR(divisor>>8);
	UART1->BDL = UART_BDL_SBR(divisor);
	
	// No parity, 8 bits, two stop bits, other settings;
	UART1->C1 = 0; 
	UART1->S2 = 0;
	UART1->C3 = 0;
	
// Enable transmitter and receiver but not interrupts
	UART1->C2 = UART_C2_TE_MASK | UART_C2_RE_MASK;
	
#if USE_UART_INTERRUPTS
	NVIC_SetPriority(UART1_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(UART1_IRQn); 
	NVIC_EnableIRQ(UART1_IRQn);

//	UART2->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK;
	UART1->C2 |= UART_C2_RIE_MASK;
	Q_Init(&TxQ);
	Q_Init(&RxQ);
#endif

}

void UART1_Transmit_Poll(uint8_t data) {
		while (!(UART1->S1 & UART_S1_TDRE_MASK))
			;
		UART1->D = data;
}	

uint8_t UART1_Receive_Poll(void) {
		while (!(UART1->S1 & UART_S1_RDRF_MASK))
			;
		return UART1->D;
}	

void UART1_IRQHandler(void) {
	uint8_t c;
	NVIC_ClearPendingIRQ(UART1_IRQn);
	if (UART1->S1 & UART_S1_TDRE_MASK) {
		// can send another character
		if (!Q_Empty(&TxQ)) {
			UART1->D = Q_Dequeue(&TxQ);
		} else {
			// queue is empty so disable transmitter
			UART1->C2 &= ~UART_C2_TIE_MASK;
		}
	}
	if (UART1->S1 & UART_S1_RDRF_MASK) {
		// received a character
		if (!Q_Full(&RxQ)) {
			c = UART1->D;
			Q_Enqueue(&RxQ, c);
			if (c == '\r') {
				CR_received++;
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
			UART2->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | 
				UART_S1_FE_MASK | UART_S1_PF_MASK;
			*/
		}
}

void Send_String(uint8_t * str) {
	// enqueue string
	while (*str != '\0') { // copy characters up to null terminator
		while (Q_Full(&TxQ))
			; // wait for space to open up
		Q_Enqueue(&TxQ, *str);
		str++;
	}
	// start transmitter if it isn't already running
	if (!(UART1->C2 & UART_C2_TIE_MASK)) {
		UART1->C2 |= UART_C2_TIE_MASK;
	}
}

uint32_t Get_Num_Rx_Chars_Available(void) {
	return Q_Size(&RxQ);
}
uint8_t	Get_Char(void) {
	return Q_Dequeue(&RxQ);
}
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
