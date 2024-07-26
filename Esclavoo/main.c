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
#include "SPI/SPI.h"


uint8_t caso = 0, Val1 = 0, Val2 = 0;



void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	DDRD = 0xFF;  //Puerto D como salida
	DDRC = 0;  //Puerto C como entrada
	
	
	initADC(); //Iniciar ADC
	SPI_init();
	SPCR |= (1<<SPIE); //Activar interrupcion SPI
		
	sei(); //Activar interrupciones
}


int main(void)
{
	setup();
	
	while (1)
	{
		
		
		
		
		ADCSRA |=(1<<ADSC);  //Leer ADC
		_delay_ms(10);



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


ISR(SPI_STC_vect){
	uint8_t SPIVALOR = SPDR;
	
	if (SPIVALOR == 1)  //Si el maestro quiere ver el valor de los potenciometros
	{
		SPI_tx(Val1);
	}
	
	
}


