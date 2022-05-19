#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "motor1.h"
#include "uart.h"

int main(void)
{
	int index = 0;			// ���� ���ۿ� ������ ��ġ
	char buffer[20] = "";	// ���� ������ ����
	char data;				// ���� ������
	
	UART_INIT();			// UART ��� �ʱ�ȭ
	MotorInit();			// ���� ���� �ʱ�ȭ
	
	while(1) {
		
		data = UART_receive();	// ������ ����
		buffer[index] = data;
		
		if(strcmp(buffer, "g") == 0){
			MotorGo(100);
			_delay_ms(1000);
			UART_transmit(data);
			index = 0;
			MotorStop();
		}
		
		else if(strcmp(buffer, "l") == 0){
			MotorLeft(100);
			_delay_ms(1000);
			UART_transmit(data);
			index = 0;
			MotorStop();
		}
		
		else if(strcmp(buffer, "r") == 0){
			MotorRight(100);
			_delay_ms(1000);
			UART_transmit(data);
			index = 0;
			MotorStop();
		}
		
		else if(strcmp(buffer, "s") == 0){
			MotorStop();
			UART_transmit(data);
			index = 0;
		}
		else {
			UART_INIT();			// UART ��� �ʱ�ȭ
			_delay_ms(200);
			MotorInit();			// ���� ���� �ʱ�ȭ
			_delay_ms(200);
		}
	}
	
	return 0;
}
