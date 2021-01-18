//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: Accelerator module header file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================
#ifndef _MMA8451Q_H
#define _MMA8451Q_H

#define STATUS_REG            0x00		

#define OUT_X_MSB_REG         0x01		
#define OUT_X_LSB_REG         0x02		
#define OUT_Y_MSB_REG         0x03		
#define OUT_Y_LSB_REG         0x04		
#define OUT_Z_MSB_REG         0x05		
#define OUT_Z_LSB_REG         0x06		

#define F_SETUP_REG           0x09    	
#define TRIG_CFG_REG          0x0A    	
#define SYSMOD_REG            0x0B    	
#define INT_SOURCE_REG        0x0C    	
#define WHO_AM_I_REG          0x0D 
#define XYZ_DATA_CFG_REG      0x0E
#define HP_FILTER_CUTOFF_REG  0x0F

#define ASLP_COUNT_REG        0x29 

#define CTRL_REG1             0x2A 
#define CTRL_REG2             0x2B 
#define CTRL_REG3             0x2C 
#define CTRL_REG4             0x2D 
#define CTRL_REG5             0x2E 
#define OFF_X_REG             0x2F    	
#define OFF_Z_REG             0x31

//MMA8451Q 7-bit I2C address
#define MMA_I2C_ADDRESS   0x1D		// SA0 pin = 1 -> 7-bit I2C address is 0x1D 

#include "MKL25Z4.h"
#include "i2c.h"
#include "uart.h"

//===========================================
//Function name: Acc_init()
//Describtion: Initialize the MMA acceleration sensor on the KL25Z.Must be placed after I2C initialization.
//===========================================
void Acc_init(void);

//===========================================
//Function name: readAccXYZ()
//Describtion: Stores the data from the accelerometer into global variables.
//===========================================
void readAccXYZ(void);

//===========================================
//Function name: cal_density()
//Describtion: Calculate the raw data read as the percentage of brightness in the LED lamp.
//Parameters:	short origin_out-> Data in range of [0,4096] - 2g
//Function return:  the percentage of brightness in the LED lamp in short type
//===========================================
short cal_density(short origin_out);

//===========================================
//Function name: split_short()
//Describtion: Calculate the raw data read as the percentage of brightness in the LED lamp.
//Parameters:	Divide a floating point number into integers.Since the KL25 doesn't have an FPU,\
							can't output floating-point numbers directly on the screen.
//===========================================
void split_short(short origin);

#endif
