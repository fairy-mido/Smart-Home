#define F_CPU 16000000UL
#include <xc.h>
#include "DIO.h"
#include "mkit.h"
#include "DC_Motor.h"
#include <stdlib.h>
#include <util/delay.h>


void init_Motor(char Motor_No)
{
    if(Motor_No == DC_Motor_1)
    {
        setpinOUT(PC,H_A3);
        setpinOUT(PC,H_A4);
        setpinOUT(PD,H_EN1);
        // Set pin on in the enable
        setpin(PD,H_EN1);
    }
    else if(Motor_No == DC_Motor_2)
    {
        setpinOUT(PC,H_A1);
        setpinOUT(PC,H_A2);
        setpinOUT(PD,H_EN2);
        // Set pin on in the enable
        setpin(PD,H_EN2); 
    }
}
void Motor_Forward(char Motor_No)
{
    if(Motor_No == DC_Motor_1)
    {
        setpin(PC,H_A3);
        resetpin(PC,H_A4);
    }
    else if(Motor_No == DC_Motor_2)
    {
        setpin(PC,H_A1);
        resetpin(PC,H_A2);
    }
}

void Motor_Reverse(char Motor_No)
{
    if(Motor_No == DC_Motor_1)
    {
        resetpin(PC,H_A3);
        setpin(PC,H_A4);
    }
    else if(Motor_No == DC_Motor_2)
    {
        resetpin(PC,H_A1);
        setpin(PC,H_A2);
    }
}

void Motor_stop(char Motor_No)
{
    if(Motor_No == DC_Motor_1)
    {
        resetpin(PC,H_A3);
        resetpin(PC,H_A4);
        resetpin(PC,H_EN1);
    }
    else if(Motor_No == DC_Motor_2)
    {
        resetpin(PC,H_A1);
        resetpin(PC,H_A2);
        resetpin(PC,H_EN2);
    }
}

