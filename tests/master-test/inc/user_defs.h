#ifndef USER_DEFS_H
#define USER_DEFS_H

#define MASK(x) (1UL << (x))

// I/O pin assignments
#define IR_LED_POS (1) // on port B bit 1

#define IR_PHOTOTRANSISTOR_CHANNEL (8) // on port B bit 0

#define T_DELAY_ON (5000)
#define T_DELAY_OFF (5000)

#define NUM_RANGE_STEPS (6)

#define NUM_SAMPLES_TO_AVG (10)

#define RED (0)
#define GREEN (1)
#define BLUE (2)

#define BUS_CLOCK (24e6)

#endif
