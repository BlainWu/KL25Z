//===============================
//Author: Peilin Wu
//Data: 24/11/2020
//Descibtion: i2c module source file
//Student Number: 17049125
//E-mail: p.wu@northumbria.ac.uk
//===============================
#include "i2c.h"

void i2c_init(uint8_t mode){
	
	//I2C_0 use PORTE_24(SCL) PORTE_25(SDA)
	SIM_SCGC4 |= SIM_SCGC4_I2C0(1);		//enable clock for I2C0
	SIM_SCGC5 |= SIM_SCGC5_PORTE(1);	//enable clock for PortE
	
	PORTE_PCR24 |= PORT_PCR_MUX(5);		//set PTE_24 as I2C0_SCL
	PORTE_PCR25 |= PORT_PCR_MUX(5);		//set PTE_25 as I2C0_SDA
	
	//MULT:0h ICR:14h -> SDA:2.125us | SCL start:4.250us | SCL stop:5.125us
	I2C0_F |= I2C_F_ICR(0x14) + I2C_F_MULT(0);	//set BautRate	
	I2C0_S = I2C_S_IICIF(1);		//clear the interrupt (w1c)
	I2C0_C1 = 0;
	I2C0_C1 |= I2C_C1_IICEN(1);	//enbale I2C0
	//select mode as Master or Slave
	if(mode) I2C0_C1 |= I2C_C1_MST(1);
	else	I2C0_C1 |= I2C_C1_MST(0);
	
}


void i2c_signal(uint8_t start_stop){

	switch(start_stop){
		case 's':
		case 'S':
			//set Transmit Mode as Transmiter
			//setting MST to 1 can produce start signal
			I2C0_C1 |= I2C_C1_TX(1);
			I2C0_C1 |= I2C_C1_MST(1);
			break;
		
		case 'o':
		case 'O':
			//set Transmit Mode as Reciver
			//setting MST to 0 can produce stop signal
			I2C0_C1 |= I2C_C1_MST(0);
			I2C0_C1 |= I2C_C1_TX(0);
			break;
		
		case 'r':
		case 'R':
			//restart signal, it's different from start signal
			I2C0_C1 |= I2C_C1_RSTA(1);
			break;
		
		case 'c':
		case 'C':
			//change mode: change master as reciver; slave as transmiter
			I2C0_C1 |= I2C_C1_TX(0);
	}
}

void Pause(int number){
	volatile int cnt;
	for(cnt = 0; cnt<number; cnt++){
		asm("nop");
	}
}

void i2c_wait(){
	while((I2C0_S & I2C_S_IICIF_MASK)==0){}	//wait for Interrupt Flag is 1
	I2C0_S |= I2C_S_IICIF(1);								//set Interrupt Flag 0
}

int i2c_WrByte(char SlavAddr, char RegAddr, char Data){
	//send start signal
	i2c_signal('s');	
	
	//set first 7 bit as address and 8th bit as 0(WR) and send it
	I2C0_D = SlavAddr<<1;		
	i2c_wait();
	if(I2C0_S & I2C_S_RXAK_MASK)	//if no slave response to the Address
		return ERR_NO_ACK;
	
	//send register address to write
	I2C0_D = RegAddr;	
	if(I2C0_S & I2C_S_RXAK_MASK)	//if no slave response to the RegAddress
		return ERR_NO_ACK;
	
	//send data
	I2C0_D = Data;
	if(I2C0_S & I2C_S_RXAK_MASK)	//if no slave response to the Data
		return ERR_NO_ACK;
	
	//send stop signal
	i2c_signal('o');
	
	Pause(50);
	return NONE_ERR;
}

unsigned char i2c_RdByte(char SlavAddr, char RegAddr){

	unsigned char data;
	i2c_signal('s');//start signal
	
	//send slave address and write mode
	I2C0_D = SlavAddr<<1;
	i2c_wait();
	
	//send register address
	I2C0_D = RegAddr;
	i2c_wait();
	
	//send restart signal
	i2c_signal('r');
	
	//send slave address and read mode
	I2C0_C1 = (SlavAddr<<1) | 0x01;
	i2c_wait();
	
	//change slave as a transmiter
	i2c_signal('c');
	I2C0_C1 |= I2C_C1_TXAK(1);//No ACK signal, prepare to stop
	data = I2C0_D;//**dummy read to initiate bus read**
	i2c_wait();
	
	//send stop signal
	i2c_signal('o');
	
	data = I2C0_D;//real read
	
	Pause(50);
	return data;
}

unsigned char i2c_RdMultiByte(char SlavAddr, char RegAddr, int nRd, char *buff){

	unsigned char data;
	int i;
	
	i2c_signal('s');
	I2C0_D = SlavAddr<<1;
	i2c_wait();
	
	I2C0_D = RegAddr;
	i2c_wait();
	
	i2c_signal('r');
	
	I2C0_C1 = (SlavAddr<<1) | 0x01;
	i2c_wait();
	
	i2c_signal('c');
 	I2C0_C1 |= I2C_C1_TXAK(0);//Enable master ACK signal, not to stop
	
	data = I2C0_D;//dummy read
	i2c_wait();
	//all above is same as i2c_RdByte
	
	for(i=0; i<nRd-2; i++){
		*buff = I2C0_D;
		buff++;
	}
	//when it's here, the last second one is in I2C0_D
	I2C0_C1 |= I2C_C1_TXAK(1);//No ACK signal, prepare to stop
	*buff = I2C0_D;
	//after read the last 2nd, last one is read in I2C0_D and NACK is sent
	buff++;
	i2c_wait();
	i2c_signal('o');
	*buff = I2C0_D;
	Pause(50);
	return data;
}