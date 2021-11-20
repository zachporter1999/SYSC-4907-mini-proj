#ifndef IR_H
#define IR_H

#include "user_defs.h"
#include "LEDs.h"

int Threshold[NUM_RANGE_STEPS] = {34000, 27000, 20000, 14000, 8000, 0};

const int Colors[NUM_RANGE_STEPS][3] = {{ 1, 1, 1}, // white
																	{ 1, 0, 1}, // magenta
																	{ 1, 0, 0}, // red
																	{ 1, 1, 0}, // yellow
																	{ 0, 0, 1}, // blue
																	{ 0, 1, 0}};// green

void Init_ADC(void);
void Control_IR_LED(unsigned int led_on);
void Init_IR_LED(void);
unsigned Measure_IR(void);
void Display_Range(int b);
void Delay_us(volatile unsigned int time_del);

#endif

