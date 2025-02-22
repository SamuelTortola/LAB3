 #include "SPI.h"


void SPI_init()
{
	/*	Pines de la interface de comunicaci�n
		PB3: MOSI
		PB4: MISO
		PB5: SCK
	*/

	/*	Pines de control para esclavos
		PB2: Esclavo 1
	*/
	
	
	DDRB |= (1<<DDB4);  //MISO COMO SALIDA
	DDRB &= ~((1<<DDB2) | (1<<DDB3) | (1<<DDB5));   //SS, MOSI, and SCK OUTPUT in master mode

	/*	Orden de salida de los datos 
		DORD = 0, El bit m�s significativo (MSB) es enviado primero
		DORD = 1, El bit menos significativo (LSB) es enviado primero
	*/
	SPCR &=~ (1<<DORD);

	/*  Configuraci�n de polaridad y fase (Modo de comunicaci�n)
		 CPOL |  CPHA  |                           MODO	
		------|--------|---------------------------------------------------------------
		  0	  |   0    |  Clock inactivo en bajo, detecci�n de bits en flanco de subida
		  0	  |   1    |  Clock inactivo en bajo, detecci�n de bits en flanco de bajada
		  1	  |   0    |  Clock inactivo en alto, detecci�n de bits en flanco de bajada
		  1	  |   1    |  Clock inactivo en alto, detecci�n de bits en flanco de subida			
	*/
	SPCR &=~ (1<<CPOL);
	SPCR &=~ (1<<CPHA);

	/*	Pre-escalador  (Divisor de Frecuencia)
		SPI2X | SPR1 | SPR0 | Pre-escalador
		------|------|------|----------------
		0     | 0	 |	0	|	4
		0	  | 0	 |	1	|	16
		0	  | 1	 |	0	|	64
		0	  | 1	 |	1	|	128
		1	  | 0	 |	0	|	2
		1	  | 0	 |	1	|	8
		1	  | 1	 |	0	|	32
		1	  | 1	 |	1	|	64
		
		F_CPU=16MHz -> F_SPI= F_CPU/16= 1MHz		 
	*/
	SPCR |=  (1<<SPR0);
	SPCR &=~ (1<<SPR1);
	SPSR &=~ (1<<SPI2X);

	/*	Modo de funcionamiento 
		MSTR = 0, SPI como esclavo
		MSTR = 1; SPI como maestro
	*/
	SPCR &= ~(1<<MSTR);

	/* Activar SPI 
		SPE = 0, SPI desactivado
		SPE = |, SPI activado
	*/
	SPCR |= (1<<SPE);
}



	


