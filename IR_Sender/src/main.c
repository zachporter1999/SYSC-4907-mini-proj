#include <MKL25Z4.h>
#include <stdio.h>
#include "LEDs.h"
#include "IR.h"
#include "UART.h"
#include "LCD_4bit.h"
#include "delay.h"

#define IR_SAMPLE_PERIOD 40000
#define UART_BAUDRATE 300
#define LCD_EN

static void Delay(uint32_t dly)
{
	volatile uint32_t t;
	
	for (t=dly*10000; t>0; t--);
}

int main(void)
{
	static unsigned on_brightness = 0, off_brightness = 0;
	static int avg_diff;
	static int diff;
	unsigned n;
	// enable lcd module
	#ifdef UART_EN

	Init_LCD();	
	Clear_LCD();
	Set_Cursor(0, 0);
	Print_LCD("Hello World");

	#endif
	Init_ADC();
	Init_UART1(300);
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
		
		// uart_send((avg_diff >> 8) & 0xFF);
		#if 1
		
		Q_Enqueue(&TxQ, (uint8_t)(avg_diff >> 8));
		Q_Enqueue(&TxQ, (uint8_t)avg_diff);
		if (!(UART1->C2 & UART_C2_TIE_MASK)) {
			UART1->C2 |= UART_C2_TIE_MASK;
		}
		Delay(250);
		#else
		UART1_Transmit_Poll((uint8_t)(avg_diff >> 8));
		//Delay(100);
		UART1_Transmit_Poll((uint8_t)(avg_diff));
		Delay(50);
		#endif
	}
}
