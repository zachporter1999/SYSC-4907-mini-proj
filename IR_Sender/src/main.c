#include <MKL25Z4.h>
#include <stdio.h>
#include <math.h>
#include "LEDs.h"
#include "IR.h"
#include "uart.h"
#include "LCD_4bit.h"
#include "delay.h"

//#define UART_EN

#define IR_SAMPLE_PERIOD 40000
#define UART_BAUDRATE 300

volatile uart_transceiver_t uart1_transceiver;
volatile uart_transceiver_t uart2_transceiver;

int main(void)
{
	static unsigned on_brightness = 0, off_brightness = 0;
	static int avg_diff;
	static int diff;
	uint8_t lcd_row = 0;
	uint8_t lcd_col = 0;
	unsigned n;
	uint32_t received_data;

	Init_RGB_LEDs();
	Init_LCD();	
	Clear_LCD();
	Set_Cursor(0, 0);
	Control_RGB_LEDs(1,0,0);
	Print_LCD("BoardA Starting");
	Delay(10);
	
	
	//Init_UART1(UART_BAUDRATE, sizeof(uint16_t), &uart1_transceiver);
	Control_RGB_LEDs(1,1,0);
	Delay(50);

	
	Init_ADC();	
	Init_IR_LED();

	Clear_LCD();
	Set_Cursor(0, 1);
	Control_RGB_LEDs(0, 1, 0);
	Print_LCD("BoardA Ready.");
	Delay(10);
	
	
	
	__enable_irq();
	
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
		
		#ifdef UART_EN
		send_data(&uart1_transceiver, &avg_diff);

		
		get_data(&uart1_transceiver, &received_data);	

		char buff[4] = "<o>";
		switch(received_data)
		{
			case 1:
				lcd_row = (lcd_row + 1) % 3;
				break;
			case 2:
				lcd_row = (lcd_row - 1) % 3;
				break;
			case 3:
				lcd_col = (lcd_col + 1) % 16;
				break;
			case 4:
				lcd_col = (lcd_col - 1) % 16;
				break;
		}
		Clear_LCD();
		Set_Cursor(lcd_col, lcd_row);
		Print_LCD(buff);
		#endif
		Delay(100);
	}
}
