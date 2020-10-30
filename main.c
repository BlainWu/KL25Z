//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: KD6027 assignment project
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================

#include "uart.h"

int main(){

	uart0_init(38400);
	
	char msg[] = "Northumbria University!!!\r\n";

	uart0_sent_string(msg);
	
	while(1){
	
		uint8_t reci_flag = 0,ch;
		if((ch = uart0_reci_char(&reci_flag)) && reci_flag){
			uart0_sent_char(ch);
			reci_flag = 0;
		}
	}
	
	return 0;
}