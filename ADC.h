/*
 * ADC.h
 *
 * Created: 02/06/2018 09:34:04
 *  Author: yann_
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_Init(void);

unsigned char ADC_get_State(void);
unsigned int ADC_get_Result(void);
void ADC_Start(void);



#define ADC_RUNNING 0
#define ADC_FINISHED 1






#endif /* ADC_H_ */