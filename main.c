//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: KD6027 assignment project-Main function
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================

#include "pwmled.h"
#include "uart.h"
#include "i2c.h"
#include "MMA8451Q.H"
#include "gui.h"
#include <string.h>
#include <stdio.h>

extern short Xout_perc,Yout_perc,Zout_perc;
extern short Xout_g_int,Xout_g_dec1,Xout_g_dec2;
extern short Yout_g_int,Yout_g_dec1,Yout_g_dec2;
extern short Zout_g_int,Zout_g_dec1,Zout_g_dec2;
extern char Xout_g_S,Yout_g_S,Zout_g_S;
int data_ready = 0;
char buf[100];

void MCU_Init(void)
{
	uart0_init(57600);										//baud rate 57600
	GUI_init();
	pwmled_init();
	i2c_init();
	Acc_init();
	
	__disable_irq(); 											// Disable interrupt Globally 
	//Configure the PTA14 pin (connected to the INT1 of the MMA8451Q) for falling edge interrupts
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		// Turn on clock to Port A module 
	PORTA_PCR14 |= (0|PORT_PCR_ISF_MASK|	// Clear the interrupt flag 
					  PORT_PCR_MUX(0x1)|					// PTA14 is configured as GPIO 
					  PORT_PCR_IRQC(0xA));				// PTA14 is configured for falling edge interrupts 
	//Enable PORTA interrupt on NVIC
	int irq_num=PORTA_IRQn; 							// PortA Interrupt request number
	NVIC->ICPR[0] |= 1 << irq_num; 				// clear any pending interrupt of PORTA
  NVIC->ISER[0] |= 1 << irq_num; 				// enable PORTA interrupt
	NVIC_EnableIRQ(PORTA_IRQn);
	
	__enable_irq(); 											//Enable interrupt Globally
}


void PORTA_IRQHandler(){
	short X,Y,Z;
	readAccXYZ();
	X = Xout_perc,Y=Yout_perc,Z=Zout_perc;
	pwmled_update(X,Y,Z);
	PORTA_PCR14 |= PORT_PCR_ISF_MASK;
	data_ready=1;
}

int main(){
	MCU_Init();
	while(1){
		if(data_ready){
				GUI_update(Xout_perc,Yout_perc,Zout_perc,Xout_g_S,Xout_g_int,Xout_g_dec1,Xout_g_dec2,\
				Yout_g_S,Yout_g_int,Yout_g_dec1,Yout_g_dec2,Zout_g_S,Zout_g_int,Zout_g_dec1,Zout_g_dec2);
				data_ready=0;
		}
	}
}
