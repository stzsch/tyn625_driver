
#include <avr/io.h>
#include "gpio.h"


void gpio_setup(void)
{
	// Configurar pinos dos MOCs como sa�das
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

