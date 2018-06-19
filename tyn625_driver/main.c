/* SCR_driver
 * main.c
 *
 * Created: 06/06/2018 15:27:16
 * Author : Douglas
 */ 

#define	F_CPU	8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"
#include "timer.h"
#include "adc.h"
#include "gpio.h"

int main(void)
{
	clock_setup(); 
	adc_setup();
	gpio_setup();
	timer0_setup();
	timer1_setup();
	timer2_setup();

	volatile uint16_t pot_adc = 0;
	
	sei(); // inicializa interrup��es
	
	timer0_flag = 0;
	timer1_flag = 0;
	timer2_flag = 0;
	
    while (1) 
    {			
		if (1 & (PORT_OPTO1 >> PIN_OPTO1))
		{
				if ( (last_state_opto1 != 1) && (~timer0_flag) )
				{
					last_state_opto1 = 1; // muda estado utilizado para testar altera��es
					pot_adc = (ADC_POT_H << 8) | (ADC_POT_L << 0); // obt�m valor 10 bits do adc (necessita testar)
					OCR0A = MAGIC_OPTO1_POS + pot_adc / POT_DIVISOR; // seta o compare para o timer 0 
					if (!(1 & (PORT_OPTO2 >> PIN_OPTO2))) // teste para sequ�ncia de fase
					{
						// ordem de fase trocada
						phase_sequence_opto1 = COUNTER_CLOCKWISE;
					}
					else
					{
						//ordem de fase normal
						phase_sequence_opto1 = CLOCKWISE;
					}
					timer0_reset();
					timer0_flag = 1;
					timer0_start();
				}
		}
		else if (0 & (PORT_OPTO1 >> PIN_OPTO1))
		{
				if ( (last_state_opto1 != 0)  && (~timer0_flag) )
				{
					last_state_opto1 = 0; // muda estado utilizado para testar altera��es
					pot_adc = (ADC_POT_H << 8) | (ADC_POT_L << 0); // obt�m valor 10 bits do adc (necessita testar)
					OCR0A = MAGIC_OPTO1_NEG + pot_adc / POT_DIVISOR; // seta o compare para o timer 0
					if (!(1 & (PORT_OPTO3 >> PIN_OPTO3)))
					{
						// ordem de fase trocada
						phase_sequence_opto1 = COUNTER_CLOCKWISE;
					}
					else
					{
						//ordem de fase normal
						phase_sequence_opto1 = CLOCKWISE;
					}
					timer0_reset();
					timer0_flag = 1;
					timer0_start();
				}
		}
		
		if (1 & (PORT_OPTO2 >> PIN_OPTO2))
		{
			if ( (last_state_opto2 != 1)  && (~timer1_flag)  )
			{
				last_state_opto2 = 1; // muda estado utilizado para testar altera��es
				pot_adc = (ADC_POT_H << 8) | (ADC_POT_L << 0); // obt�m valor 10 bits do adc (necessita testar)
				OCR1AL = MAGIC_OPTO2_POS + pot_adc / POT_DIVISOR; // seta o compare para o timer 0
				if (!(1 & (PORT_OPTO3 >> PIN_OPTO3))) // teste para sequ�ncia de fase
				{
					// ordem de fase trocada
					phase_sequence_opto2 = COUNTER_CLOCKWISE;
				}
				else
				{
					//ordem de fase normal
					phase_sequence_opto2 = CLOCKWISE;
				}
				timer1_reset();
				timer1_flag = 1;
				timer1_start();
			}
		}
		else if (0 & (PORT_OPTO2 >> PIN_OPTO2))
		{
			if ( (last_state_opto2 != 0)  && (~timer1_flag) )
			{
				last_state_opto2 = 0; // muda estado utilizado para testar altera��es
				pot_adc = (ADC_POT_H << 8) | (ADC_POT_L << 0); // obt�m valor 10 bits do adc (necessita testar)
				OCR1AL = MAGIC_OPTO2_NEG + pot_adc / POT_DIVISOR; // seta o compare para o timer 0
				if (!(1 & (PORT_OPTO1 >> PIN_OPTO1))) // teste para sequ�ncia de fase
				{
					// ordem de fase trocada
					phase_sequence_opto2 = COUNTER_CLOCKWISE;
				}
				else
				{
					//ordem de fase normal
					phase_sequence_opto2 = CLOCKWISE;
				}
				timer1_reset();
				timer1_flag = 1;
				timer1_start();
			}
		}
		
		
		if (1 & (PORT_OPTO3 >> PIN_OPTO3))
		{
			if ( (last_state_opto3 != 1)  && (~timer2_flag) )
			{
				last_state_opto3 = 1; // muda estado utilizado para testar altera��es
				pot_adc = (ADC_POT_H << 8) | (ADC_POT_L << 0); // obt�m valor 10 bits do adc (necessita testar)
				OCR2A = MAGIC_OPTO3_POS + pot_adc / POT_DIVISOR; // seta o compare para o timer 0
				if (!(1 & (PORT_OPTO1 >> PIN_OPTO1))) // teste para sequ�ncia de fase
				{
					// ordem de fase trocada
					phase_sequence_opto3 = COUNTER_CLOCKWISE;
				}
				else
				{
					//ordem de fase normal
					phase_sequence_opto3 = CLOCKWISE;
				}
				timer2_reset();
				timer2_flag = 1;
				timer2_start();
			}
		}
		else if (0 & (PORT_OPTO3 >> PIN_OPTO3))
		{
			if ( (last_state_opto3 != 0)  && (~timer2_flag) )
			{
				last_state_opto3 = 0; // muda estado utilizado para testar altera��es
				pot_adc = (ADC_POT_H << 8) | (ADC_POT_L << 0); // obt�m valor 10 bits do adc (necessita testar)
				OCR2A = MAGIC_OPTO3_NEG + pot_adc / POT_DIVISOR; // seta o compare para o timer 0
				if (!(1 & (PORT_OPTO2 >> PIN_OPTO2))) // teste para sequ�ncia de fase
				{
					// ordem de fase trocada
					phase_sequence_opto3 = COUNTER_CLOCKWISE;
				}
				else
				{
					//ordem de fase normal
					phase_sequence_opto3 = CLOCKWISE;
				}
				timer2_reset();
				timer2_flag = 1;
				timer2_start();
			}
		}
		

		switch (scr_trigger)
		{
			case TRIGGER_15:
			PORT_MOC1 |= (1 << PIN_MOC1); // setar pino moc
			PORT_MOC5 |= (1 << PIN_MOC5); // setar pino moc
			_delay_us(MOC_SIGNAL_DURATION_US); // delay 50 us
			PORT_MOC1 &= ~(1 << PIN_MOC1); // des setar pino
			PORT_MOC5 &= ~(1 << PIN_MOC5); // des setar pino
			scr_trigger = OFF;	// setar estado trigger de volta para OFF
			break;
			
			case TRIGGER_16:
			PORT_MOC1 |= (1 << PIN_MOC1); // setar pino moc
			PORT_MOC6 |= (1 << PIN_MOC6); // setar pino moc
			_delay_us(MOC_SIGNAL_DURATION_US); // delay 50 us
			PORT_MOC1 &= ~(1 << PIN_MOC1); // des setar pino
			PORT_MOC6 &= ~(1 << PIN_MOC6); // des setar pino
			scr_trigger = OFF;	// setar estado trigger de volta para OFF
			break;
			
			case TRIGGER_26:
			PORT_MOC2 |= (1 << PIN_MOC2); // setar pino moc
			PORT_MOC5 |= (1 << PIN_MOC5); // setar pino moc
			_delay_us(MOC_SIGNAL_DURATION_US); // delay 50 us
			PORT_MOC2 &= ~(1 << PIN_MOC2); // des setar pino
			PORT_MOC5 &= ~(1 << PIN_MOC5); // des setar pino
			scr_trigger = OFF;	// setar estado trigger de volta para OFF
			break;
			
			case TRIGGER_24:
			PORT_MOC2 |= (1 << PIN_MOC2); // setar pino moc
			PORT_MOC4 |= (1 << PIN_MOC4); // setar pino moc
			_delay_us(MOC_SIGNAL_DURATION_US); // delay 50 us
			PORT_MOC2 &= ~(1 << PIN_MOC2); // des setar pino
			PORT_MOC4 &= ~(1 << PIN_MOC4); // des setar pino
			scr_trigger = OFF;	// setar estado trigger de volta para OFF
			break;
			
			case TRIGGER_34:
			PORT_MOC3 |= (1 << PIN_MOC3); // setar pino moc
			PORT_MOC4 |= (1 << PIN_MOC4); // setar pino moc
			_delay_us(MOC_SIGNAL_DURATION_US); // delay 50 us
			PORT_MOC3 &= ~(1 << PIN_MOC3); // des setar pino
			PORT_MOC4 &= ~(1 << PIN_MOC4); // des setar pino
			scr_trigger = OFF;	// setar estado trigger de volta para OFF
			break;
			
			case TRIGGER_35:
			PORT_MOC3 |= (1 << PIN_MOC3); // setar pino moc
			PORT_MOC5 |= (1 << PIN_MOC5); // setar pino moc
			_delay_us(MOC_SIGNAL_DURATION_US); // delay 50 us
			PORT_MOC3 &= ~(1 << PIN_MOC3); // des setar pino
			PORT_MOC5 &= ~(1 << PIN_MOC5); // des setar pino
			scr_trigger = OFF;	// setar estado trigger de volta para OFF
			break;
			
			default:
			break;
			
		}
		
    }
}

