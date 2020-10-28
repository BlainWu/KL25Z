//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: UART driver header file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================

# ifndef _UART_H
# define _UART_H

#include "MKL25Z4.h"
# define UART_0 0
# define UART_1 1
# define UART_2 2


//===========================================
//Function name: uart_init
//Describtion: Initialize the UART
//Parameters: UART_No: UART_0/UART_1/UART_2
//						baud_rate:1200/2400/4800/9600/38400/575600/115200/460800/921600/230400
//Function return: None
//===========================================
void uart_init(uint8_t UART_No,uint16_t baud_rate);


# endif

