//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Electrónica digital 2
// Autor: Samuel Tortola - 22094
// Proyecto: Laboratorio 3
// Hardware: Atmega238p
// Creado: 26/07/2024
//Última modificación: 29/07/2024
//******************************************************************************
  //CODIGO DEL MAESTRO 
  
  
  /* Este programa consiste en utilizar 8 leds, conectados a los pines PD2 a PD7 y de PC0 a PC1, Estos lEDs son un contador de 8 bits, los cuales
  se pueden manipular desde una terminal abriendo el puerto COM, o usando la interfaz gráfica de python, tambien este programa tiene otro microcontrolador
  contralado con SPI, que lee el valor de dos potenciómetros conectados en PC0 y  PC1, igual se pueden observar abriendo en una terminal el puero COM o usando
  la interfaz gráfica de python */

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

int activa = 0, menu2 = 0, i = 0;
int cambio = 0, MAYOR = 0, MENOR  = 0, activa3 = 0, desactivador = 0;
volatile char receivedChar = 0;    //Variable que almacena el valor del UART

int lista1[] = {0,5,5}; //Lista de numeros a mostrar
	
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
		_delay_ms(5);
		if (receivedChar == 'R') //si se desea usar python, bloquear el acceso a UART normal
		{
			activa = 1;
		}
		
		if(activa == 0 && menu2 == 0){
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
		
		
			
		if (receivedChar !='c' && activa3 == 1)
		{
			
			
			switch(receivedChar){
				case '0': 
					lista1[i] = 0;
					break;
				case '1':
					lista1[i] = 1;
					break;
				case '2':
					lista1[i] = 2;
					break;
				case '3':
					lista1[i] = 3;
					break;
				case '4':
					lista1[i] = 4;
					break;
				case '5':
					lista1[i] = 5;
					break;
				case '6':
					lista1[i] = 6;
					break;
				case '7':
					lista1[i] = 7;
					break;
				case '8':
					lista1[i] = 8;
					break;
				case '9':
					lista1[i] = 9;
					break;
				
			}
			
			
				if (i >= 2)
				{
					int result = 0;

					for (int P = 0; P < 3; P++) {
						result = result * 10 + lista1[P];  // Construir el número
					}
					
					PORTD = result << 2;  //Mostrar el valor del contador, con corrimiento hacia la derecha, de dos bits, muestra los primeros 6 bits
					PORTC = result >> 6;   //Mostrar el valor del contador, con corrimiento hacia la izquierda, muestra los ultimos 2 bits
					i = 0;
					activa3 = 0;
				}
				

		    i++;
			receivedChar = 'c';
		
		}
		
		
		if(receivedChar != 0 && activa3 == 0){      //Si la variable que hay en USART es diferente de cero
			
			if (receivedChar == 'A') //Si se quiere enviar un valor directo al contador por python
			{
				activa3 = 1;
				receivedChar = 'c';
				i = 0;
			}
			
			
			
			if ((receivedChar == '1' && menu2 == 0) || receivedChar == 'Q')   //Si se quiere ver los potenciometros, Q es para usar la interfaz de python 
			{
				if (receivedChar == 'Q')
				{
					USANDOPYTHON(1);
				}
				else{
					USANDOPYTHON(0);
				}
			     
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