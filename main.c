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
	
		char str[100];
		if(uart0_reci_str(str)){
		
			uart0_sent_string("The line is:");
			uart0_sent_string(str);
			
			memset(str,0,strlen(str));					//GREAT! clear the string
		
		}
	
	}
	
	return 0;
}