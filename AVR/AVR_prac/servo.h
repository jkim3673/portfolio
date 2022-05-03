/*
 * servo.h
 *
 * Created: 2022-04-20 오후 3:59:27
 *  Author: user
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#define ROTATION_DELAY	1000  // 1초 대기
#define PULSE_MIN		1300  // 최소 펄스 길이
#define PULSE_MID		3000
#define PULSE_MAX		4700  // 최대 펄스 길이

void INIT_TIMER1(void);

#endif /* SERVO_H_ */