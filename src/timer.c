/*
 * timer.c
 *
 * Created: 07/06/2018 13:19:13
 *  Author: Douglas
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h"
#include "timer.h"


/* Funções Timer 0 */
void timer0_setup(void)
{
	TIMSK0 |= (1 << OCIE0A); // ativar interrupt do output compare 0A
}
void timer0_start(void)
{
	TCCR0B |= (1 << CS02); // ativar timer com prescaler 256
}
void timer0_stop(void)
{
	TCCR0B &= ~(1 << CS02); // desativar timer
}
void timer0_reset(void)
{
	TCNT0 = 0;
}

/* Funções Timer 1 */
void timer1_setup(void)
{
	TIMSK1 |= (1 << OCIE1A);
}
void timer1_start(void)
{
	TCCR1B |= (1 << CS12); // ativar timer com prescaler 256
}
void timer1_stop(void)
{
	TCCR1B &= ~(1 << CS12); // desativar timer
}
void timer1_reset(void)
{
	TCNT1H = 0;
	TCNT1L = 0;
}

/* Funções Timer 2 */
void timer2_setup(void)
{
	TIMSK2 |= (1 << OCIE2A);
}
void timer2_start(void)
{
	TCCR2B |= (1 << CS22) | (1 << CS21);
}
void timer2_stop(void)
{
	TCCR2B = 0;
}
void timer2_reset(void)
{
	TCNT2 = 0;
}


/* Interrupções dos comparadores dos timers */
ISR(TIMER0_COMPA_vect)
{
	timer0_flag = 1; // Reativa flag para possibilitar alterações do timer para o próximo semiciclo
	timer0_stop();
	
	if (last_opto1) // semiciclo positivo
	{
		//scr_trigger = (phase_sequence == COUNTER_CLOCKWISE) ? TRIGGER_16 : TRIGGER_15;
		scr_trigger = TRIGGER_15;
		
	}
	else			// semiciclo negativo
	{
		//scr_trigger = (phase_sequence == COUNTER_CLOCKWISE) ? TRIGGER_34 : TRIGGER_24;
		scr_trigger = TRIGGER_24;
	}
	
}

ISR(TIMER1_COMPA_vect)
{
	timer1_flag = 1; 
	timer1_stop();
	
	if (last_opto2) // semiciclo positivo
	{
		//scr_trigger = (phase_sequence == COUNTER_CLOCKWISE) ? TRIGGER_35 : TRIGGER_34;
		scr_trigger = TRIGGER_26;
		
	}
	else			// semiciclo negativo
	{
		//scr_trigger = (phase_sequence == COUNTER_CLOCKWISE) ? TRIGGER_26 : TRIGGER_16;
		scr_trigger = TRIGGER_35;
	}

}

ISR(TIMER2_COMPA_vect)
{
	timer2_flag = 1; 
	timer2_stop();
	
	if (last_opto3) // semiciclo positivo
	{
		//scr_trigger = (phase_sequence == COUNTER_CLOCKWISE) ? TRIGGER_24 : TRIGGER_26;
		scr_trigger = TRIGGER_34;
		
	}
	else			// semiciclo negativo
	{
		//scr_trigger = (phase_sequence == COUNTER_CLOCKWISE) ? TRIGGER_15 : TRIGGER_35;
		scr_trigger = TRIGGER_16;
	}
	
}

