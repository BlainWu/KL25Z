//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: The main function of the project
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================

#include "uart.h"

void delayMs(int n) {
    int i;
    int j;
    for(i = 0 ; i < n; i++)
        for (j = 0; j < 7000; j++) {}
}

int main(){
	 char msg[] = "Northumbria University!\r\n"; //output message
	 uart_init(UART_0,38400);
	 for(int i = 0;i < 25;i++){
		 while(!(UART0->S1 & 0x80)) {
		 //while transmiting, do noting
		 }
		 UART0->D = msg[i];
		 delayMs(20);
	 }
 }

