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
	int index = 0;			// 수신 버퍼에 저장할 위치
	char buffer[20] = "";	// 수신 데이터 버퍼
	char data;				// 수신 데이터
	
	UART_INIT();			// UART 통신 초기화
	MotorInit();			// 주행 모터 초기화
	
	while(1) {
		
		data = UART_receive();	// 데이터 수신
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
			UART_INIT();			// UART 통신 초기화
			_delay_ms(200);
			MotorInit();			// 주행 모터 초기화
			_delay_ms(200);
		}
	}
	
	return 0;
}
