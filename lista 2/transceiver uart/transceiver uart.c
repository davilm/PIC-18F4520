#include <p18f4520.h>

#define tx PORTCbits.RC0
#define rx PORTCbits.RC1


int dado[8];

void delay_1200bps(void){	// 1/1200 = 833us (tempo de 1 bit)
	unsigned int i;
	for(i=0;i<108;i++){}
}

void delay_meiobit(void){
	unsigned int i;
	for(i=0;i<53;i++){}
	i=0;
	i=0;
	i=0;
}

void transmite_serial(void){
	unsigned int i;
	
	tx = 1;
	delay_1200bps();		//repouso
	tx = 0;
	delay_1200bps();		//start

	for(i=0;i<8;i++){
		tx = dado[i];
		delay_1200bps();
	}

	tx = 1;					//stop bit
	delay_1200bps();

}
 
void recebe_serial (void){
	int i;

	while(rx){};		//espera start
	delay_meiobit();	//defasa de meio bit
	delay_1200bps();	//tempo do bit


	for(i=0;i<8;i++){
		dado[i] = rx;
		delay_1200bps();
	}
	
}

main(){

	TRISCbits.RC0 = 0;		//tx -> saida
	TRISCbits.RC1 = 1;		//rx -> entrada

	delay_1200bps();
	delay_meiobit(); 
    
	dado[0] = 1;
    dado[1] = 0;
    dado[2] = 0;
    dado[3] = 0;
    dado[4] = 0;
    dado[5] = 0;
    dado[6] = 1;
    dado[7] = 0;

	transmite_serial();

	while(1){
		recebe_serial();
		transmite_serial();
	}
}