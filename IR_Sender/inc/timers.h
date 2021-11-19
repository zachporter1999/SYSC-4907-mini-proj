#ifndef TIMERS_H
#define TIMERS_H
#include <MKL25Z4.h>
#include "IR.h"

#define LCD_UPDATE_PERIOD (100)

void Init_PIT(unsigned period);
void Start_PIT(void);
void Stop_PIT(void);

void Init_PWM(void);

extern volatile unsigned PIT_IR_sample_count;
extern volatile unsigned IR_brightness;
extern volatile unsigned IR_diff;
extern volatile unsigned n_IR_samples;
extern volatile unsigned IR_led_state;

#endif
