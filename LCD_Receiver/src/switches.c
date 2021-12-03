#include <MKL25Z4.H>
#include "switches.h"
#include "gpio_defs.h"

void Init_5way_Switch(void) {
  SIM->SCGC5 |=  SIM_SCGC5_PORTE_MASK; /* enable clock for port E */
	
  /* Select GPIO and enable pull-up resistors for pins connected to switches */
  PORTE->PCR[SW_UP_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	
  PORTE->PCR[SW_DN_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	
  PORTE->PCR[SW_LT_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	
  PORTE->PCR[SW_RT_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	
  PORTE->PCR[SW_CR_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK;	
	
  /* Set port E bits 0-3, 7 to inputs */
  PTE->PDDR &= ~( MASK(SW_UP_POS) | 
				  MASK(SW_DN_POS) |
				  MASK(SW_LT_POS) | 
				  MASK(SW_RT_POS) |
				  MASK(SW_CR_POS) );
}

// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
