//===============================
//Author: Peilin Wu
//Data: 24/11/2020
//Descibtion: i2c module header file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================
#ifndef _I2C_H
#define _I2C_H

#define SLAVE 0
#define MASTER 1

#define NONE_ERR 0
#define ERR_NO_ACK 0x01
#define ERR_ARB_LOST 0x02
#define ERR_BUS_BUSY 0x03

#include "MKL25Z4.h"

//===========================================
//Function name: i2c_init
//Describtion: initilize I2C0->PTE24 PTE25
//Parameters:	mode-> SLAVE(0);MASTER(1)
//Function return: None
//===========================================
void i2c_init(uint8_t mode);

//===========================================
//Function name: 	i2c_signal
//Describtion: 		send start or end signal;
//Parameters:			's'(start)->start signal; 'o'(over)->over signal;
//Function return: None
//===========================================
void i2c_signal(uint8_t start_stop);

//===========================================
//Function name: Pause
//Describtion: 	execute very times of nop
//Parameters:		nop times
//Function return: None
//===========================================
void Pause(int number);

//===========================================
//Function name: 	i2c_wait
//Describtion: 		wait for one byte transimission finishes
//Parameters:			None
//Function return:None 
//===========================================
void i2c_wait();

//===========================================
//Function name: 	i2c_WrByte
//Describtion: 		send a byte to slave
//Parameters:			SlavAddr->7 bits address of slave
//								RegAddr	->the register address to write
//								Data		->data sent
//Function return:0	-> None Error:send successfully
//								1 -> No Ack:Slave not response
//===========================================
int i2c_WrByte(char SlavAddr, char RegAddr, char Data);

#endif