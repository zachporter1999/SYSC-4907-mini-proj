#include <MKL25Z4.h>

#include "timers.h"

#define IR_SAMPLE_PERIOD 40000

int main(void)
{
	// Setup
	static unsigned avg_diff;

	// unsigned n;

	Init_RGB_LEDs();
	Init_IR_LED();
	Init_PIT(IR_SAMPLE_PERIOD);
	Init_ADC();
	Control_RGB_LEDs(0, 0, 0);
	j Start_PIT();

	// Main Loop
	while (1)
	{
		// average the differences of IR Readings
		if (n_IR_samples == 2 * NUM_SAMPLES_TO_AVG)
		{
			avg_diff = IR_diff / NUM_SAMPLES_TO_AVG;
			n_IR_samples = 0;

			Display_Range((int)avg_diff);
		}
	}
}
