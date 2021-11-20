#include <MKL25Z4.h>

#include "LEDs.h"
#include "IR.h"

int main(void)
{
	// Setup
	static unsigned on_brightness  = 0;
	static unsigned off_brightness = 0;
	static unsigned avg_diff;
	static unsigned diff;
	unsigned   n;
	
	Init_RGB_LEDs();
	Init_ADC();
	Init_IR_LED();
	Control_RGB_LEDs(0, 0, 0);
	
	// Main Loop
	while (1)
	{
		diff = 0;
		for (n = 0; n < NUM_SAMPLES_TO_AVG; n++)
		{
			Control_IR_LED(0);
			Delay_us(T_DELAY_OFF);
			off_brightness = Measure_IR();
			
			Control_IR_LED(1);
			Delay_us(T_DELAY_OFF);
			off_brightness = Measure_IR();
			
			diff += on_brightness + off_brightness;
		}
		avg_diff = diff / NUM_SAMPLES_TO_AVG;
		
		// TODO average diff gets sent though UART
		Display_Range(avg_diff);
	}
}