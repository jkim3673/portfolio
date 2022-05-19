#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#define ROTATION_DELAY	1000  // 1초 대기
#define PULSE_MIN		1300  // 최소 펄스 길이
#define PULSE_MID		3000
#define PULSE_MAX		4700  // 최대 펄스 길이

void INIT_TIMER1(void)
{
	// fast PWM 모드, TOP = ICR1
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	TCCR1B |= (1<<CS11);
	
	ICR1 = 40000;
	
	TCCR1A |= (1<<COM1A1);
	DDRB |= (1<<PINB1);
}

void Uart_Init(void)
{
	UCSR0A |= (1<<U2X0);
	
	UBRR0H |= 0x00;
	UBRR0L = 207;
	
	UCSR0C |= 0x06;
	
	UCSR0B |= (1<<RXEN0);
	UCSR0B |= (1<<TXEN0);
	
}

void Uart_TX(unsigned char data)
{
	while( !( UCSR0A & (1 << UDRE0) ) ); // 통신이 준비되면
	
	UDR0 = data; // 데이터 송신
}


unsigned char Uart_RX(void)
{
	while( !( UCSR0A & (1 << RXC0) ) );
	
	return UDR0;
}

int main(void)

{
	unsigned char data;
	
	Uart_Init();
	INIT_TIMER1();
	data = Uart_RX();
	
	while (1) 
	{	
		switch(data)
		{
			case 'a':
			{
				OCR1A = PULSE_MIN;			// 0도
				_delay_ms(ROTATION_DELAY);
				break;
			}
			case 'b':
			{
				OCR1A = PULSE_MID;			// 90도
				_delay_ms(ROTATION_DELAY);
				break;
			}
			case 'c':
			{
				OCR1A = PULSE_MAX;			// 180도
				_delay_ms(ROTATION_DELAY);
				break;
			}
			case 'd': break;
			default: break;
		}
	}
	
	return 0;
}