//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: KD6027 assignment project
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================

/*

#include "uart.h"
#include <string.h>
int main(){

	uart0_init(9600);
	
	char msg[] = "Enter one number each time !!!\r\n";
	uart0_sent_string(msg);
	
	int flag =0,red=0,green=0,blue = 0,value=0;
	
	while(1){
	
		char str[100];
		if(uart0_reci_str(str)){							//recived a string
			
			for (int i=0;	i<strlen(str);	i++)
				value = value*10 + (str[i]-'0');
			
			switch(flag){
				case 0:
					red = value;
					uart0_sent_string("The red value is:");
					break;
				case 1:
					green = value;
					uart0_sent_string("The green value is:");
					break;
				case 2:
					blue = value;
					uart0_sent_string("The blue value is:");
					break;
				default:
					flag = 0;
			}
			uart0_sent_string(str);
			uart0_sent_string("\r\n");
			
			memset(str,0,strlen(str));					//clear the string
			flag ++;
		}
		
	}
	return 0;
}
	
*/


/*
#include<MKL25Z4.H>
int main(){

	SIM_SCGC5 |= 0x1000;
	PORTD_PCR1 = 0x0400;
	SIM_SCGC6 |= 0x01000000;
	SIM_SOPT2 |= 0x01000000;
	TPM0_SC = 0;
	TPM0->CONTROLS[1].CnSC = 0x20 | 0x08;
	TPM0->MOD = 45770;
	TPM0->CONTROLS[1].CnV = 104;
	TPM0->SC = 0x0B;
	while(1){
	}

}
*/
 /*
#include "pwmled.h"
void delay(int n);

int main(){
	pwmled_init();
	uint16_t con = 0;
	while(1){
		delay(5000000);
		pwmled_set(0,'g');
		delay(5000000);
		pwmled_set(20,'g');
		delay(5000000);
		pwmled_set(40,'g');
		delay(5000000);
		pwmled_set(60,'g');
		delay(5000000);
		pwmled_set(80,'g');
		delay(5000000);
		pwmled_set(100,'g');

	}
}
void delay(int n){

	int i;
	for(i=0;i<n;i++);

}
*/

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

char buf[100];
int n=0;

void MCU_Init(void)
{
	uart0_init(57600);		//baud rate 57600
	GUI_init();
	pwmled_init();
	i2c_init();
	Acc_init();
	
	__disable_irq(); /* Disable interrupt Globally */
	//Configure the PTA14 pin (connected to the INT1 of the MMA8451Q) for falling edge interrupts
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		// Turn on clock to Port A module 
	PORTA_PCR14 |= (0|PORT_PCR_ISF_MASK|	// Clear the interrupt flag 
					  PORT_PCR_MUX(0x1)|	// PTA14 is configured as GPIO 
					  PORT_PCR_IRQC(0xA));	// PTA14 is configured for falling edge interrupts 
	//Enable PORTA interrupt on NVIC
	// writing 1 to the Interrupt clear-pending bits
   // 	is to removes pending state from interrupt.
	int irq_num=PORTA_IRQn; //30
	NVIC->ICPR[0] |= 1 << irq_num;  // clear any pending interrupt of PORTA
  NVIC->ISER[0] |= 1 << irq_num; // enable PORTA interrupt
	NVIC_EnableIRQ(PORTA_IRQn);
	
	//NVIC_ICPR |= 1 << ((INT_PORTA - 16)%32); 
	//NVIC_ISER |= 1 << ((INT_PORTA - 16)%32); 
	__enable_irq(); /* Enable interrupt Globally */
}

void PORTA_IRQHandler(){

}
int main(){
	MCU_Init();
	
	short X,Y,Z;
	while(1){
		readAccXYZ();
		X = Xout_perc,Y=Yout_perc,Z=Zout_perc;
		pwmled_update(X,Y,Z);
		GUI_update(X,Y,Z,\
							Xout_g_S,Xout_g_int,Xout_g_dec1,Xout_g_dec2,\
							Yout_g_S,Yout_g_int,Yout_g_dec1,Yout_g_dec2,\
							Zout_g_S,Zout_g_int,Zout_g_dec1,Zout_g_dec2);
	}
}
