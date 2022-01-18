/*
 * Timer1.h
 *
 * Created: 16/06/2018 10:35:37
 *  Author: yann_
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_
 
 #include <avr/io.h>
 #include <avr/interrupt.h> // Da wir einen Interrupt auslösen wollen.
 
 // Declarationen der Funktionen 
 
 void Timer1_Init(void);
 unsigned char Timer1_get_100msState(void);
 #define TIMER_RUNNING 0
 #define TIMER_TRIGGERED 1




#endif /* TIMER1_H_ */