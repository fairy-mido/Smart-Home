/* 
 * File:   Keypad.h
 * Author: TOKA
 *
 * Created on March 20, 2023, 7:57 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H
#include<xc.h>

#define pass_size            4
#define NOT_STORED          0xFF
#define NOT_PRESSED         0xFF

#define keypad_out_port      PB
#define keypad_in_port       PB
#define keypad_First_Pin     PB0   
#define keypad_second_Pin    PB1  
#define keypad_Third_Pin     PB2  
#define keypad_Fourth_Pin    PB3  
#define keypad_Fifth_Pin     PB4  
#define keypad_sixth_Pin     PB5  
#define keypad_Seventh_Pin   PB6  
#define keypad_Eighth_Pin    PB7  



void connect_pullup (char PortName , char PinNum , char connect_pullup);
void keypad_init();
char Keypad_CheckPress();
void press_action();
//void login_pass();
int login_user_pass();
void updated_press_action();
void lcd_choices_display();
#endif	/* KEYPAD_H */

