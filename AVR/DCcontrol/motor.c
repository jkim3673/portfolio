/*
 * motor.c
 *
 * Created: 2022-04-19 오전 10:34:53
 *  Author: user
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"

void motor_Init(void) {
	DDRB |= 0x0D;
	DDRD |= 0x68;
	
	TCCR0A |= (1<<WGM01) | (1<<WGM00);
	TCCR0B |= (1<<WGM02);
	TCCR0A |= (1<<COM0A1);
	TCCR0B |= (1<<CS02);
	TCCR2A |= (1<<WGM21) | (1<<WGM20);
	TCCR2B |= (1<<WGM22);
	TCCR2A |= (1<<COM2A1);
	TCCR2B |= (1<<CS22);
}

void motor_Go(void) {
	PORTB &= ~(1<<PINB2);
	PORTD &= ~(1<<PIND6);
	
	PORTB |= (1<<PINB2);
	PORTD |= (1<<PIND6);
	for (int i = 0; i < 256; i++) {
		OCR0A = i;
		OCR2A = i;
		_delay_ms(25);
	}
	OCR2A |= 0;
	OCR0A |= 0;
	_delay_ms(1000);
}

void motor_Left(void) {
	PORTB &= ~(1<<PINB2);
	//PORTD &= ~0x04;
	
	PORTB |= (1<<PINB2);
	OCR2A |= 127;
	//for (int i = 0; i < 256; i++) {
		//OCR2A = i;
		//_delay_ms(25);
	//}
	//PORTD |= 0x20;
	//OCR0A |= 0;
	_delay_ms(1000);
}

void motor_Right(void) {
	//PORTB &= ~0x04;
	PORTD &= ~(1<<PIND6);
	
	//PORTB &= ~0x02;
	//OCR0A |= 0;

	PORTD |= (1<<PIND6);
	OCR0A |= 127;
	_delay_ms(1000);
}

void motor_Stop(void) {
	PORTB |= (1<<PINB2);
	PORTD |= (1<<PIND6);
	OCR0A |= 0;
	OCR2A |= 0;
	_delay_ms(1000);
}