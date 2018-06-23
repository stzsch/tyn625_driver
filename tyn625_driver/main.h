/*
 * main.h
 *
 * Created: 07/06/2018 11:21:47
 *  Author: Douglas
 */ 

#pragma once
#include <avr/io.h>


// enum para as possibilidades de cada tensão linha em seu semiciclo correspondente. AC, BA, CB?
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

// enum para sequência de fase
typedef enum _sequence
{
	CLOCKWISE,
	COUNTER_CLOCKWISE,
} sequence; 

/* Variáveis globais para compartilhar estado entre main e ISRs */

volatile uint16_t pot_adc; // não precisa ser global mas ehh

// Variável de acionamento dos scr
volatile trigger_states scr_trigger;

// Variáveis de estado dos optos
volatile uint8_t current_opto1;
volatile uint8_t current_opto2;
volatile uint8_t current_opto3;

volatile uint8_t last_opto1;
volatile uint8_t last_opto2;
volatile uint8_t last_opto3;

// Variável de sequência de fase
volatile sequence phase_sequence;

// Variáveis de flag para timers
volatile uint8_t timer0_flag;
volatile uint8_t timer1_flag;
volatile uint8_t timer2_flag;

inline void clock_setup(void)
{
	// caso o clock seja 16 MHz, divisor de 2 para todo o Atmega
	CLKPR=0x80;
	CLKPR=0x01;
}
