/*
 * timer.h
 *
 * Created: 07/06/2018 13:19:39
 *  Author: Douglas
 */ 

#pragma once
#include <avr/io.h>

/*
180 graus 60 Hz --> 260 contagens clock 8 MHz / 256

alpha deve variar de 0 a 120 graus

60 graus --> 87 contagens
120 graus --> 173 contagens


alpha é obtido do potenciômetro, que varia de 0V a 5V com 10 bits, portanto 1024 valores

0V --> adc 0 --> 	60 graus (magic, até 87) + alpha 0 graus (0 contagens)
5V --> adc 1024 -->	60 graus (magic, até 87) + alpha 120 graus (173 contagens)



PROBLEMA: soma 260
solução --> diminuir constante mágica inicial em 5: para 82
resultado: caso o opto seja muito rápido, dispararia antes do ponto de comutação natural

PROBLEMA: divisão máxima do 1024 para chegar perto do 173 é por 6, resultando em 170
solução --> como já remove 3, daria pra diminuir a diminuição da cte mágica para 85
resultado: caso não modifique a constante, não dispararia em 180 graus
solução 2 --> pode-se colocar um if para o caso acima de 1020 (170x6) para não disparar (saída zero)
*/

    
/* Timers:
	Cada timer é associado a um opto diferente:
	- TC0 --> OPTO1
	- TC1 --> OPTO2
	- TC2 --> OPTO3
*/
	

/* Constantes mágicas de timer */
 
#define MAGIC_OPTO1_POS	82
#define MAGIC_OPTO1_NEG	82
#define MAGIC_OPTO2_POS	82
#define MAGIC_OPTO2_NEG	82
#define MAGIC_OPTO3_POS	82
#define MAGIC_OPTO3_NEG	82

/* Funções relacionadas ao uso dos timers */

/* Funções Timer 0 */
static inline void timer0_setup(void)
{
	TIMSK0 |= (1 << OCIE0A); // ativar interrupt do output compare 0A
}
static inline void timer0_start(void)
{
	TCCR0B |= (1 << CS02); // ativar timer com prescaler 256
}
static inline void timer0_stop(void)
{
	TCCR0B &= ~(1 << CS02); // desativar timer
}
static inline void timer0_set(uint8_t value)
{
	TCNT0 = value;
}
static inline void timer0_reset(void)
{
	TCNT0 = 0;
}

/* Funções Timer 1 */
static inline void timer1_setup(void)
{
	TIMSK1 |= (1 << OCIE1A);
}
static inline void timer1_start(void)
{
	TCCR1B |= (1 << CS12); // ativar timer com prescaler 256
}
static inline void timer1_stop(void)
{
	TCCR0B &= ~(1 << CS12); // desativar timer
}
static inline void timer1_set(uint8_t value) // somente os 8 lower bits
{
	TCNT1L = value;
}
static inline void timer1_reset(void)
{
	TCNT1H = 0;
	TCNT1L = 0;
}

/* Funções Timer 2 */
static inline void timer2_setup(void)
{
	TIMSK2 |= (1 << OCIE2A);
}
static inline void timer2_start(void)
{
	TCCR2B |= (1 << CS22) | (1 << CS21);
}
static inline void timer2_stop(void)
{
	TCCR2B &= ~(1 << CS22) | (1 << CS21);
}
static inline void timer2_set(uint8_t value)
{
	TCNT2 = value;
}
static inline void timer2_reset(void)
{
	TCNT2 = 0;
}
