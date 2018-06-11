/*
 * adc.h
 *
 * Created: 08/06/2018 10:52:18
 *  Author: Douglas
 */ 

#pragma once
#include "main.h"


static inline void adc_setup(void)
{
	/* Sele��o de modo de tens�o de refer�ncia. */
	ADMUX |= (1 << REFS0); // Utiliza Avcc como refer�ncia
	
	/* Sele��o das portas ligadas ao mux */
	ADMUX |= (1 << MUX1); // ADC2
	
	/* Setup do prescaler, deve estar entre 50 KHz e 200 KHz */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // Para 8 MHz, um divisor de 64 gera 125 KHz
	
	/* Seleciona modo de funcionamento do ADC. */
	ADCSRA |= (1 << ADATE); // Ativa auto trigger do ADC
	// ADCSRB &= ~(1 << ADTS2) & ~(1 << ADTS1) & ~(1 << ADTS0) & // Modo Free Running
	
	/* Ativa o ADC */
	ADCSRA |= (1 << ADEN);

	/* Inicia a primeira convers�o em modo Free Running */
	ADCSRA |= (1 << ADSC);
}
