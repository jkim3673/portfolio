/*
 * uart1.h
 *
 * Created: 2022-04-14 오후 12:25:14
 *  Author: user
 */ 

#include <avr/io.h>
#include <stdio.h>

#ifndef USART_H_
#define USART_H_

void Uart_Init(void);
void Uart_TX(unsigned char data);
//void Uart(int num);
//void Data_send(int data);
unsigned char Uart_RX(void);
//void Print_String(const char str[]);
//void Read_String(char str[], uint8_t length);

#endif /* USART_H_ */