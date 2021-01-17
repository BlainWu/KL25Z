//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: KD6027 assignment project
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================

#include "pwmled.h"
#include "uart.h"
#include "i2c.h"
#include "MMA8451Q.H"
#include <string.h>


int main(){
	
	uart0_init(38400);		//baud rate 38400
	pwmled_init();
	i2c_init(i2c_MASTER);
	Acc_init();
	
	uart0_sent_string("Finshed initialzation\r\n");
	
	short Xout_14_bit,Yout_14_bit,Zout_14_bit;
	char out_info[100];
	
	
	while(1){
		//readAccXYZ();
		//uart0_sent_string(Xout_14_bit);
	}

}

