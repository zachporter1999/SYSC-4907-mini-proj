#include <MKL25Z4.h>
#include "LEDs.h"
#include "IR.h"
#include "uart.h"

#define IR_SAMPLE_PERIOD 40000

int main(void)
{
	static unsigned on_brightness = 0, off_brightness = 0;
	static int avg_diff;
	static int diff;
	unsigned n;

	Init_ADC();
	Init_uart();
	Init_RGB_LEDs();
	Init_IR_LED();
	Control_RGB_LEDs(0, 0, 0);

	while (1)
	{
		diff = 0;
		for (n = 0; n < NUM_SAMPLES_TO_AVG; n++)
		{
			// measure IR level with IRLED off
			Control_IR_LED(0);
			Delay_us(T_DELAY_OFF);
			off_brightness = Measure_IR();

			// measure IR level with IRLED on
			Control_IR_LED(1);
			Delay_us(T_DELAY_ON);
			on_brightness = Measure_IR();

			// calculate difference
			diff += on_brightness - off_brightness;
		}
		avg_diff = diff / NUM_SAMPLES_TO_AVG;

		// light RGB LED according to range
		Display_Range(avg_diff);
		
		uart_send((uint8_t)1);
	}
}
