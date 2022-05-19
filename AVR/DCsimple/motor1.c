/*
 * motor1.c
 *
 * Created: 2022-05-17 오후 4:03:35
 *  Author: user
 */ 
#include <avr/io.h>
#include "motor1.h"

void MotorInit(){
	
	DDRB |= 0x09;		// PB0, 3 OPEN
	DDRD |= 0xFC;		// PD2,3,4,5,6,7 OPEN
	
	TCCR0A = 0x83;		// Fast PWM & 비반전 모드 설정
	TCCR0B = 0x02;		// 분주비 64, 아날로그 0~255
	TCCR2A = 0x83;
	TCCR2B = 0x02;
	
	PORTD |= 0x68;		// PD3,5,6 - 모터1,2 PWM 비활성화
	PORTB |= 0x08;		// PB3 - 모터2 LPWM 비활성화
	
	PORTD &= ~0x94;		// PD2,4,7 - 모터1 L,REN, 모터2 REN 비활성화
	PORTB &= ~0x01;		// PB0 - 모터2 LEN 비활성화
}	

void MotorGo(int pwm){
	
	PORTD |= 0x94;		// PD2,4,7 - 모터1 L,REN, 모터2 REN 활성화
	PORTB |= 0x01;		// PB0 - 모터2 LEN 활성화
	
	PORTB &= ~0x08;		// PB3 - 모터1 LPWM 활성
	PORTD |= 0x08;		// PD3 - 모터1 RPWM 비활성
	OCR2A = pwm;		// 모터1 속도를 입력값으로 설정
	
	PORTD &= ~0x40;		// PD6 - 모터2 LPWM 활성
	PORTD |= 0x20;		// PD5 - 모터1 RPWM 비활성
	OCR0A = pwm;		// 모터2 속도를 입력값으로 설정
}

void MotorStop(){
	
	PORTB &= ~0x08;		// PB3 - 모터1 LPWM 활성
	OCR2A = 0;			// 모터1 속도를 0으로 설정
	
	PORTD &= ~0x40;		// PD6 - 모터2 LPWM 활성
	OCR0A = 0;			// 모터2 속도를 0으로 설정
	
	PORTD |= 0x68;		// PD3,5,6 - 모터1,2 PWM 비활성화
	PORTB |= 0x08;		// PB3 - 모터2 LPWM 비활성화
	
	PORTD &= ~0x94;		// PD2,4,7 - 모터1,2 EN 비활성화
	PORTB &= ~0x01;		// PB0 - 모터2 LEN 비활성화
}

void MotorLeft(int pwm){
	
	PORTD |= 0x80;		// PD7 - 모터2 REN 활성화
	PORTB |= 0x01;		// PB0 - 모터2 LEN 활성화
	
	PORTD &= ~0x40;		// PD6 - 모터2 LPWM 활성
	PORTD |= 0x20;		// PD5 - 모터2 RPWM 비활성
	OCR0A = pwm;		// 모터2 속도를 입력값으로 설정
}

void MotorRight(int pwm){
	
	PORTD |= 0x14;		// PD4, 2 - 모터1 LEN, REN 활성화
	
	PORTB &= ~0x08;		// PB3 - 모터1 LPWM 활성
	PORTD |= 0x08;		// PD3 - 모터1 RPWM 비활성
	OCR2A = pwm;		// 모터1 속도를 입력값으로 설정
}