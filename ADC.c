/*
 * ADC.c
 *
 * Created: 02/06/2018 10:06:24
 *  Author: yann_
 */ 

#include "ADC.h" // Bindet unsere ADC header Datei in dem Code ein

unsigned int uiResult; //Result der Messung
unsigned char ucADC_Flag=0;// Wird 1 wenn die Umwandlung fertig wird.

void ADC_Init()    //Initialisierung der ADC wandler

{
	ADMUX = (1 << REFS0);	//5v ist die Referenzspannungsquelle

	ADMUX |=(1<<MUX2);// Analog eingang PC4
    ADCSRA |=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);// Prescaler =128
	ADCSRA|=1<<ADEN; // ADC Enable
	ADCSRA|=1<<ADSC; // Start der 1.Umwandlung
	
	while(ADCSRA&(1<<ADSC));//Warten auf das Ende der Umwandlung
	
	ADCSRA|=1<<ADIE; // Interrupt Freigabe.
	
	sei(); //Freigabe alle interrupts
}

  ISR(ADC_vect) // Interrupt Service Routine
{
	uiResult=ADC; // Result in 8bit Speicher stellen
	ucADC_Flag=1;
}
 
void ADC_Start(void)
{
	//die Messung am gewünschten Kanal wird gestartet
	ADCSRA |= (1 << ADSC);	
}

// Prüfen ob die Umwandlung Fertig ist
unsigned char ADC_get_State(void) 
{
	if (ucADC_Flag==1)
	{
		ucADC_Flag=0;
		//Die Umwandlung ist Fertig 
		return ADC_FINISHED; 
	}
	else 
	{   //Die Umwandlung ist noch nicht fertig
		return ADC_RUNNING;
	}
}

unsigned int ADC_get_Result(void) // Liefert uns das Messwert
{
	//Result der Umwandlung
	return uiResult;
} 


