#include <MKL25Z4.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "delay.h"
#include "UART.h"

#define BUFF_SIZE (16)

extern uint8_t CR_received;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	uint16_t i;
	/*
	//polling approach
	char bugger[16];
	*/
	
	//interrupt approach
	char buff[BUFF_SIZE];
	__enable_irq();
	
	Init_UART1(300);
	Init_LCD();
	
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
			i |= (uint16_t)(Get_Char() << 8);
			i |= (uint8_t)Get_Char();
			sprintf(buff, "IR: %u", i);
			Clear_LCD();
			Set_Cursor(0,0);
			Print_LCD(buff);
			Set_Cursor(0,1);
			Print_LCD("Interrupt");
			Delay(20);
		}
		
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
