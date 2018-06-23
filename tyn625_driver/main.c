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
	gpio_setup();
	adc_setup();
	timer0_setup();
	timer1_setup();
	timer2_setup();
	sei(); // inicializa interrupções
	
	
	// Definição das globais
	pot_adc = 0;
	
	current_opto1 = 0;
	current_opto2 = 0;
	current_opto3 = 0;
	
	last_opto1 = 0;
	last_opto2 = 0;
	last_opto3 = 0;
	
	timer0_flag = 1;
	timer1_flag = 1;
	timer2_flag = 1;

	phase_sequence = CLOCKWISE;
	
    while (1) 
    {		
		// Lê os valores dos pinos e inverte, dado que o sinal é 0 para ciclo positivo e 1 para ciclo negativo
		current_opto1 = !(PINB & (1 << 3));
		current_opto2 = !(PINB & (1 << 2));
		current_opto3 = !(PINB & (1 << 1));
		
		// if para detecção de borda da entrada, com flag de timer para garantia contra ruído
		if ( (current_opto1 == 1) && (last_opto1 == 0) && (timer0_flag))
		{
			// Atualiza valor anterior do opto
			last_opto1 = current_opto1;
				
			// A verificação da sequência de fase somente é realizada na borda de subida do opto 1.
			// Na sequência de fase normal, opto2 deve ser 1 e opto 3 deve ser 0.
			// se opto2 estiver zero a sequência é invertida
			phase_sequence = (current_opto2 == 0) ? COUNTER_CLOCKWISE : CLOCKWISE;
			
			// Aquisição do valor do ADC
			pot_adc = adc_read(ADC_PIN);
				
			// Setar compare do timer.
			// A constante MAGIC é dependente do delay do opto em relação à fase e deve ser manualmente ajustada (timer.h)
			// A divisão por 6 é uma aproximação para evitar uso de floats.
			OCR0A = MAGIC_OPTO1_POS + pot_adc/6;
			
			// Inicia timer
			timer0_reset();
			timer0_flag = 0; // Com a flag em zero não é possível modificar o timer até a interrupção.
			timer0_start();
		}

		// OPTO 1 NEGATIVO
		if ( (current_opto1 == 0) && (last_opto1 == 1) && (timer0_flag) )
		{
			last_opto1 = current_opto1;
			pot_adc = adc_read(ADC_PIN);
			OCR0A = MAGIC_OPTO1_NEG + pot_adc/6;
			timer0_reset();
			timer0_flag = 0;
			timer0_start();
		}
		
		// OPTO 2 POSITIVO
		if ( (current_opto2 == 1) && (last_opto2 == 0) && (timer1_flag) )
		{
			last_opto2 = current_opto2;
			pot_adc = adc_read(ADC_PIN);
			OCR1A = MAGIC_OPTO2_POS + pot_adc/6;
			timer1_reset();
			timer1_flag = 0;
			timer1_start();
		}
		
		// OPTO 2 NEGATIVO
		if ( (current_opto2 == 0) && (last_opto2 == 1) && (timer1_flag) )
		{
			last_opto2 = current_opto2;
			pot_adc = adc_read(ADC_PIN);
			OCR1A = MAGIC_OPTO2_NEG + pot_adc/6;
			timer1_reset();
			timer1_flag = 0;
			timer1_start();
		}
		
		// OPTO 3 POSITIVO
		if ( (current_opto3 == 1) && (last_opto3 == 0) && (timer2_flag) )
		{
			last_opto3 = current_opto3;
			pot_adc = adc_read(ADC_PIN);
			OCR2A = MAGIC_OPTO3_POS + pot_adc/6;
			timer2_reset();
			timer2_flag = 0;
			timer2_start();
		}
		
		// OPTO 3 NEGATIVO
		if ( (current_opto3 == 0) && (last_opto3 == 1) && (timer2_flag) )
		{
			last_opto3 = current_opto3;
			pot_adc = adc_read(ADC_PIN);
			OCR2A = MAGIC_OPTO3_NEG + pot_adc/6;
			timer2_reset();
			timer2_flag = 0;
			timer2_start();
		}
		
		
		// Switch de gatilhamento, o valor de scr_trigger é alterado nas ISR
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

