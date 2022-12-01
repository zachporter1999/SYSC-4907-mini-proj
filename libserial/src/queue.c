#include "queue.h"

#if defined(EN_Q_DBG_LED) && EN_Q_DBG_LED
/**
 * Enables RBG LED for debugging UART Queue, and ISR.
 */
static void init_Q_debug_led(void) {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	PORTB->PCR[18] = (uint32_t)PORT_PCR_MUX(1);
	PORTB->PCR[19] = (uint32_t)PORT_PCR_MUX(1);
	PORTD->PCR[1]  = (uint32_t)PORT_PCR_MUX(1);
	
	PTB->PDDR |= (uint32_t)((1 << 18) | (1 << 19));
	PTD->PDDR |= (uint32_t) (1 << 1);
	
	PTB->PSOR |= (uint32_t)((1 << 18) | (1 << 19));
	PTD->PSOR |= (uint32_t) (1 << 1);
}

/**
 * Enables RBG LED for debugging UART Queue, and ISR.
 */
static void set_Q_debug_led(uint8_t r, uint8_t g, uint8_t b) {
	if (r) PTB->PCOR |= (uint32_t)(1 << 18);
	else   PTB->PSOR |= (uint32_t)(1 << 18);
	
	if (g) PTB->PCOR |= (uint32_t)(1 << 19); 
	else   PTB->PSOR |= (uint32_t)(1 << 19);
	
	if (b) PTD->PCOR |= (uint32_t)(1 << 1); 
	else   PTD->PSOR |= (uint32_t)(1 << 1);
	
	Delay(25);
	PTB->PSOR |= (uint32_t)((1 << 18) | (1 << 19));
	PTD->PSOR |= (uint32_t) (1 << 1);
}
#endif

int Q_Empty(Q_T * q) {
#if defined(EN_Q_DBG_LED) && EN_Q_DBG_LED
	set_Q_debug_led(0, 1, 0); // Green on empty
#endif
  return q->Size == 0;
}

int Q_Full(Q_T * q) {
#if defined(EN_Q_DBG_LED) && EN_Q_DBG_LED
	set_Q_debug_led(1, 0, 0); // Red on empty
#endif
  return q->Size == Q_SIZE;
}

unsigned int Q_Size(Q_T * q) {
	return q->Size;
}


int Q_Enqueue(Q_T * q, uint8_t d) {
  // if queue is full, abort rather than overwrite and return
  // an error code
  if (!Q_Full(q)) {
    q->Data[q->Tail++] = d;
    q->Tail %= Q_SIZE;
    q->Size++;
#if defined(EN_Q_DBG_LED) && EN_Q_DBG_LED
		set_Q_debug_led(0, 0, 1); // Blue on EnQ
#endif
    return 1; // success
  } else 
    return 0; // failure
}

uint8_t Q_Dequeue(Q_T * q) {
  // Must check to see if queue is empty before dequeueing
  uint8_t t=0;
  if (!Q_Empty(q)) {
    t = q->Data[q->Head];
    q->Data[q->Head++] = 0; // empty unused entries for debugging
    q->Head %= Q_SIZE;
    q->Size--;
#if defined(EN_Q_DBG_LED) && EN_Q_DBG_LED
		set_Q_debug_led(1, 0, 1); // Purple on DeQ
#endif
  }
  return t;
}


void Q_Init(Q_T * q) {
  unsigned int i;
	init_Q_debug_led();
  for (i=0; i<Q_SIZE; i++)  
    q->Data[i] = 0;  // to simplify our lives when debugging
  q->Head = 0;
  q->Tail = 0;
  q->Size = 0;
}
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
