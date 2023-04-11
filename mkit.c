
#define F_CPU 16000000UL
#include <xc.h>
#include <util/delay.h>
#include "mkit.h"
#include "DIO.h"

void init_kit() {
    init_Buzzer();
    init_Relay();
    init_LEDs();
    init_BTNs();
    _delay_ms(20);
}

void init_Buzzer() {
    //IO Configuration
    setpinOUT(PA, Buzzer);
    //reset Buzzer
    Buzzer_off();
}

void Buzzer_on() {
    setpin(PA, Buzzer);
}

void Buzzer_off() {
    resetpin(PA, Buzzer);
}

void init_Relay() {
    //IO Configuration
    setpinOUT(PA, Relay);
    //Relay reset
    Relay_off();
}

void Relay_on() {
    setpin(PA, Relay);
}

void Relay_off() {
    resetpin(PA, Relay);
}

void init_POT()
{
    setpinIN(PA,POT);
    
}


void init_LEDs() {
    //IO Configuration
    setpinOUT(PC, LED0);
    setpinOUT(PC, LED1);
    setpinOUT(PD, LED2);
    
    //LEDs set
    /*LED_on(LED0);
    LED_on(LED1);
    LED_on(LED2);
    _delay_ms(20);
    // LEDs reset
    LED_off(LED0);
    LED_off(LED1);
    LED_off(LED2);
     */
}

void LED_on(char LED_Number) {
    switch (LED_Number) {
        case LED0:
            setpin(PC, LED0);
            break;
        case LED1:
            setpin(PC, LED1);
            break;
        case LED2:
            setpin(PD, LED2);
            break;
    }
}

void LED_off(char LED_Number) {
    switch (LED_Number) {
        case LED0:
            resetpin(PC, LED0);
            break;
        case LED1:
            resetpin(PC, LED1);
            break;
        case LED2:
            resetpin(PD, LED2);
            break;
    }
}

void init_BTNs() {
    //IO Configuration
    setpinIN(PB, BTN0);
    setpinIN(PD, BTN1);
    setpinIN(PD, BTN2);
}

char isPressed(char BTN_Number) {
    switch (BTN_Number) {
        case BTN0:
            return readPin(PB, BTN0);
            break;
        case BTN1:
            return readPin(PD, BTN1);
            break;
        case BTN2:
            return readPin(PD, BTN2);
            break;
        default:
            return 0;
    }
}



