/*
 * timer.h
 *
 * Created: 07/06/2018 13:19:39
 *  Author: Douglas
 */ 

#pragma once

/*
Cada disparo é realizado sempre no ponto de comutação natural 30 graus (de 60 Hz) após o início do respectivo semiciclo.

Estes 30 graus, em milissegundos, equivalem a
30/360 * 1/60 = 1.3888... 


Como o ponto de comutação natural é 60 graus do ponto de vista da tensão de linha, o valor de alpha pode variar de 0 a 120 graus, resultando em um disparo que ocorre entre 30 graus a 150 graus do início do semiciclo

150 graus em segundos:
150/360 * 1/60 = 6.9444...


O clock externo utilizado é de 16 MHz, com um divisor de 2, resultando em 8 MHz
O timer está configurado para um prescaler de 256, resultando em uma  frequência de 8MHz / 256 = 31.250 KHz de contagem
Nesta frequência, o tempo para overflow dos 8 bits de contagem é:
256 / 31250 = 8.16 ms

Resultando portanto em uma boa relação de precisão no timing, trabalhando dentro da faixa desejada.
Realizando a conversão dos tempos de disparo para contagens do timer, temos

Tempo mínimo de disparo (alpha = 0): 1.3888... --> 43.4 contagens
Tempo máximo de disparo (alpha = 120): 6.9444... --> 217.01 contagens

O valor que indica qual o valor de alpha vem dos 10 bits do adc (1024 valores), portanto:

0V pot --> adc 0	--> 43 contagens
5V pot --> adc 1024 -->	43 + 174 = 217 contagens

Desta forma, o valor inicial de 43 é fixo (MAGIC_OPTO) e pode ser ajustado (reduzido), caso haja delay nos optos.

A segunda parcela, de 174, é obtida direto do adc. Uma divisão simples equivale a:

1024 / 174 = 5.88

Aproximando para 6 para evitar floats:

1024 / 6 = 170

Estes 4 representam um erro de pelo menos 128 us no valor máximo de alpha, porém garante que sempre estará disparando no semiciclo correto.

*/

/* Constantes mágicas de timer */
 
#define MAGIC_OPTO1_POS	43
#define MAGIC_OPTO1_NEG	43
#define MAGIC_OPTO2_POS	43
#define MAGIC_OPTO2_NEG	43
#define MAGIC_OPTO3_POS	43
#define MAGIC_OPTO3_NEG	43

/* Funções relacionadas ao uso dos timers */

/* Funções Timer 0 */
void timer0_setup(void);
void timer0_start(void);
void timer0_stop(void);
void timer0_reset(void);

/* Funções Timer 1 */
void timer1_setup(void);
void timer1_start(void);
void timer1_stop(void);
void timer1_reset(void);

/* Funções Timer 2 */
void timer2_setup(void);
void timer2_start(void);
void timer2_stop(void);
void timer2_reset(void);