/* 
 * File:   DC_Motor.h
 * Author: moham
 *
 * Created on April 14, 2023, 2:53 PM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

void init_Motor(char Motor_No);
void Motor_Forward(char Motor_No);
void Motor_Reverse(char Motor_No);
void Motor_stop(char Motor_No);

#endif	/* DC_MOTOR_H */

