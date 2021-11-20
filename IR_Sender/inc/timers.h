#ifndef TIMERS_H
#define TIMERS_H
#include <MKL25Z4.h>
#include "IR.h"

#define LCD_UPDATE_PERIOD (100)

void Init_PIT(unsigned period);
void Start_PIT(void);
void Stop_PIT(void);

void Init_PWM(void);
<<<<<<< HEAD
void Set_PWM_Values(uint16_t perc1, uint16_t perc2);

extern volatile unsigned PIT_interrupt_counter;
extern volatile unsigned LCD_update_requested;

#endif
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************
== == == =

             extern volatile unsigned PIT_IR_sample_count;
extern volatile unsigned IR_brightness;
extern volatile unsigned IR_diff;
extern volatile unsigned n_IR_samples;
extern volatile unsigned IR_led_state;

#endif
>>>>>>> fd41189917ce25adcab425dcb8e70f792f7fe5a7
