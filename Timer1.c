/*
 * Timer1.c
 *
 * Created: 16/06/2018 10:40:46
 *  Author: yann_
 */ 

#include "Timer1.h" // Bindet unsere Timer header Datei in dem Code ein


unsigned char ucTimer1_10msFlag=0; //Wird 1 wenn 10ms verstrichen sind.
unsigned char ucTimer1_100msFlag=0; //wird 1 wenn 100ms verstrichen sind.
unsigned char ucTimer1_100msCnt=0; // zählt die 1 bis 100ms

// Initialisierung Der Timer

void Timer1_Init(void)

{
	TCCR1B =(1<<CS11);//Prescaler=64
	TCCR1B |=1<<WGM12; // CTC Mode
	OCR1A = 23039; // 28800 in Compare Register
	TIMSK1 |=1<<OCIE1A; // Freigabe des Time Interrupts
	
	sei(); // Freigabe alle Interrupts
}

ISR (TIMER1_COMPA_vect) // Interrupt Service Routine

{
	// Nach 10ms startet der ucTimer1_100msCnt 
	ucTimer1_10msFlag=1; 
	ucTimer1_100msCnt++;
	
	//ucTimer1_100msCnt Zählt dann bis 10 und das sind dann 100ms
	if (ucTimer1_100msCnt==10)
	{
		ucTimer1_100msFlag=1;
		//ucTimer1_100msCnt wieder auf 0 setzen
		ucTimer1_100msCnt=0;
	}
	
}

unsigned char Timer1_get_100msState(void) // Sagt uns ob 100ms Vorbei sind 
{
	
	if (ucTimer1_100msFlag==1) 
	{
		// Flag wieder auf 0 setzen für nähste runde
		ucTimer1_100msFlag=0; 
		//100ms sind verstrichen
		return TIMER_TRIGGERED;
	}
	//100ms sind noch nicht vorbei
	else return TIMER_RUNNING;
}


