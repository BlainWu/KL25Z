//===============================
//Author: Peilin Wu
//Data: 22/11/2020
//Descibtion: GPIO driver header file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================


#ifndef _GPIO_H
#define _GPIO_H

#include "MKL25Z4.h"
#define INPUT 0
#define OUTPUT 1

//===========================================
//Function name: gpio_init
//Describtion:	initialize gpio
//Parameters:		port_group	:A~E
//							uint8_t			:0~31
//							io					:INPUT/OUTPUT
//===========================================
void gpio_init(uint8_t port_group,uint8_t pin_num,uint8_t io);

//===========================================
//Function name: gpio_set
//Describtion:	set 1 to specific pin
//Parameters:		port_group	:A~E
//							uint8_t			:0~31
//===========================================
void gpio_set(uint8_t port_group,uint8_t pin_num);

//===========================================
//Function name: gpio_clear
//Describtion:	set 0 to specific pin
//Parameters:		port_group	:A~E
//							uint8_t			:0~31
//===========================================
void gpio_clear(uint8_t port_group,uint8_t pin_num);

//===========================================
//Function name: gpio_revese
//Describtion:	revease the state of specific pin
//Parameters:		port_group	:A~E
//							uint8_t			:0~31
//===========================================
void gpio_revese(uint8_t port_group,uint8_t pin_num);
#endif
