/*
 * File:   servo.c
 * Author: Kimo Store
 *
 * Created on March 23, 2023, 1:25 PM
 */


#define F_CPU 16000000UL
#include <xc.h>
#include <util/delay.h>
#include "DIO.h"
#include "servo.h"

void servo_init()
{

    
    setpinOUT(PD,7);
    _delay_ms(50);

    
    TCCR2=0b01111101;
    OCR2 = 67;
}

void servo_open()
{
    OCR2 = 0;
}

void servo_close()
{
 
    OCR2 = 67;
}