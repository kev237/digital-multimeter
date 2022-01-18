/*
 * UART.c
 *
 * Created: 20/06/2018 08:25:36
 *  Author: yann_
 */ 

#include "UART.h" // Bindet unsere UART header Datei in dem Code ein


unsigned char ucData; // Datei Zum Abschiken
unsigned char ucUART_Flag=0; // Wird nach dem Lesen auf 1 gesetzt

void UART_Init(void) // Initialisierung Von UART
{
	
	
   /*RXEN0: schaltet den Empfang frei ein
	TXEN0: schaltet das Senden frei
	RXCIE0: schaltet den interrupt beim Empfang frei*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
  
	
	// 8 Daten Bits, Keine Parität , 1Stoppbit
	UCSR0C=(1<<UCSZ00)|(1<<UCSZ01); 
	
	//9600 Bit/S @ f=18432MHz
	UBRR0=119;
	//Freigabe alle Interrupts
	sei();
}

ISR(USART_RX_vect) // Interrupt Service Routine
{
	//Das empfangene Byte wird aus dem Empfangs register gelesen
	ucData=UDR0;
	//Nach dem Lesen wird unsere Flag auf 1 gesetzt
	ucUART_Flag=1;
}

unsigned char UART_get_State(void) 
{
	// nach dem lesen aus dem empfangs register wird unsere ucUART_Flag wieder auf 0 gesetzt 
	if (ucUART_Flag==1)
	{
		ucUART_Flag=0;
		
		// Der Datei wurde schon gelesen
		return UART_RECIEVED;
	}
	 // Wenn der Datei noch nicht gelesen ist wartet noch Uart
	return UART_WAITING;
}

unsigned char UART_get_Value(void)
{
	// unsere Datei wird ausgegeben
	return ucData;
}

void UART_TX(unsigned char ucData)
{
	//	Warten bis der Sendpuffer leer ist
	
	while (!(UCSR0A&(1<<UDRE0)));
	//und abschicken
	UDR0=ucData;
}