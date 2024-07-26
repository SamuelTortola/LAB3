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

uint8_t datoRecibido1 = 0x00;
uint8_t datoRecibido2 = 0x00;

uint8_t activa = 0, menu2 = 0;
int cambio = 0, MAYOR = 0, MENOR  = 0;
volatile char receivedChar = 0;    //Variable que almacena el valor del UART

	
void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	DDRD = 0xFF;  //Puerto D como salida
	DDRC = 0x03;  //Puerto C como salida 
	
	initUART9600();  //Iniciar UART
	SPI_init();
	

	PORTD = 0x00;
	sei(); //Activar interrupciones
}




int main(void)
{
   setup();
   
    while (1) 
    {
		
		if(activa == 0 && menu2 ==0){
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
			if (receivedChar == '1' && menu2 == 0)
			{
			     
				SPI_slaveON(2);
				SPI_tx(1);
				datoRecibido1 = SPI_rx();
				SPI_slaveOFF(2);
				
				
				SPI_slaveON(2);
				SPI_tx(2);
				datoRecibido2 = SPI_rx();
				SPI_slaveOFF(2);			
						
			 POT(datoRecibido1, datoRecibido2);
		
				receivedChar = 0;
			}
			
			
			if (receivedChar == '2' ){   //Si se elige modificar el valor del contador
				menu2 = 1;
				writeTextUART("Presione + para incrementar, - para decrementar, e para menu principal \n\r");
				writeUART(10);
				writeUART(13);
				writeUART(10);
				writeUART(13);
				
				receivedChar = 0;
			}
			
			if (receivedChar == '+' && menu2 == 1){
				cambio ++;
				if (cambio >= 255)    //si el contador es mayor de 255, dejarlo en 255
				{
					cambio = 255;
				}
				CONTA(cambio);
				
				
				PORTD = cambio << 2;  //Mostrar el valor del contador, con corrimiento hacia la derecha, de dos bits, muestra los primeros 6 bits
				PORTC = cambio >>6;   //Mostrar el valor del contador, con corrimiento hacia la izquierda, muestra los ultimos 2 bits
				receivedChar = 0;
				 
			}
			
			if (receivedChar == '-' && menu2 == 1){
				cambio --;
				
				if (cambio <= 0)    //si el contador es mayor de 255, dejarlo en 255
				{
					cambio = 0;
				}
				CONTA(cambio);
				PORTD = cambio << 2;  //Mostrar el valor del contador, con corrimiento hacia la derecha, de dos bits, muestra los primeros 6 bits
				PORTC = cambio >>6;   //Mostrar el valor del contador, con corrimiento hacia la izquierda, muestra los ultimos 2 bits
				receivedChar = 0;
				
			}
			
			if (receivedChar == 'e')
			{
				receivedChar = 0;
				menu2 = 0;
				activa = 0;
				writeUART(10);  //Enviar un enter
				writeUART(10);  //Enviar un enter
				writeUART(10);  //Enviar un enter
				writeUART(10);  //Enviar un enter
				writeUART(10);  //Enviar un enter
			}
		}
    
	
	

	
}
}


ISR(USART_RX_vect)
{
	receivedChar = UDR0; // Almacena el carácter recibido
	
	while(!(UCSR0A & (1<<UDRE0)));    //Mientras haya caracteres
	
}