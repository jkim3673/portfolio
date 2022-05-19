


/*
 * main.c
 *
 * Created: 2022-05-03 오후 1:46:55
 *  Author: user
 */ 

//#define F_CPU 16000000L
//#include <avr/io.h>
//#include <util/delay.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "uart.h"
//
//#define ROTATION_DELAY 	1500
//#define PULSE_00		1200
//#define PULSE_45		2100
//#define PULSE_90		3150
//#define PULSE_135		4000
//#define PULSE_180		5000
//
//void INIT_TIMER1(void)
//{
	//DDRB |= 0x0F; // 모터 제어를 위한 핀들을 출력으로 설정
	//DDRD |= 0x68; // 모터 제어를 위한 핀들을 출력으로 설정
	//
	//// Fast PWM 모드, TOP = ICR1
	//TCCR1A |= (1 << WGM11);
	//TCCR1B |= (1 << WGM12) | (1 << WGM13);
	//TCCR1B |= (1 << CS11);		// 분주율 8, 2MHz
	//TCCR1A |= (1 << COM1A1);	// 비반전 모드
	//ICR1 = 40000;				// 20ms 주기
	//
	//
	//// 타이머/카운터 2번을 고속 PWM 모드로 설정
	//TCCR2A |= (1 << WGM21) | (1 << WGM20);
	//TCCR2A |= (1 << COM2A1); // 비반전 모드
	//TCCR2B |= (1 << CS22); // 분주비 64
	//PORTB |= 0x04; // 초기 상태는 비활성화 상태
	//
	//// 타이머/카운터 0번을 고속 PWM 모드로 설정
	//TCCR0A |= (1 << WGM01) | (1 << WGM00);
	//TCCR0A |= (1 << COM0A1); // 비반전 모드
	//TCCR0B |= (1 << CS02); // 분주비 64
	//PORTD |= 0x40; // 초기 상태는 비활성화 상태
//}
//
//int main(void)
//{
	//int index = 0;			// 수신 버퍼에 저장할 위치
	//char buffer[20] = "";	// 수신 데이터 버퍼
	//char data;				// 수신 데이터
	//
	//UART_INIT();			// UART 통신 초기화
	//INIT_TIMER1();
	//
	//while(1)
	//{
		//data = UART_receive();	// 데이터 수신
		//buffer[index] = data;
		//
		//if(strcmp(buffer, "q") == 0){
			//OCR1A = PULSE_00;
			//PORTB &= ~0x04; // 모터 1 활성화
			//PORTD &= ~0x40; // 모터 2 활성화
			//OCR0A = 128;
			//OCR2A = 128;
			//UART_transmit(data);
			//OCR0A = 0; // 모터1 정지
			//OCR2A = 0; // 모터2 정지
			//PORTB |= 0x04; // 모터 1 비활성화
			//PORTB |= 0x40; // 모터 2 비활성화
			//index = 0;
		//}
		//else if(strcmp(buffer, "w") == 0){
			//OCR1A = PULSE_45;
			//PORTB &= ~0x04; // 모터 1 활성화
			//PORTD &= ~0x40; // 모터 2 활성화
			//OCR0A = 128;
			//OCR2A = 0;
			//UART_transmit(data);
			//OCR0A = 0; // 모터1 정지
			//OCR2A = 0; // 모터2 정지
			//PORTB |= 0x04; // 모터 1 비활성화
			//PORTB |= 0x40; // 모터 2 비활성화
			//index = 0;
		//}
		//else if(strcmp(buffer, "e") == 0){
			//OCR1A = PULSE_90;
			//PORTB &= ~0x04; // 모터 1 활성화
			//PORTD &= ~0x40; // 모터 2 활성화
			//OCR0A = 0;
			//OCR2A = 128;
			//UART_transmit(data);
			//OCR0A = 0; // 모터1 정지
			//OCR2A = 0; // 모터2 정지
			//PORTB |= 0x04; // 모터 1 비활성화
			//PORTB |= 0x40; // 모터 2 비활성화
			//index = 0;
		//}
		//else if(strcmp(buffer, "r") == 0){
			//OCR1A = PULSE_135;
			//PORTB &= ~0x04; // 모터 1 활성화
			//PORTD &= ~0x40; // 모터 2 활성화
			//OCR0A = 0;
			//OCR2A = 0;
			//UART_transmit(data);
			//OCR0A = 0; // 모터1 정지
			//OCR2A = 0; // 모터2 정지
			//PORTB |= 0x04; // 모터 1 비활성화
			//PORTB |= 0x40; // 모터 2 비활성화
			//index = 0;
		//}
		//else if(strcmp(buffer, "t") == 0){
			//OCR1A = PULSE_180;
			//UART_transmit(data);
			//index = 0;
		//}
		//else{
			//UART_transmit(data);
		//}
	//}
//}