/*
 * gpio.h
 *
 * Created: 11/06/2018 09:55:55
 *  Author: Douglas
 */ 

#pragma once
#include <avr/io.h>

/* Defines para pinos de entrada, dos optos e do pot*/

#define PORT_OPTO1	PORTB
#define PORT_OPTO2	PORTB
#define PORT_OPTO3	PORTB

#define PIN_OPTO1	PINB3
#define PIN_OPTO2	PINB2
#define PIN_OPTO3	PINB1

#define	ADC_PIN		2	

#define ADC_POT_H	ADCH
#define ADC_POT_L	ADCL

#define POT_DIVISOR	6


/* Defines para pinos de saída dos mocs */

#define DDR_MOC1	DDRD
#define DDR_MOC2	DDRD
#define DDR_MOC3	DDRC
#define DDR_MOC4	DDRD
#define DDR_MOC5	DDRD
#define DDR_MOC6	DDRC

#define PORT_MOC1	PORTD
#define PORT_MOC2	PORTD
#define PORT_MOC3	PORTC
#define PORT_MOC4	PORTD
#define PORT_MOC5	PORTD
#define PORT_MOC6	PORTC

#define PIN_MOC1	PORTD2
#define PIN_MOC2	PORTD0
#define PIN_MOC3	PORTC3
#define PIN_MOC4	PORTD3
#define PIN_MOC5	PORTD1
#define PIN_MOC6	PORTC4

#define MOC_SIGNAL_DURATION_US	50

inline void gpio_setup(void)
{
	// Configurar pinos dos MOCs como saídas
	DDR_MOC1 |= (1 << PIN_MOC1);
	DDR_MOC2 |= (1 << PIN_MOC2);
	DDR_MOC3 |= (1 << PIN_MOC3);
	DDR_MOC4 |= (1 << PIN_MOC4);
	DDR_MOC5 |= (1 << PIN_MOC5);
	DDR_MOC6 |= (1 << PIN_MOC6);
	
	DDRB = 0x00;
	// PORTB |= (1 << PORTB1);
	// PORTB |= (1 << PORTB2);
	// PORTB |= (1 << PORTB3);
}

