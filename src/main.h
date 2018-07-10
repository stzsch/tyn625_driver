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

volatile uint16_t pot_adc; // n�o precisa ser global mas ehh

// Vari�vel de acionamento dos scr
volatile trigger_states scr_trigger;

// Vari�veis de estado dos optos
volatile uint8_t current_opto1;
volatile uint8_t current_opto2;
volatile uint8_t current_opto3;

volatile uint8_t last_opto1;
volatile uint8_t last_opto2;
volatile uint8_t last_opto3;

// Vari�vel de sequ�ncia de fase
volatile sequence phase_sequence;

// Vari�veis de flag para timers
volatile uint8_t timer0_flag;
volatile uint8_t timer1_flag;
volatile uint8_t timer2_flag;

void clock_setup(void);