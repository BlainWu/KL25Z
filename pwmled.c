//===============================
//Author: Peilin Wu
//Data: 23/11/2020
//Descibtion: PWM-LED module source file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================
#include "pwmled.h"
#define MOD_VALUE 19999

void pwmled_init(){
	SIM_SCGC5 |= SIM_SCGC5_PORTB(1) + SIM_SCGC5_PORTD(1);	//enble portB portD
	SIM_SCGC6 |= SIM_SCGC6_TPM0(1) + SIM_SCGC6_TPM2(1);		//enable TPM0 TPM2
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);											//Set MCGFLLCLK as TPM clock, 20.97Mhz
	
	PORTD_PCR1 |= PORT_PCR_MUX(4);												//set PORTD_1 I/O as TPM0_CH0
	PORTB_PCR18 |=PORT_PCR_MUX(3);												//set PORTB_18 I/0 as TPM2_CH0
	PORTB_PCR19 |=PORT_PCR_MUX(3);												//set PORTB_19 I/0 as TPM2_CH1
	
	//set as High-Ture pulses;Edge-aligned PWM
	//Blue
	TPM0_SC = 0;
	TPM0->CONTROLS[1].CnSC = 0x24;
	TPM0->MOD = MOD_VALUE;
	TPM0->CONTROLS[1].CnV = 1;
	TPM0_SC = 0x08;

	//Red Green
	TPM2->SC = 0;
	TPM2->CONTROLS[0].CnSC = 0x24;
	TPM2->CONTROLS[1].CnSC = 0x24;
	TPM2->MOD = MOD_VALUE;
	TPM2->CONTROLS[0].CnV = 1;
	TPM2->CONTROLS[1].CnV = 1;
	TPM2->SC = 0x08;
}

void pwmled_set(short duty_cycle,uint8_t colour){
	uint16_t CnV_VALUE = duty_cycle * (MOD_VALUE+1) * 0.01;
	switch(colour){
		case 'R':
		case 'r':
			TPM2->CONTROLS[0].CnV = CnV_VALUE;
			break;
		
		case 'G':
		case 'g':
			TPM2->CONTROLS[1].CnV = CnV_VALUE;
			break;
		
		case 'B':
		case 'b':
			TPM0->CONTROLS[1].CnV = CnV_VALUE;
			break;
	}
}

void pwmled_update(short X, short Y, short Z){
	pwmled_set(X,'r');
	pwmled_set(Y,'g');
	pwmled_set(Z,'b');
}
