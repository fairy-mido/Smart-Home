/* 
 * File:   Lamps.h
 * Author: TOKA
 *
 * Created on March 24, 2023, 3:46 PM
 */

#ifndef LAMPS_H
#define	LAMPS_H

#define LED1_PORT   PC
#define LED2_PORT   PC
#define LED3_PORT   PC
#define LED4_PORT   PD
#define LED5_PORT   PD

#define LED1   PC2  // 2
#define LED2   PC3  // 7
#define LED3   PC4  // 3
#define LED4   PD6
#define LED5   PD5 

#define ALL_LEDs  10



// LEDS functions
void init_LEDs();
void LED_on(char LED_number);
void LED_off(char LED_number);




#endif	/* LAMPS_H */

