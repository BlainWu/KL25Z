//===============================
//Author: Peilin Wu
//Data: 22/11/2020
//Descibtion: GPIO driver source file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================
#include "gpio.h"

void gpio_init(uint8_t port_group,uint8_t pin_num,uint8_t io){

	switch(port_group){	
		case 'A':
	  case 'a':
			SIM_SCGC5 |= SIM_SCGC5_PORTA(1);				//enable clock
			PORTA->PCR[pin_num] |= PORT_PCR_MUX(1);	//GPIO function
			if(io)																	//select input or output
				GPIOA_PDDR |= (1UL<<pin_num);
			else
				GPIOA_PDDR |= (0UL<<pin_num);
			break;
		
		case 'B':
	  case 'b':
			SIM_SCGC5 |= SIM_SCGC5_PORTB(1);
			PORTB->PCR[pin_num] |= PORT_PCR_MUX(1);
			if(io)
				GPIOB_PDDR |= (1UL<<pin_num);
			else
				GPIOB_PDDR |= (0UL<<pin_num);
			break;
		
		case 'C':
	  case 'c':
			SIM_SCGC5 |= SIM_SCGC5_PORTC(1);
			PORTC->PCR[pin_num] |= PORT_PCR_MUX(1);
			if(io)
				GPIOC_PDDR |= (1UL<<pin_num);
			else
				GPIOC_PDDR |= (0UL<<pin_num);
			break;
		
		case 'D':
	  case 'd':
			SIM_SCGC5 |= SIM_SCGC5_PORTD(1);
			PORTD->PCR[pin_num] |= PORT_PCR_MUX(1);
			if(io)
				GPIOD_PDDR |= (1UL<<pin_num);
			else
				GPIOD_PDDR |= (0UL<<pin_num);
			break;

		case 'E':
	  case 'e':
			SIM_SCGC5 |= SIM_SCGC5_PORTE(1);
			PORTE->PCR[pin_num] |= PORT_PCR_MUX(1);
			if(io)
				GPIOE_PDDR |= (1UL<<pin_num);
			else
				GPIOE_PDDR |= (0UL<<pin_num);
			break;
	}
}

void gpio_set(uint8_t port_group,uint8_t pin_num){
	switch(port_group){	
		case 'A':
	  case 'a':
		GPIOA_PSOR |= (1UL<<pin_num);		//set 1
			break;
		
		case 'B':
	  case 'b':
		GPIOB_PSOR |= (1UL<<pin_num);
			break;
		
		case 'C':
	  case 'c':
		GPIOC_PSOR |= (1UL<<pin_num);
			break;
		
		case 'D':
	  case 'd':
		GPIOD_PSOR |= (1UL<<pin_num);
			break;

		case 'E':
	  case 'e':
		GPIOE_PSOR |= (1UL<<pin_num);
			break;
	}
}

void gpio_clear(uint8_t port_group,uint8_t pin_num){
	switch(port_group){	
		case 'A':
	  case 'a':
		GPIOA_PCOR |= (1UL<<pin_num);		//set 0
			break;
		
		case 'B':
	  case 'b':
		GPIOB_PCOR |= (1UL<<pin_num);
			break;
		
		case 'C':
	  case 'c':
		GPIOC_PCOR |= (1UL<<pin_num);
			break;
		
		case 'D':
	  case 'd':
		GPIOD_PCOR |= (1UL<<pin_num);
			break;

		case 'E':
	  case 'e':
		GPIOE_PCOR |= (1UL<<pin_num);
			break;
	}
}

void gpio_revese(uint8_t port_group,uint8_t pin_num){
	switch(port_group){	
		case 'A':
	  case 'a':
		GPIOA_PTOR |= (1UL<<pin_num);		//set 0
			break;
		
		case 'B':
	  case 'b':
		GPIOB_PTOR |= (1UL<<pin_num);
			break;
		
		case 'C':
	  case 'c':
		GPIOC_PTOR |= (1UL<<pin_num);
			break;
		
		case 'D':
	  case 'd':
		GPIOD_PTOR |= (1UL<<pin_num);
			break;

		case 'E':
	  case 'e':
		GPIOE_PTOR |= (1UL<<pin_num);
			break;
	}
}
