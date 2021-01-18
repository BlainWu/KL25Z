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
short Xout_perc,Yout_perc,Zout_perc;
short Xout_g_int,Xout_g_dec1,Xout_g_dec2;
short Yout_g_int,Yout_g_dec1,Yout_g_dec2;
short Zout_g_int,Zout_g_dec1,Zout_g_dec2;
char DataReady,Xout_g_S,Yout_g_S,Zout_g_S;
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
	i2c_WrByte(MMA_I2C_ADDRESS,CTRL_REG4,0x01);				//INT_EN_DRDY
	i2c_WrByte(MMA_I2C_ADDRESS,CTRL_REG5,0x01);				//daty ready interrupt to A14 pin
	//i2c_WrByte(MMA_I2C_ADDRESS,CTRL_REG1,0x3D);				//ODR=1.56HZ,Active mode, reduced noise
	//i2c_WrByte(MMA_I2C_ADDRESS,CTRL_REG1,0x25);				//ODR=50HZ,Active mode, reduced noise
	i2c_WrByte(MMA_I2C_ADDRESS,CTRL_REG1,0x2D);				//ODR=12.5HZ,Active mode, reduced noise

}

int abs(int x){
	if(x<0) return -x;
	else return x;
}

void readAccXYZ(void){

	unsigned char reg_val = 0;
	int tmp;
	short tmp_short;

	while(!reg_val){	//XYZ Data Ready
		reg_val = i2c_RdByte(MMA_I2C_ADDRESS,STATUS_REG) & 0x08;
	}

	//if ready, read 6 byte data
	i2c_RdMultiBytes(MMA_I2C_ADDRESS,OUT_X_MSB_REG,6,AccData);
	Xout_14_bit = ((short) (AccData[0]<<8 | AccData[1]))>>2;
	Yout_14_bit = ((short) (AccData[2]<<8 | AccData[3]))>>2;
	Zout_14_bit = ((short) (AccData[4]<<8 | AccData[5]))>>2;
	
	Xout_perc = cal_density(Xout_14_bit);
	Yout_perc = cal_density(Yout_14_bit);
	Zout_perc = cal_density(Zout_14_bit);
	
	tmp_short = Xout_14_bit;
	if(tmp_short>=0) Xout_g_S ='+';
	else Xout_g_S = '-';
	tmp = abs((int)(tmp_short/40.96));
	Xout_g_int = tmp/100;		//integer part
	Xout_g_dec1 = tmp/10;			//1st decimal
	Xout_g_dec2 = tmp%10;			//2nd decimal
	
	tmp_short = Yout_14_bit;
	if(tmp_short>=0) Yout_g_S ='+';
	else Yout_g_S = '-';
	tmp = abs((int)(tmp_short/40.96));
	Yout_g_int = tmp/100;		//integer part
	Yout_g_dec1 = tmp/10;			//1st decimal
	Yout_g_dec2 = tmp%10;			//2nd decimal

	tmp_short = Zout_14_bit;
	if(tmp_short>=0) Zout_g_S ='+';
	else Zout_g_S = '-';
	tmp = abs((int)(tmp_short/40.96));
	Zout_g_int = tmp/100;		//integer part
	Zout_g_dec1 = tmp/10;			//1st decimal
	Zout_g_dec2 = tmp%10;			//2nd decimal
	
}

short cal_density(short origin_out){

	short result = 0;
	if(origin_out < 0)
		origin_out = -origin_out;
	result = (origin_out/40.96);
	if(result >100)
		result = 100;
	return result;
}
