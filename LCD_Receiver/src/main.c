#include <MKL25Z4.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "delay.h"
#include "UART.h"

#define BUFF_SIZE (40)

extern uint8_t CR_received;

/*------------------------------------------------------------------------------
	Example for LCD interface
	*------------------------------------------------------------------------------*/
static void LCD_Example(void) {
	Init_LCD();
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("Hello, World!");
	Set_Cursor(0,1);
	Print_LCD("Ready to Begin");
	for(int i = 0; i < 1000; i++);
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD("helpppp");
	for(int i = 0; i < 1000; i++);
	
}
/*
static void LCD_UARTout(int i) {
	Clear_LCD();
	Set_Cursor(0,0);
	Print_LCD(intToString(i, ));
}
*/
/*
void reverse(char* s, int n) {
	char temp;
	for (int i = 0; i < n/2; i++) {
		temp = s[i];
		s[i] = s[n - i - 1];
		s[n - i - 1] = temp;
	}
	
}

int intToString(int input, char s[], int digits) {
	int i = 0;
	while (input) {
		s[i++] = (input % 10) + '0';
		input = input / 10;
	}
	
	while (input < digits) {
		s[i++] = '0';
	}
	reverse(s, i);
	s[i] = '\0';
	return i;
}


static void floatToString(float input, char* s, int dec) {
	int i = (int)input;
	float f = input - (float)i;
	int index = intToString(i, s, 0);
	if (dec != 0) {
		s[index] = '.';
		f = f * pow(10, dec);
		intToString((int)f, s + index + 1, dec);
	}
}
*/
/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	uint8_t c;//, i;
	//uint8_t buff[BUFF_SIZE];
	char* charVal;
	char tempVal;
	
	Init_UART1(9600);
	
	int welcomeDelay = 100;

	LCD_Example();
	while (welcomeDelay > 0) welcomeDelay--;
	
	__enable_irq();
	
	while (1) {
		//i = 0;
		//buff[i] = '\0';
		//do {
			while (Get_Num_Rx_Chars_Available() == 0);
			c = Get_Char();
			/*
			buff[i++] = c;
			buff[i] = '\0';
			*/
		tempVal = c+'0';
		charVal = &tempVal;
			Clear_LCD();
			Set_Cursor(0,0);
			Print_LCD(charVal);
		//} while (i<BUFF_SIZE);
	}
	
	
	
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
