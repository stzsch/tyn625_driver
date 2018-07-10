/*
 * adc.c
 *
 * Created: 23/06/2018 12:52:02
 *  Author: Douglas
 */ 

#include <avr/io.h>
#include "adc.h"

void adc_setup(void)
{
	/* Sele��o de modo de tens�o de refer�ncia. */
	ADMUX |= (1 << REFS0); // Utiliza Avcc como refer�ncia
	
	/* Sele��o das portas ligadas ao mux */
	//ADMUX |= (1 << MUX1); // ADC2
	
	/* Setup do prescaler, deve estar entre 50 KHz e 200 KHz */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // Para 8 MHz, um divisor de 64 gera 125 KHz
	
	/* Seleciona modo de funcionamento do ADC. */
	//ADCSRA |= (1 << ADATE); // Ativa auto trigger do ADC
	//ADCSRB = 0x00; // Modo Free Running
	
	/* Ativa o ADC */
	ADCSRA |= (1 << ADEN);

	/* Inicia a primeira convers�o em modo Free Running */
	//ADCSRA |= (1 << ADSC);
}


uint16_t adc_read(uint8_t adc_pin) {
	// sele��o do pino no mux do adc
	ADMUX	&=	0xF0;
	ADMUX	|=	adc_pin;

	// inicia a convers�o
	ADCSRA |=  (1 << ADSC);

	// loop para aguardar o fim da convers�o
	while ( (ADCSRA & (1 << ADSC)) );

	return ADC;
}