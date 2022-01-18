/*
 * UART.h
 *
 * Created: 20/06/2018 08:20:13
 *  Author: yann_
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h> 

void UART_Init(void);
void UART_TX(unsigned char ucData);

unsigned char UART_get_State(void);
unsigned char UART_get_Value(void);

#define UART_WAITING 0
#define UART_RECIEVED 1



#endif /* UART_H_ */