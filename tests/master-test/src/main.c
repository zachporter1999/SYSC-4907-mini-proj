#include <MKL25Z4.h>

#include "drivers/uart.h"
#include "delay.h"

// Controls for selecting which tests to run
#define TEST_UART 1
#define TEST_I2C  0
#define TEST_SPI  0

int main(void)
{
#if TEST_UART

	uart1_init(UART_BAUDRATE_300);
	//uart1_init(UART_BAUDRATE_9600);
	
	char msg[16];
	sprintf(msg, "a");
	
	for (;;)
	{
		uart1_send(msg);	
		//uart1_update();
		Delay(10);
	}
		

#endif

#if TEST_I2C


#endif

#if TEST_SPI


#endif
}
