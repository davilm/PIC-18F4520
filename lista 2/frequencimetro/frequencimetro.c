#include <p18f4520.h>

#define sinal PORTDbits.RD0

unsigned int periodo;
unsigned int frequencia;
unsigned int dezena;
unsigned int unidade;

void delay_100us_video (void){
	unsigned char i;
	for(i=0;i<29;i++){}
	i=0;
	i=0;		//ajuste fino do delay
}
//No meu computador a função abaixo deu 100us e a função do video deu mais de 100us
void delay_100us (void){
	unsigned char i;
	for(i=0;i<12;i++){}
	i=0;
	i=0;		//ajuste fino do delay
}

void mede_periodo (void){
	periodo = 0;
	while(sinal){};		//espera o sinal descer
	while(!sinal){};	//espera o sinal subir ou espera transição positiva
	
	while(sinal){
		delay_100us();
		periodo++;
	}

	while(!sinal){
		delay_100us();
		periodo++;
	}
}

void calcula_frequencia (void){
	frequencia = 10000/periodo;
}

int converte_decimal_para_binario(int num){
	int bin = 0, rem = 0, place = 1;  
  
    while(num){  
        rem   = num % 2;  
        num   = num / 2;  
        bin   = bin + (rem * place);  
        place = place * 10;  
    }  
    return bin; 
}


void mostra_frequencia(void){
	int dezena_m,dezena_c,dezena_d,dezena_u;
	int unidade_m,unidade_c,unidade_d,unidade_u; 

	dezena = frequencia/10;
	unidade = frequencia%10;

	dezena = converte_decimal_para_binario(dezena);
	unidade = converte_decimal_para_binario(unidade);

	//separa as casas em variáveis diferentes
	dezena_m = dezena/1000;
	dezena_c = dezena%1000;
	dezena_d = dezena%100;
	dezena_u = dezena_d%10;
	dezena_d = dezena_d/10;
	dezena_c = dezena_c/100;

	//separa as casas em variáveis diferentes
	unidade_m = unidade/1000;
	unidade_c = unidade%1000;
	unidade_d = unidade%100;
	unidade_u = unidade_d%10;
	unidade_d = unidade_d/10;
	unidade_c = unidade_c/100;

	//adiciona os valores ao primeiro display
	PORTCbits.RC0 = dezena_m;
	PORTCbits.RC1 = dezena_c;
	PORTCbits.RC2 = dezena_d;
	PORTCbits.RC3 = dezena_u;

	//adiciona os valores ao segundo display
	PORTCbits.RC4 = unidade_m;
	PORTCbits.RC5 = unidade_c;
	PORTCbits.RC6 = unidade_d;
	PORTCbits.RC7 = unidade_u;
}

void main (void){
	TRISDbits.RD0 = 1; //sinal de freq
	TRISC = 0b00000000; //mostrador
	delay_100us();
	
	while(1){
		mede_periodo();
		calcula_frequencia();
		mostra_frequencia();
	}
}