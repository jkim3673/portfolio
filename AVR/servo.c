/*
 * servo.c
 *
 * Created: 2022-04-20 오후 2:17:32
 *  Author: user
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "servo.h"

void INIT_TIMER1(void)
{
	// fast PWM 모드, TOP = ICR1
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	TCCR1B |= (1<<CS11);
	
	ICR1 = 40000;
	
	TCCR1A |= (1<<COM1A1);
	DDRB |= (1<<PINB3);
}