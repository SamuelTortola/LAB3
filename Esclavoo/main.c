//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Electrónica digital 2
// Autor: Samuel Tortola - 22094
// Proyecto: Laboratorio 3
// Hardware: Atmega238p
// Creado: 26/07/2024
//Última modificación: 26/07/2024
//******************************************************************************
//CODIGO DEL ESCLAVO

#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>


#include "ADC/ADC.h"   //Incluir libreria de ADC
#include "POT/POT.h"  //Incluir libreria de Manejo de potenciometros



uint8_t caso = 0, Val1 = 0, Val2 = 0;





void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	DDRD = 0xFF;  //Puerto D como salida
	DDRB = 0xFF;  //Puerto B como salida
	DDRC = 0;  //Puerto C como entrada
	
	
	initADC(); //Iniciar ADC
	
	sei(); //Activar interrupciones
}


int main(void)
{
	setup();
	
	while (1)
	{
		
		ADCSRA |=(1<<ADSC);  //Leer ADC
		

	}
	
		
	
	
	
}



ISR(ADC_vect){
	
	switch (caso){
		case 0:
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0)); //Borrar configuracion actual y poner ADC1
		Val1 = ADCH;
		caso = 1;
		break;
		
		case 1:
		ADMUX &= ~((1<<MUX2)|(1<<MUX1)|(1<<MUX0));   //Borrar configuracion actual y poner ADC0
		ADMUX |= (1<<MUX0);
		Val2 = ADCH;
		caso = 0;
		break;
	}
	
	ADCSRA |= (1<<ADIF); //Se borra la bandera de interrupción
}


