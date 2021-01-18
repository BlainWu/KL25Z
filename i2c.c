#include <MKL25Z4.H>
#include "i2c.h"

void i2c_init(void){

	//I2C_0 use PORTE_24(SCL) PORTE_25(SDA)
	SIM_SCGC4 |= SIM_SCGC4_I2C0(1);		//enable clock for I2C0
	SIM_SCGC5 |= SIM_SCGC5_PORTE(1);	//enable clock for PortE
	//set pins to I2C function
	PORTE_PCR24 |= PORT_PCR_MUX(5);		//set PTE_24 as I2C0_SCL
	PORTE_PCR25 |= PORT_PCR_MUX(5);		//set PTE_25 as I2C0_SDA
	
	//MULT:0h ICR:14h -> SDA:2.125us | SCL start:4.250us | SCL stop:5.125us
	I2C0->F = I2C_F_ICR(0x14) ;//set BautRate
	I2C0_C1 = 0;
	I2C0_S = I2C_S_IICIF(1); //clear the interrupt (w1c)
	//enable i2c and set to master mode
	I2C0_C1 |= I2C_C1_IICEN(1); //enbale I2C0
}

void i2c_start(){
	//set Transmit Mode as Transmiter
	//setting MST to 1 can produce start signal
	I2C0_C1 |= I2C_C1_TX(1);
	I2C0_C1 |= I2C_C1_MST(1);
}

void i2c_wait(){
	 while((I2C0_S & 0x02)==0) {} //wait for Interrupt Flag is 1
	 I2C0_S |= 0x02;
}

int i2c_WrByte(unsigned char SlaveAddr, unsigned char RegAddr, char Data)
{
	
	int retry = 1000;
	while (I2C0->S & 0x20) { // wait until bus is available
		if (--retry <= 0)
		return ERR_BUS_BUSY;
		Pause(50);
	}
	//send start signal
	i2c_start();
	//set first 7 bit as address and 8th bit as 0(WR) and send it
	I2C0->D = SlaveAddr<<1;	
	i2c_wait();	

	if (I2C0_S & I2C_S_RXAK_MASK) 	//if no slave response to the Address
		return ERR_NO_ACK;
		
  //send register address to write
	I2C0_D = RegAddr;	
	i2c_wait();

	if (I2C0_S & I2C_S_RXAK_MASK)	//if no slave response to the RegAddress
		return ERR_NO_ACK;

	// send data
	I2C0_D = Data;
	I2C_Wait();

	if (I2C0_S & I2C_S_RXAK_MASK) 
		return ERR_NO_ACK;

  I2C_Stop();
	Pause(50);
	return ERR_NONE;
}

unsigned char i2c_RdByte(unsigned char SlaveAddr, unsigned char RegAddr)
{
	unsigned char result;
	//start signal
	I2C_Start();
	//send slave address and write mode	
	I2C0_D = SlaveAddr << 1;	
	I2C_Wait();
	//send register address
	I2C0_D = RegAddr;	
	I2C_Wait();
	//send restart signal
	I2C_RepeatedStart();
	//send slave address and read mode
	I2C0_D = (SlaveAddr << 1) | 0x01;
	I2C_Wait();	
	//change slave as a transmiter
	I2C_EnterRxMode();
	//No ACK signal, prepare to stop
	I2C_DisableAck();
	//dummy read
	result = I2C0_D;
	I2C_Wait();
	//send stop signal
	I2C_Stop();  
	//real read
	result = I2C0_D;
	Pause(50);
	return result;
}

void i2c_RdMultiBytes(unsigned char SlaveAddr, unsigned char RegAddr, unsigned char n, unsigned char *r)
{
	char i;
	I2C_Start();	  
	
	I2C0_D = SlaveAddr << 1;	//Send I2C device address with W/R bit = 0	
	I2C_Wait();										

	I2C0_D = RegAddr;		// Send register address
	I2C_Wait();

	I2C_RepeatedStart();
		
	I2C0_D = (SlaveAddr << 1) | 0x01;	
	I2C_Wait();	

	I2C_EnterRxMode();
	I2C_EnableAck();							//Enable master ACK signal, not to stop
	
	i = I2C0_D;										//dummy read
	I2C_Wait();
	
	for(i=0; i<n-2; i++) 
	{
	    *r = I2C0_D;
	    r++;
	    I2C_Wait();
	}
	//when it's here, the last second one is in I2C0_D
	I2C_DisableAck();
	*r = I2C0_D;
	//after read the last 2nd, last one is read in I2C0_D and NACK is sent
	r++;
	I2C_Wait();
	I2C_Stop();
	*r = I2C0_D; 
	Pause(50);		
}

void Pause(int number)
{
	int cnt;
	for(cnt=0; cnt<number; cnt++)
	{
		asm("nop");
	};
}
