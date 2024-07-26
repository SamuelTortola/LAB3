//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Electrónica digital 2
// Autor: Samuel Tortola - 22094
// Proyecto: Laboratorio 3
// Hardware: Atmega238p
// Creado: 26/07/2024
//Última modificación: 26/07/2024
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



uint8_t activa = 0, caso = 0, Val1 = 0, Val2 = 0;
volatile char receivedChar = 0;    //Variable que almacena el valor del UART

int millares = 0;
int centenas = 0;
int decenas = 0;
int unidades = 0;


char lista[10] = {'0','1','2','3','4','5','6','7','8','9'}; //Lista de numeros a mostrar



void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	DDRD = 0xFF;  //Puerto D como salida
	DDRB = 0xFF;  //Puerto B como salida
	DDRC = 0;  //Puerto C como entrada
	UCSR0B = 0;  //Usar los pines TX y RX como digitales
	
	
	initADC(); //Iniciar ADC
	initUART9600();  //Iniciar UART
	
	sei(); //Activar interrupciones
}


int main(void)
{
	setup();
	
	while (1)
	{
		
		ADCSRA |=(1<<ADSC);  //Leer ADC
		
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
	
	if(receivedChar != 0){      //Si la variable que hay en USART es diferente de cero
		switch(receivedChar)   //Switch para elegir que se desea, si pot o ASCII
		{
			case '1':
			writeTextUART("\n\r------------------------------------------\n\r");
			writeTextUART("Lectura actual de potenciometro es:");
			
			
		
			
			
			//Obtener el dato del potenciometro descompuesto
			 millares = Val1/1000;
			 centenas = (Val1-(millares*1000))/100;
			 decenas = (Val1- (millares*1000 + centenas*100))/10;
			 unidades = Val1-(millares*1000 + centenas*100 + decenas*10);
			
			
			switch(centenas){   //Mostrar centenas
				case 0:
				writeUART(lista[0]);
				break;
				
				
				case 1:
				writeUART(lista[1]);
				break;
				
				case 2:
				writeUART(lista[2]);
				break;
				
				
				case 3:
				writeUART(lista[3]);
				break;
				
				case 4:
				writeUART(lista[4]);
				break;
				
				
				case 5:
				writeUART(lista[5]);
				break;
				
				
				case 6:
				writeUART(lista[6]);
				break;
				
				
				case 7:
				writeUART(lista[7]);
				break;
				
				case 8:
				writeUART(lista[8]);
				break;
				
				
				case 9:
				writeUART(lista[9]);
				break;
				
			}
			
			
			switch(decenas){   //Mostrar decenas
				case 0:
				writeUART(lista[0]);
				break;
				
				
				case 1:
				writeUART(lista[1]);
				break;
				
				case 2:
				writeUART(lista[2]);
				break;
				
				
				case 3:
				writeUART(lista[3]);
				break;
				
				case 4:
				writeUART(lista[4]);
				break;
				
				
				case 5:
				writeUART(lista[5]);
				break;
				
				
				case 6:
				writeUART(lista[6]);
				break;
				
				
				case 7:
				writeUART(lista[7]);
				break;
				
				case 8:
				writeUART(lista[8]);
				break;
				
				
				case 9:
				writeUART(lista[9]);
				break;
				
			}
			
			switch(unidades){   //Mostrar unidades
				case 0:
				writeUART(lista[0]);
				break;
				
				
				case 1:
				writeUART(lista[1]);
				break;
				
				case 2:
				writeUART(lista[2]);
				break;
				
				
				case 3:
				writeUART(lista[3]);
				break;
				
				case 4:
				writeUART(lista[4]);
				break;
				
				
				case 5:
				writeUART(lista[5]);
				break;
				
				
				case 6:
				writeUART(lista[6]);
				break;
				
				
				case 7:
				writeUART(lista[7]);
				break;
				
				case 8:
				writeUART(lista[8]);
				break;
				
				
				case 9:
				writeUART(lista[9]);
				break;
				
			}
			
			activa = 0;   //Ingresar a menu principal
			receivedChar  = 0;    //Salir del if
			writeTextUART("\n\r------------------------------------------\n\r");
			break;
			
			case '2':
			receivedChar = 0;  //Por si se desea colocar un valor en UART
			writeTextUART("\n\rIngrese un valor\n\r");
			break;
			
		}
	}
	
	
	
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



ISR(USART_RX_vect)
{
	receivedChar = UDR0; // Almacena el carácter recibido
	
	while(!(UCSR0A & (1<<UDRE0)));    //Mientras haya caracteres
	UDR0 = receivedChar;
}