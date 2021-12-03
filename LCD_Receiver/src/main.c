#include <MKL25Z4.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "delay.h"
#include "uart.h"
#include "switches.h"

#define BUFF_SIZE (16)

extern uint8_t CR_received;
extern volatile unsigned send_button;
#define UART_BAUDRATE 300

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	uint16_t i;
	
	#ifdef UART_EN
	uart1_transceiver = Init_UART1(UART_BAUDRATE, sizeof(uint16_t));
	#endif
	
	/*
	//polling approach
	char bugger[16];
	*/
	
	//interrupt approach
	char buff[BUFF_SIZE];
	__enable_irq();
	
	Init_4way_Switch();
	
	Init_UART1(300);
	Init_LCD();
	Set_Cursor(0,0);
	Print_LCD("bruh");
	
	while(1) {
		/*
		//polling approach
		i = 0;
		i |= (uint16_t)(UART1_Receive_Poll() << 8);
		i |= (uint8_t)UART1_Receive_Poll();
		sprintf(bugger, "IR: %u", i);
		Clear_LCD();
		Set_Cursor(0,0);
		Print_LCD(bugger);
		Set_Cursor(0,1);
		Print_LCD("Polling);
		Delay(10);
		*/
		
		//interrupt approach
		if (Get_Num_Rx_Chars_Available() >= 2) {
			i = 0;
			i = get_data(&uart1_transceiver);
			/*
			i |= (uint16_t)(get_data(&uart1_transceiver) << 8);
			i |= (uint8_t)get_data(&uart1_transceiver);
			*/
			sprintf(buff, "IR: %u", i);
			Clear_LCD();
			Set_Cursor(0,0);
			Print_LCD(buff);
			Set_Cursor(0,1);
			Print_LCD("Interrupt");
			Delay(20);
		}
		
		send_data(&uart1_transceiver, &send_button);
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
