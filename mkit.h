/* 
 * File:   mkit.h
 * Author: moham
 *
 * Created on February 4, 2023, 9:52 AM
 */

#ifndef MKIT_H
#define	MKIT_H

// Master address to TWAR
#define Master_Address_without_GC  0x06
#define Master_Address_with_GC     0x07

// Address Assigned to TWDR 
#define SLA_R                      0x03
#define SLA_W                      0x02

// Address Assigned to TWAR
#define SAddress_without_GC   0x02 
#define SAddress_with_GC      0x03




#define Buzzer PA3
#define Relay  PA2
#define POT    PA1

#define LED0   PC2
#define LED1   PC7
#define LED2   PD3

#define BTN0   PB0
#define BTN1   PD6
#define BTN2   PD2



//Function Prototypes
void init_kit();
void init_Buzzer();
void Buzzer_on();
void Buzzer_off();
void init_Relay();
void Relay_on();
void Relay_off();
void init_POT();
void init_LEDs();
void LED_on(char LED_Number);
void LED_off(char LED_Number);
void init_BTNs();
char isPressed(char BTN_Number);

#endif	/* MKIT_H */

