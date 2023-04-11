/*
 * File:   Keypad.c
 * Author: TOKA
 *
 * Created on March 20, 2023, 7:58 PM
 */


#define F_CPU 16000000UL
#include"Keypad.h"
#include<util/delay.h>
#include <stdlib.h>

void connect_pullup (char PortName , char PinNum , char connect_pullup)
{
    switch(PortName){

        case PA:
            if (connect_pullup == 1) {
                setpinIN(SFIOR, PUD);
                setpinIN(PA, PinNum);
                setpin(PA, PinNum);
            } else {
                resetpin(PA, PinNum);
            }
            break;
        case PB:
            if (connect_pullup == 1) {
                setpinIN(SFIOR, PUD);
                setpinIN(PB, PinNum);
                setpin(PB, PinNum);
            } else {
                resetpin(PB, PinNum);
            }
            break;
        case PC:
            if (connect_pullup == 1) {
                setpinIN(SFIOR, PUD);
                setpinIN(PC, PinNum);
                setpin(PC, PinNum);
            } else {
                resetpin(PC, PinNum);
            }
            break;
        case PD:
            if (connect_pullup == 1) {
                setpinIN(SFIOR, PUD);
                setpinIN(PD, PinNum);
                setpin(PD, PinNum);
            } else {
                resetpin(PD, PinNum);
            }
            break;
    }
}



void keypad_init()
{
    // Set Ports as output
    setpinOUT(keypad_out_port,keypad_First_Pin );
    setpinOUT(keypad_out_port,keypad_second_Pin);
    setpinOUT(keypad_out_port,keypad_Third_Pin);
    setpinOUT(keypad_out_port,keypad_Fourth_Pin);
    
    // Set Ports as Input
    
    setpinIN(keypad_in_port,keypad_Fifth_Pin);
    setpinIN(keypad_in_port,keypad_sixth_Pin);
    setpinIN(keypad_in_port,keypad_Seventh_Pin);
    setpinIN(keypad_in_port,keypad_Eighth_Pin);
    
    // SET CONNECT PULL_UP
    // set coln as input (high 0xff by default)
    connect_pullup(keypad_in_port,keypad_Fifth_Pin,1);
    connect_pullup(keypad_in_port,keypad_sixth_Pin,1);
    connect_pullup(keypad_in_port,keypad_Seventh_Pin,1);
    connect_pullup(keypad_in_port,keypad_Eighth_Pin,1);
    
}

char Keypad_CheckPress()
{
    char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}}; //keypad buttons
    char row; //which indicate the given output  pin
	char coloumn; //which indicate the given input pin
	char key_pressed_indicator; //the variable  which contain the key pressed
    
    char returnval = NOT_PRESSED; //the variable contain the value which will be returned which will be key pressed or not pressed in case of no key pressed
    
    for(row=0;row<4;row++)
	{
		/*stop the work of keypad firstly*/
        setpin(keypad_out_port,keypad_First_Pin );
        setpin(keypad_out_port,keypad_second_Pin);
        setpin(keypad_out_port,keypad_Third_Pin);
        setpin(keypad_out_port,keypad_Fourth_Pin);
		
		/*************************************/
        _delay_ms(20); 
        
        resetpin(keypad_out_port,row);  //write 0 to the first pin in keypad (output pin from MC)
        for(coloumn=0 ; coloumn<4; coloumn++)
		{
			key_pressed_indicator=readPin(keypad_in_port ,(coloumn+4)); // read the input pins of MC which connected to keypad
			if(key_pressed_indicator == 0)// will be 0 only if any key pressed
			{
				returnval = arr[row][coloumn]; //put the selected pressed key to the returnval
				break ; // break from the loop
			}
		}
	}
    return returnval ; //return the pressed key in case of key pressed or return 0xff in case of no key pressed
}

    

