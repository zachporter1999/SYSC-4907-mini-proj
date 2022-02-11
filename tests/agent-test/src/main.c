#include <MKL25Z4.h>

#include "drivers/uart.h"
#include "delay.h"
#include "lcd_4bit.h"

// Controls for selecting which tests to run
#define TEST_UART 1
#define TEST_I2C  0
#define TEST_SPI  0

int main(void)
{
#if TEST_UART

	UART1_INIT(666, 128);
	Init_LCD();
	
	char uart_msg[4];
	char lcd_msg[16];
	
	for (;;)
	{
		Set_Cursor(0, 0);
		Clear_LCD();
		UART1_READ(uart_msg);
		
		sprintf(lcd_msg, "Received: %s", uart_msg);
		
		Print_LCD(lcd_msg);
		Delay(25);
	}

#endif

#if TEST_I2C


#endif

#if TEST_SPI


#endif
}
