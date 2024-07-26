//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Electrónica digital 2
// Autor: Samuel Tortola - 22094
// Proyecto: Laboratorio 3
// Hardware: Atmega238p
// Creado: 26/07/2024
//Última modificación: 26/07/2024
//******************************************************************************
  //CODIGO DEL MAESTRO 

#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "UART/UART.h"
#include "SPI/SPI.h"
#include "POT/POT.h"

uint8_t datoRecibido = 0x00;

uint8_t activa = 0;
volatile char receivedChar = 0;    //Variable que almacena el valor del UART

void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	DDRD = 0xFF;  //Puerto D como salida
	DDRC = 0;  //Puerto C como entrada
	
	initUART9600();  //Iniciar UART
	SPI_init();
	

	
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
		
		if(receivedChar != 0){      //Si la variable que hay en USART es diferente de cero
			SPI_slaveON(2);
			SPI_tx(4);
			datoRecibido = SPI_rx();
			SPI_slaveOFF(2);
			
			if (datoRecibido >= 4)
			{
				writeTextUART("si funciona el escalavo");
			}
			//writeTextUART("888");
			
			receivedChar = 0;
    }
	
	

	
}
}


ISR(USART_RX_vect)
{
	receivedChar = UDR0; // Almacena el carácter recibido
	
	while(!(UCSR0A & (1<<UDRE0)));    //Mientras haya caracteres
	
}