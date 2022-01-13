#include <MKL25Z4.h>

#include "drivers/uart.h"

// Controls for selecting which tests to run
#define TEST_UART 1
#define TEST_I2C  0
#define TEST_SPI  0

int main(void)
{
#if TEST_UART

	uart_transceiver_t uart1_transeiver = Init_UART1(9600, sizeof(uint8_t));
	uart_transceiver_t uart2_transeiver = Init_UART2(115200, sizeof(uint8_t));

#endif

#if TEST_I2C


#endif

#if TEST_SPI


#endif
}
