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


alpha � obtido do potenci�metro, que varia de 0V a 5V com 10 bits, portanto 1024 valores

0V --> adc 0 --> 	60 graus (magic, at� 87) + alpha 0 graus (0 contagens)
5V --> adc 1024 -->	60 graus (magic, at� 87) + alpha 120 graus (173 contagens)



PROBLEMA: soma 260
solu��o --> diminuir constante m�gica inicial em 5: para 82
resultado: caso o opto seja muito r�pido, dispararia antes do ponto de comuta��o natural

PROBLEMA: divis�o m�xima do 1024 para chegar perto do 173 � por 6, resultando em 170
solu��o --> como j� remove 3, daria pra diminuir a diminui��o da cte m�gica para 85
resultado: caso n�o modifique a constante, n�o dispararia em 180 graus
solu��o 2 --> pode-se colocar um if para o caso acima de 1020 (170x6) para n�o disparar (sa�da zero)
*/

    
/* Timers:
	Cada timer � associado a um opto diferente:
	- TC0 --> OPTO1
	- TC1 --> OPTO2
	- TC2 --> OPTO3
*/
	

/* Constantes m�gicas de timer */
 
#define MAGIC_OPTO1_POS	82
#define MAGIC_OPTO1_NEG	82
#define MAGIC_OPTO2_POS	82
#define MAGIC_OPTO2_NEG	82
#define MAGIC_OPTO3_POS	82
#define MAGIC_OPTO3_NEG	82

/* Fun��es relacionadas ao uso dos timers */

/* Fun��es Timer 0 */
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

/* Fun��es Timer 1 */
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

/* Fun��es Timer 2 */
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
