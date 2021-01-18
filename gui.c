//===============================
//Author: Peilin Wu
//Data: 10/1/20
//Descibtion: GUI module source file
//E-mail: p.wu@northumbria.ac.uk
//===============================
#include "gui.h"

void GUI_init(void){
	uart0_sent_string("\33[2J \33[1;1H");	//Clear the screen and set cursor at (1,1)
	uart0_sent_string("|----------------------------------------------------|\r\n");
	uart0_sent_string("|         KL25Z application: Tilt Indicator          |\r\n");
	uart0_sent_string("|----------------------------------------------------|\r\n");
	uart0_sent_string("|      Author: Wu Peilin  | Northumbria University   |\r\n");
	uart0_sent_string("|----------------------------------------------------|\r\n");
	uart0_sent_string("|  Axis |        X             Y            Z        |\r\n");
	uart0_sent_string("|Gravity|             g             g            g   |\r\n");
	uart0_sent_string("|       |   \033[41m           \033[0m   \033[42m           \033[0m   \033[44m           \033[0m  |\r\n");
	uart0_sent_string("|  LED  |   Red:      %   Green:    %   Blue:     %  |\r\n");
	uart0_sent_string("|----------------------------------------------------|\r\n");
}

void GUI_update(short X,short Y, short Z,char Xout_g_S,short Xout_g_int,short Xout_g_dec1,short Xout_g_dec2,\
								char Yout_g_S,short Yout_g_int,short Yout_g_dec1,short Yout_g_dec2,\
								char Zout_g_S,short Zout_g_int,short Zout_g_dec1,short Zout_g_dec2){

	char buf[100];
	uart0_sent_string("\33[9;22H \33[9;36H \33[9;50H \033[0m");//clear the highest postion
	uart0_sent_string("\33[7;21H \33[7;35H \33[7;48H \033[0m");//clear the highest postion
	sprintf(buf,"\33[9;20H\33[31m%2d\33[9;34H\33[32m%2d\33[9;48H\33[34m%2d\033[0m",X,Y,Z);//update value density
	uart0_sent_string(buf);
									
	sprintf(buf,"\33[7;16H%c%d.%d%d",Xout_g_S,Xout_g_int,Xout_g_dec1,Xout_g_dec2);//update value density
	uart0_sent_string(buf);
									
	sprintf(buf,"\33[7;30H%c%d.%d%d",Yout_g_S,Yout_g_int,Yout_g_dec1,Yout_g_dec2);//update value density
	uart0_sent_string(buf);
									
	sprintf(buf,"\33[7;43H%c%d.%d%d\033[?25l",Zout_g_S,Zout_g_int,Zout_g_dec1,Zout_g_dec2);//update value density
	uart0_sent_string(buf);
								
	
}
