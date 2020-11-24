//===============================
//Author: Peilin Wu
//Data: 23/11/2020
//Descibtion: PWM signal light LED on KL25Z source file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================
#ifndef _PWMLED_H
#define _PWMLED_H

#include "MKL25Z4.h"

//===========================================
//Function name: pwmled_init
//Describtion: initialize PTM module and light the RGB light on board
//Parameters: None
//Function return: None
//===========================================
void pwmled_init();

//===========================================
//Function name: pwmled_set
//Describtion: 
//Parameters:		duty_cycle: 0~100 (percentage)
//							colour:			r/R g/G b/B
//Function return: None
//===========================================
void pwmled_set(uint16_t duty_cycle,uint8_t colour);

#endif