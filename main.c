//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Electrónica digital 2
// Autor: Samuel Tortola - 22094
// Proyecto: Laboratorio 2
// Hardware: Atmega238p
// Creado: 18/07/2024
//Última modificación: 19/07/2024
//******************************************************************************


#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>


#include "ADC/ADC.h"   //Incluir libreria de ADC
#include "UART/UART.h"  //Incluir libreria de UART



int activa = 0;
volatile char receivedChar = 0;    //Variable que almacena el valor del UART


void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	DDRD = 0xFF;  //Puerto D como salida
	DDRB = 0xFF;  //Puerto B como salida
	DDRC =0;  //Puerto C como entrada
	
	UCSR0B = 0;  //Usar los pines TX y RX como digitales
	
	
	
	//initADC(); //Iniciar ADC
	
	initUART9600();  //Iniciar UART
	
	sei(); //Activar interrupciones
}


int main(void)
{
	setup();
	
	while (1)
	{
		
		if(activa == 0){
			writeTextUART("\n\r     **************Hola como esta****************");   //Mostrar inicio
			writeUART(10);
			writeUART(13);
			writeUART(10);
			writeTextUART("          Coloque 1 para leer potenciometros");   //Mostrar inicio
			writeUART(10);
			writeUART(13);
			writeTextUART("          Coloque 2 para incrementar contador\n\r");   //Mostrar inicio
			writeUART(10);
			writeUART(13);
			activa = 1;   //Salir del menu
	}
	
	
	
	
}
}





ISR(USART_RX_vect)
{
	receivedChar = UDR0; // Almacena el carácter recibido
	
	while(!(UCSR0A & (1<<UDRE0)));    //Mientras haya caracteres
	UDR0 = receivedChar;
}