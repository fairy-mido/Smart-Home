/* 
 * File:   servo.h
 * Author: Kimo Store
 *
 * Created on March 23, 2023, 1:29 PM
 */

#ifndef SERVO_H
#define	SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif

void servo_init();
void servo_open();
void servo_close();

#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

