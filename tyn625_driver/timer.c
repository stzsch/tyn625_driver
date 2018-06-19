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


/* Interrupções dos comparadores dos timers */
ISR(TIMER0_COMPA_vect)
{
	timer0_stop();
	if (last_state_opto1)
	{
		// semiciclo positivo fase a
		if (phase_sequence_opto1 == CLOCKWISE)
		{
			// ordem de fase normal
			scr_trigger = TRIGGER_15;
		}
		else if (phase_sequence_opto1 == COUNTER_CLOCKWISE)
		{
			// ordem de fase trocada
			scr_trigger = TRIGGER_16;
		}
	} 
	else
	{
		// semiciclo positivo fase a
		if (phase_sequence_opto1 == CLOCKWISE)
		{
			// ordem de fase normal
			scr_trigger = TRIGGER_24;
		}
		else if (phase_sequence_opto1 == COUNTER_CLOCKWISE)
		{
			// ordem de fase trocada
			scr_trigger = TRIGGER_34;
		}		
	}
	// des-setar a flag de timer
	timer0_flag = 0;
}

ISR(TIMER1_COMPA_vect)
{
	timer1_stop();
	if (last_state_opto2)
	{
		// semiciclo positivo fase b
		if (phase_sequence_opto2 == CLOCKWISE)
		{
			// ordem de fase normal
			scr_trigger = TRIGGER_26;
		}
		else if (phase_sequence_opto2 == COUNTER_CLOCKWISE)
		{
			// ordem de fase trocada
			scr_trigger = TRIGGER_24;
		}
	}
	else
	{
		// semiciclo positivo fase b
		if (phase_sequence_opto2 == CLOCKWISE)
		{
			// ordem de fase normal
			scr_trigger = TRIGGER_35;
		}
		else if (phase_sequence_opto2 == COUNTER_CLOCKWISE)
		{
			// ordem de fase trocada
			scr_trigger = TRIGGER_15;
		}
	}
	// des-setar a flag de timer
	timer1_flag = 0;
}

ISR(TIMER2_COMPA_vect)
{
		
	timer2_stop();
	if (last_state_opto3)
	{
		// semiciclo positivo fase c
		if (phase_sequence_opto2 == CLOCKWISE)
		{
			// ordem de fase normal
			scr_trigger = TRIGGER_34;
		}
		else if (phase_sequence_opto2 == COUNTER_CLOCKWISE)
		{
			// ordem de fase trocada
			scr_trigger = TRIGGER_35;
		}
	}
	else
	{
		// semiciclo positivo fase c
		if (phase_sequence_opto2 == CLOCKWISE)
		{
			// ordem de fase normal
			scr_trigger = TRIGGER_16;
		}
		else if (phase_sequence_opto2 == COUNTER_CLOCKWISE)
		{
			// ordem de fase trocada
			scr_trigger = TRIGGER_26;
		}
	}
	// des-setar a flag de timer
	timer2_flag = 0;
}
