#ifndef QUEUE_H
#define QUEUE_H

/**
 * Debug LED Summary
 * =================
 * 
 * - Queue Full  = Red
 * - Queue Empty = Green
 * - Enqueue     = Blue
 * - Dequeue     = Purple
 */

#define EN_Q_DBG_LED 1

#if defined(EN_Q_DBG_LED) && EN_Q_DBG_LED
#include <MKL25Z4.h>
#else
#include <stdint.h>
#endif

#define Q_SIZE (256)

typedef struct {
  unsigned char Data[Q_SIZE];
  unsigned int Head; // points to oldest data element 
  unsigned int Tail; // points to next free space
  unsigned int Size; // quantity of elements in queue
} Q_T;


unsigned int Q_Size(Q_T * q);
int Q_Empty(Q_T * q);
int Q_Full(Q_T * q);
int Q_Enqueue(Q_T * q, uint8_t d);
uint8_t Q_Dequeue(Q_T * q);
void Q_Init(Q_T * q);

#endif // QUEUE_H
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
