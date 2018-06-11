/*
 * main.h
 *
 * Created: 07/06/2018 11:21:47
 *  Author: Douglas
 */ 

#pragma once
#include <avr/io.h>


// enum para as possibilidades de cada tens�o linha em seu semiciclo correspondente. AC, BA, CB?

typedef enum _trigger_states
{
	OFF = 0, 
	TRIGGER_15,
	TRIGGER_16,
	TRIGGER_26,
	TRIGGER_24,
	TRIGGER_34,
	TRIGGER_35,
} trigger_states;

// enum para sequ�ncia de fase
typedef enum _sequence
{
	CLOCKWISE,
	COUNTER_CLOCKWISE,
} sequence; 

/* Vari�veis globais para compartilhar estado entre main e ISRs */

// Vari�vel de acionamento dos scr
volatile trigger_states scr_trigger;

// Vari�veis de estado dos optos
volatile uint8_t last_state_opto1;
volatile uint8_t last_state_opto2;
volatile uint8_t last_state_opto3;

// Vari�veis de sequ�ncia de fase
volatile sequence phase_sequence_opto1;
volatile sequence phase_sequence_opto2;
volatile sequence phase_sequence_opto3;


static inline void clock_setup(void)
{
	// caso o clock seja 16 MHz, divisor de 2 para todo o Atmega
	CLKPR=0x80;
	CLKPR=0x01;

}
