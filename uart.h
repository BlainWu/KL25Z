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
#include "string.h"

//===========================================
//Function name: uart_init
//Describtion: Initialize the UART
//Parameters:  baud_rate:1200/2400/4800/9600/38400/575600/115200/460800/921600/230400
//Function return: None
//===========================================
void uart0_init(uint16_t baud_rate);

//===========================================
//Function name: uart_sent_char
//Describtion: 			Sent one character
//Parameters:				ch: The charater which is sent
//Function return: 1 -> sent successfully
//								 0 -> fail to sent
//===========================================
uint8_t uart0_sent_char(uint8_t ch);

//===========================================
//Function name: uart0_sent_string
//Describtion: 			Sent a string
//Parameters:				ch: The charater which is sent
//Function return: 1 -> sent successfully
//								 0 -> fail to sent
//===========================================
uint8_t uart0_sent_string(char* str);

//===========================================
//Function name: uart0_reci_char
//Describtion: 			Recive a character
//Parameters:				trigger->when recived a character,trigger=1; else trigger=0
//Function return: 	return a char(8bit)
//===========================================
uint8_t uart0_reci_char(uint8_t* trigger);

//===========================================
//Function name: uart0_reci_str
//Describtion: 			Recive a character string
//Parameters:				a empty str address
//Function return: 	return a string(address of the first char)
//===========================================
uint8_t uart0_reci_str(char* str);

# endif

