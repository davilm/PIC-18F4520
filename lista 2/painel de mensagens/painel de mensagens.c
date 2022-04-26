#include <p18f4520.h>

unsigned char mensagem_painel [] = {

0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b00000000,
0b01111110,
0b10111101,
0b11000011,//D
0b11111111,
0b00000011,
0b11110101,
0b11110110,
0b11110101,
0b10000011,//A
0b11110000,
0b10001111,
0b01111111,
0b10001111,
0b11110000,//V
0b11111111,
0b01111110,
0b00000000,
0b01111110,//I
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
};
	
unsigned char ativar_painel_LATD [] = {

0b00000001,
0b00000010,
0b00000100,
0b00001000,
0b00010000,
0b00100000,
0b01000000,
0b10000000,

};
void delay_varredura(void){
	unsigned int i;
	for (i=0;i<1000;i++){}
}
 
//void mostra_video(){
// 	int p=0, i=0, j=8, k, mascara = 0b00000001;
	
// 	for (p=0;p<32;p++){
// 		i=p;
// 		j=p+8;
// 		mascara=0b00000001;
// 		for(k=0;k<8;k++){
// 			LATD = 0b00000000;
// 			PORTC = mensagem_painel(i-k);
// 			PORTB = mensagem_painel(j+k);
// 			LATD = mascara;
// 			delay_varredura();
// 			mascara = mascara <<1;
// 		}
// 	}
// }
main(){
	int j, k, count_LATC, count_LATB;

	TRISD = 0;	//varredura painel 1 e  2
	TRISC = 0;	//barramento painel 1
	TRISB = 0;	//barramento painel 2

	ADCON1 = 0b00001111;	//para configurar a porta b como IO

	while(1){
//		mostra_video();

     for(j=0;j<8;j++){
			count_LATC = j;
			count_LATB = j+8;
			for(k=0;k<8;k++){
				LATC = mensagem_painel[count_LATC];
				LATB = mensagem_painel[count_LATB];
				LATD = ativar_painel_LATD[k];
				delay_varredura();
				LATD = 0b00000000;
				count_LATC++;
				count_LATB++;
			}
		}
	}
}