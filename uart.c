//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: UART driver source file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================

# include "uart.h"


void uart_init(uint8_t UART_No,uint16_t baud_rate){
	
	if(UART_No < 0 || UART_No > 2){
		return;																	//Check the port number
	}
	
	//UART0
	if(UART_No == 0 ){

		SIM_SOPT2 |= SIM_SOPT2_UART0SRC(0x01);	//Set MCGFLLCLK as clock, 20.97Mhz
		SIM_SCGC4 |= SIM_SCGC4_UART0(0x1);			//Enable UART0 clock
		SIM_SCGC5 |= SIM_SCGC5_PORTA(0x1);
		
		PORTA_PCR1 |= PORT_PCR_MUX(0x02);
		PORTA_PCR2 |= PORT_PCR_MUX(0x02);				//Make PTA1->RX PTA2->TX ;
		
		UART0->C2 = 0; 													//Turn off uart0 before config
		
		uint16_t sbr = 20970000/(16 * baud_rate);//Calculate SBR
		UART0_BDH |= UART0_BDH_LBKDIE(0x0);
		UART0_BDH |= UART0_BDH_RXEDGIE(0x0);
		UART0_BDH |= UART0_BDH_SBNS(0x0);
		UART0_BDH |= (UART0_BDH_SBR_MASK & (sbr>>8));
		UART0_BDL = (uint8_t)(sbr & UART0_BDL_SBR_MASK); //Set Baud rate
		
		UART0_C1 = 0x00; 													//8-bit ,noparity
		UART0_C4 |= UART0_C4_OSR(0xF);						//over-sampling-ratio = 16
		UART0_C2 |= UART0_C2_TE(0x01);						//Transmit enable
		UART0_C2 |= UART0_C2_RE(0x01);						//Receiver enable
	}
}

