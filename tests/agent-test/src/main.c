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

	UART1_INIT(9600, 128);
	char msg[16];
	
	for (;;)
	{
		UART1_READ(msg);
		
		Delay(25);
	}

#endif

#if TEST_I2C


#endif

#if TEST_SPI


#endif
}
