/*
 * motor1.h
 *
 * Created: 2022-05-17 오후 4:03:48
 *  Author: user
 */ 


#ifndef MOTOR1_H_
#define MOTOR1_H_

void MotorInit();
void MotorGo(int pwm);
void MotorStop();
void MotorLeft(int pwm);
void MotorRight(int pwm);

#endif /* MOTOR1_H_ */