
#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

#define DC_Motor_1 1
#define DC_Motor_2 2

#define ON                      1
#define OFF                     0

#define H_A1   PA0
#define H_A2   PA1
#define H_A3   PA2
#define H_A4   PA3
#define H_EN1  PD4
#define H_EN2  PC1

void init_Motor();
void Motor_Forward();
void Motor_Reverse();
void Motor_stop();

#endif	/* DC_MOTOR_H */

