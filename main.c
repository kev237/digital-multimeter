/*
 * Projekt_DigitalesVoltmeter.c
 *
 * Created: 20/06/2018 12:04:17
 * Author : yann_
 */ 

#include <avr/io.h>
#include "Timer1.h" // Bindet unsere Timer header Datei in dem Code ein.
#include "ADC.h"    // Bindet unsere ADC header Datei in dem Code ein.
#include "display_funktionen.h" // Bindet unsere Display header Datei in dem Code ein.
#include "UART.h"    // Bindet unsere UART header Datei in dem Code ein.
  



int main(void)
{
	//Initialisierung der Aufgerufene Funktionen.
	Timer1_Init();    
	UART_Init();      
	ADC_Init();
	Display_Init();
	
	//Unsere Gemessene Wert vom TYP Long(4Byte=32Bit) wird hier gespeichert in der Variable "Value".
	unsigned long Value;
	
	//Unsere gemessene Spannung wird in diesem Char gespeichert um auf dem Display anzuzeigen [0,000V].
	unsigned char  uctext[7];
	
	
	uctext[1]=','; // Stelle 2 wird immer ein koma sein.
	uctext[5]='V'; // Stelle 6 wird immer V für Volt anzeigen.
	uctext[6]=' '; // Stelle 7 wird ein leer Zeichen.
	
	// Unsere Cursor wird auf erste Zeile und erste Spalte gestellt
	Display_SetCursor(0,0);
	 // Die Umwandlung wird Gestartet sicher
	ADC_Start();
	
     // in While schleife damit das Programm immer laüft
    while (1)  
    {
		//Wenn 100ms verstrichen sind
		if (Timer1_get_100msState()==TIMER_TRIGGERED)
		{
			//ADC wird jedes 100ms gestartet.
			ADC_Start();
		}
		
		  // Wenn die Umwandlung fertig ist 
		  if (ADC_get_State()==ADC_FINISHED)
		  {
			  // Hier wird der Result in die Variable Value gespeichert
			  Value= ADC_get_Result();
			   // Cursor nochmal gesetzt
			  Display_SetCursor(0,0);
			  
			  // Rechnungen : Da der ADC eine 10Bit Auflösung hat,Hat der ausgelesene Wert das verhältnis Value= (uiResult*Referenzapannung)/1023.
			                     
			  Value = Value*5000;	//Unsere Referenz Spannung ist 5V, um die Berechnung einfacher für mich zu machen habe ich Spannung*1000(in mV ) Berechnet
			  Value=Value/1023;        // Wichtig ist erst Multiplizieren und dann Dividieren sonst kriegt mann immer 0,000V angezeigt
			  
			  // Um es klar zu Machen; Habe ich ein Spannung Von um Beispiel 1234mV Zerlege ich es so dass ich dann 1,234V habe um es in Volt anzuzeigen
			  //Durch das Modulo(%) nehme ich nur den Rest der Division.
			  
			   uctext[4]=Value%10 +48; // Nach der beispiel kommt hier mein "4" auf Stelle 5 Von mein ucText.
			   
			   Value=Value/10;         // Hier wird 1234 durch 10 gemacht so dass ich jetzt 123 habe.
			   uctext[3]=Value%10 +48; // Nach der beispiel kommt hier mein "3" auf Stelle 4 Von mein ucText.
			   
			   Value=Value/10;         // Hier wird 123 durch 10 gemacht so dass ich jetzt 12 habe.
			   uctext[2]=Value%10 +48; // Nach der beispiel kommt hier mein "2" auf Stelle 3 Von mein ucText.
			   
			   Value=Value/10;         // Hier wird 12 durch 10 gemacht so dass ich jetzt 1 habe. 
			   uctext[0]=Value%10 +48; // Nach der beispiel kommt hier mein "1" auf Stelle 1 Von mein ucText.
			  
			  // Anzeige der gemessene wert auf dem Display in der Form (0,000V)
			 Display_Print(uctext,7);
			 
			 // Übertragung der gemessene Wert im PC über UART 
			  for (uint8_t i=0; i<7; i++) // uint8_t : unsigned char
			 
			 {  //Jeder Stelle der Variable ucText wird übertragen
				 UART_TX(uctext[i]);
			 }
			 
			 // Sende der neue Zeile befehl
			 UART_TX('\n');
			 
			
			  }
			  
		
		
    }
  
}

