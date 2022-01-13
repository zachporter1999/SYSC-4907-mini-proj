#include <MKL25Z4.h>

#include "drivers/uart.h"

int main(void)
{
	Init_UART1(9600, sizeof(uint8_t), NULL);
}
