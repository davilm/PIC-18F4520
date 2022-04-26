#include <p18f4520.h>

#define chave_minuto PORTAbits.RA1
#define chave_hora PORTAbits.RA0
#define chave_definir_alarme PORTAbits.RA2
#define buzzer PORTAbits.RA3

unsigned char contador_unidade_segundos = 0;
unsigned char contador_dezena_segundos = 0;
unsigned char contador_unidade_minutos = 0;
unsigned char contador_dezena_minutos = 0;
unsigned char contador_unidade_horas = 0;
unsigned char contador_dezena_horas = 0;

unsigned char auxiliar_unidade_segundos = 0;
unsigned char auxiliar_dezena_segundos = 0;
unsigned char auxiliar_unidade_minutos = 0;
unsigned char auxiliar_dezena_minutos = 0;
unsigned char auxiliar_unidade_horas = 0;
unsigned char auxiliar_dezena_horas = 0;

unsigned char alarme_unidade_minutos = 99;
unsigned char alarme_dezena_minutos = 99;
unsigned char alarme_unidade_horas = 99;
unsigned char alarme_dezena_horas = 99;

unsigned char converte_BCD [10] = {
	0b00000000,
	0b00000001,
	0b00000010,
	0b00000011,
	0b00000100,
	0b00000101,
	0b00000110,
	0b00000111,
	0b00001000,
	0b00001001
};

void delay_s(unsigned int segundos){
	
	int i;
	for(i=0;i<segundos;i++){
		unsigned short long j;
		for(j=0;j<40000;j++){}
	}
}

void contador_segundo(void){
	
	contador_unidade_segundos++;
	if(contador_unidade_segundos > 9){
		contador_unidade_segundos = 0;
		contador_dezena_segundos++;
		if(contador_dezena_segundos > 5){
			contador_dezena_segundos = 0;
			contador_unidade_minutos++;
			if(contador_unidade_minutos > 9){
				contador_unidade_minutos = 0;
				contador_dezena_minutos++;
				if(contador_dezena_minutos > 5){
					contador_dezena_minutos = 0;
					contador_unidade_horas++;
					if(contador_dezena_horas == 2 && contador_unidade_horas > 3){
						contador_unidade_horas = 0;
						contador_dezena_horas = 0;
					}else if(contador_unidade_horas > 9){
						contador_unidade_horas = 0;
						contador_dezena_horas++;
					}
				}
			}
		}
	}
}

void contar_minuto(void){
	
	contador_unidade_minutos++;
	if(contador_unidade_minutos > 9){
		contador_unidade_minutos = 0;
		contador_dezena_minutos++;
		if(contador_dezena_minutos > 5){
			contador_dezena_minutos = 0;
			contador_unidade_horas++;
			if(contador_dezena_horas == 2 && contador_unidade_horas > 3){
				contador_unidade_horas = 0;
				contador_dezena_horas = 0;
			}else if(contador_unidade_horas > 9){
				contador_unidade_horas = 0;
				contador_dezena_horas++;
			}
		}
	}
}

void contar_hora(void){

	contador_unidade_horas++;
	if(contador_dezena_horas == 2 && contador_unidade_horas > 3){
		contador_unidade_horas = 0;
		contador_dezena_horas = 0;
	}else if(contador_unidade_horas > 9){
		contador_unidade_horas = 0;
		contador_dezena_horas++;
	}
}

void mostrar(void){
	
	PORTC = converte_BCD[contador_unidade_segundos] | converte_BCD[contador_dezena_segundos] << 4;
	PORTD = converte_BCD[contador_unidade_minutos] | converte_BCD[contador_dezena_minutos] << 4;
	PORTB = converte_BCD[contador_unidade_horas] | converte_BCD[contador_dezena_horas] << 4;
}

void modo_ajuste(void){

	if(chave_definir_alarme){
		delay_s(1);
			if(chave_definir_alarme){
				unsigned char aux = 1;
				// Guardar o estado dos contadores
			 	auxiliar_unidade_segundos = contador_unidade_segundos;
				auxiliar_dezena_segundos = contador_dezena_segundos;
				auxiliar_unidade_minutos = contador_unidade_minutos;
				auxiliar_dezena_minutos = contador_dezena_minutos;
				auxiliar_unidade_horas = contador_unidade_horas;
				auxiliar_dezena_horas = contador_dezena_horas;
				// Zera o relógio
				contador_unidade_segundos = 0;
				contador_dezena_segundos = 0;
				contador_unidade_minutos = 0;
				contador_dezena_minutos = 0;
				contador_unidade_horas = 0;
				contador_dezena_horas = 0;
				mostrar();

				while(aux){
					if(chave_minuto){
						// Ajusta os minutos do alarme
						contar_minuto();
						delay_s(1);
						mostrar();
					}else if(chave_hora){
						// Ajusta as horas do alarme
						contar_hora();
						delay_s(1);
						mostrar();
					}else{
						if(chave_definir_alarme){
							delay_s(1);
								if(chave_definir_alarme){
									// Salva a hora e os minutos do alarme
									alarme_unidade_minutos = contador_unidade_minutos;
                                    alarme_dezena_minutos = contador_dezena_minutos;
                                    alarme_unidade_horas = contador_unidade_horas;
                                    alarme_dezena_horas = contador_dezena_horas;
									// Recupera os dados da hora
									contador_unidade_segundos = auxiliar_unidade_segundos;
									contador_dezena_segundos = auxiliar_dezena_segundos;
									contador_unidade_minutos = auxiliar_unidade_minutos;
									contador_dezena_minutos = auxiliar_dezena_minutos;
									contador_unidade_horas = auxiliar_unidade_horas;
									contador_dezena_horas = auxiliar_dezena_horas;
									aux = 0;
								}
							}
						mostrar();
					}
				}
			}
	}
}

void alarme(void){
	
	if((contador_unidade_minutos == alarme_unidade_minutos) 
		&& (contador_dezena_minutos == alarme_dezena_minutos)
		&& (contador_unidade_horas == alarme_unidade_horas) 
		&& (contador_dezena_horas == alarme_dezena_horas)){
		
            if(contador_unidade_segundos <= 3){
                buzzer = 1;
            }else{
                buzzer = 0; 
                alarme_unidade_minutos=99;
                alarme_dezena_minutos=99;
                alarme_unidade_horas=99;
                alarme_dezena_horas=99;
            }
	}
}



main(){

	TRISAbits.RA1 = 1;
	TRISAbits.RA0 = 1;
	TRISAbits.RA2 = 1;
	TRISAbits.RA3 = 0;
	ADCON1 = 0b00001111;
	TRISC = 0b00000000;  // segundos
	TRISD = 0b00000000;  // minutos
	TRISB = 0b00000000;  // horas
	while(1){
		if(chave_minuto){
			contar_minuto();
			delay_s(1);
			mostrar();
		}else if(chave_hora){
			contar_hora();
			delay_s(1);
			mostrar();
		}else{
			modo_ajuste();
			alarme();
			contador_segundo();
			delay_s(1);
			mostrar();
		}
	}
}