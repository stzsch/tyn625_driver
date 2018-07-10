/*
 * timer.h
 *
 * Created: 07/06/2018 13:19:39
 *  Author: Douglas
 */ 

#pragma once

/*
Cada disparo � realizado sempre no ponto de comuta��o natural 30 graus (de 60 Hz) ap�s o in�cio do respectivo semiciclo.

Estes 30 graus, em milissegundos, equivalem a
30/360 * 1/60 = 1.3888... 


Como o ponto de comuta��o natural � 60 graus do ponto de vista da tens�o de linha, o valor de alpha pode variar de 0 a 120 graus, resultando em um disparo que ocorre entre 30 graus a 150 graus do in�cio do semiciclo

150 graus em segundos:
150/360 * 1/60 = 6.9444...


O clock externo utilizado � de 16 MHz, com um divisor de 2, resultando em 8 MHz
O timer est� configurado para um prescaler de 256, resultando em uma  frequ�ncia de 8MHz / 256 = 31.250 KHz de contagem
Nesta frequ�ncia, o tempo para overflow dos 8 bits de contagem �:
256 / 31250 = 8.16 ms

Resultando portanto em uma boa rela��o de precis�o no timing, trabalhando dentro da faixa desejada.
Realizando a convers�o dos tempos de disparo para contagens do timer, temos

Tempo m�nimo de disparo (alpha = 0): 1.3888... --> 43.4 contagens
Tempo m�ximo de disparo (alpha = 120): 6.9444... --> 217.01 contagens

O valor que indica qual o valor de alpha vem dos 10 bits do adc (1024 valores), portanto:

0V pot --> adc 0	--> 43 contagens
5V pot --> adc 1024 -->	43 + 174 = 217 contagens

Desta forma, o valor inicial de 43 � fixo (MAGIC_OPTO) e pode ser ajustado (reduzido), caso haja delay nos optos.

A segunda parcela, de 174, � obtida direto do adc. Uma divis�o simples equivale a:

1024 / 174 = 5.88

Aproximando para 6 para evitar floats:

1024 / 6 = 170

Estes 4 representam um erro de pelo menos 128 us no valor m�ximo de alpha, por�m garante que sempre estar� disparando no semiciclo correto.

*/

/* Constantes m�gicas de timer */
 
#define MAGIC_OPTO1_POS	38
#define MAGIC_OPTO1_NEG	38
#define MAGIC_OPTO2_POS	38
#define MAGIC_OPTO2_NEG	38
#define MAGIC_OPTO3_POS	38
#define MAGIC_OPTO3_NEG	38

/* Fun��es relacionadas ao uso dos timers */

/* Fun��es Timer 0 */
void timer0_setup(void);
void timer0_start(void);
void timer0_stop(void);
void timer0_reset(void);

/* Fun��es Timer 1 */
void timer1_setup(void);
void timer1_start(void);
void timer1_stop(void);
void timer1_reset(void);

/* Fun��es Timer 2 */
void timer2_setup(void);
void timer2_start(void);
void timer2_stop(void);
void timer2_reset(void);