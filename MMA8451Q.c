//===============================
//Author: Peilin Wu
//Data: 28/10/20
//Descibtion: UART driver source file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================

# include "MMA8451Q.h"
# include <stdio.h>

unsigned char AccData[6];			//xyz_M_L
short Xout_14_bit,Yout_14_bit,Zout_14_bit;
float Xout_g,Yout_g,Zout_g;
char DataReady;
char Xoffset,Yoffset,Zoffset;

void Acc_init(void){

	unsigned char reg_val = 0;
	int errCode;

	errCode = i2c_WrByte(MMA_I2C_ADDRESS,CTRL_REG2,0x40);	//device reset
	if(errCode != 0){
		char err_msg[100];
		sprintf(err_msg,"Write operation failed. Error code:%d \r\n",errCode);
		uart0_sent_string(err_msg);
	}
	
	do{		//wait for the Reset 
		reg_val = i2c_RdByte(MMA_I2C_ADDRESS,	CTRL_REG2) & 0x40;
	}while(reg_val);
	
	i2c_WrByte(MMA_I2C_ADDRESS,XYZ_DATA_CFG_REG,0x00);//Full scale = 2g
	i2c_WrByte(MMA_I2C_ADDRESS,CTRL_REG2,0x02);				//High resolution mode
	i2c_WrByte(MMA_I2C_ADDRESS,CTRL_REG1,0x3D);				//ODR=1.56HZ,Active mode, reduced noise

}

void readAccXYZ(void){

	unsigned char reg_val = 0;

	while(!reg_val){	//XYZ Data Ready
		reg_val = i2c_RdByte(MMA_I2C_ADDRESS,STATUS_REG) & 0x08;
	}

	//if ready, read 6 byte data
	i2c_RdMultiBytes(MMA_I2C_ADDRESS,OUT_X_MSB_REG,6,AccData);

	Xout_14_bit = ((short) (AccData[0]<<8 | AccData[1]))>>2;
	Yout_14_bit = ((short) (AccData[2]<<8 | AccData[3]))>>2;
	Zout_14_bit = ((short) (AccData[4]<<8 | AccData[5]))>>2;
}
