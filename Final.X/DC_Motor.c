#define F_CPU 16000000UL
#include <xc.h>
#include "DIO.h"
#include "DC_Motor.h"
#include <stdlib.h>
#include <util/delay.h>


void init_Motor()
{
    
        setpinOUT(PA,H_A3);
        setpinOUT(PA,H_A4);
        setpinOUT(PD,H_EN1);
        // Set pin on in the enable
        setpin(PD,H_EN1);
   
}
void Motor_Forward()
{
   
        setpin(PA,H_A3);
        resetpin(PA,H_A4);
    
}

void Motor_Reverse()
{
    
        resetpin(PA,H_A3);
        setpin(PA,H_A4);
    
}

void Motor_stop()
{
    
        resetpin(PA,H_A3);
        resetpin(PA,H_A4);
        resetpin(PC,H_EN1);
    
}

