
#include <xc.h>
#include <avr/interrupt.h>

#include "mTimer.h"


void Timer0_select_CLK(char Clock_Select) {

    // TCCR0
    TCCR0 &= 0xF8; // 11111000
    TCCR0 |= Clock_Select;
}

void Timer0_select_Mode(char Timer0_mode) {
    switch (Timer0_mode) {

        case Timer0_Normal:// (WGM01 = 0, WGM00 = 0)
            TCCR0 &= ~(1 << WGM00);
            TCCR0 &= ~(1 << WGM01);
            break;
        case Timer0_CTC: // (WGM01 = 1, WGM00 = 0)
            TCCR0 &= ~(1 << WGM00);
            TCCR0 |= (1 << WGM01);
            break;
        case Timer0_PWM: // (WGM01 = 0, WGM00 = 1)
            TCCR0 |= (1 << WGM00);
            TCCR0 &= ~(1 << WGM01);
            break;
        case Timer0_FPWM:// (WGM01 = 1, WGM00 = 1)
            TCCR0 |= (1 << WGM00);
            TCCR0 |= (1 << WGM01);
            break;
        default:
            // None
            break;
    }
}

void Timer0_enable_OVIE(){
    TIMSK |= (1<<TOIE0);
}
void Timer0_enable_OCIE(){
    TIMSK |= (1<<OCIE0);
}

void Timer0_select_OC0_mode(char Timer0_OC0_mode){
    TCCR0 &= 0xCF;  // 11001111
    TCCR0 |= (Timer0_OC0_mode<<COM00);
}

void Timer0_set_DutyCycle(char DutyCycle_percentage){
    // DutyCycle = t1/t2*100 %   , t1-> High period, t2 -> Total period
    // DutyCycle = OCR0/255*100 %
    
    OCR0 = (100-DutyCycle_percentage)*255.0/100.0;
    
    
    
}

void init_Timer0(
        char Timer0_mode,   // nlknlkclkcne
        char Timer0_OC0_mode,  //kenlkenklfe
        char Timer0_OC0_DutyCycle,   // DutyCycle 0-100%, in case of (PWM or FPWM Only).
        char Timer0_Prescalar // 
        ){
    
    Timer0_select_Mode(Timer0_mode);
    Timer0_select_OC0_mode(Timer0_OC0_mode);
    if(Timer0_mode == Timer0_FPWM || Timer0_mode == Timer0_PWM){
    Timer0_set_DutyCycle(Timer0_OC0_DutyCycle);
    }
    Timer0_select_CLK(Timer0_Prescalar);
    
}

void PWM_init()
{
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);  /*set OC0 pin as output*/
}


