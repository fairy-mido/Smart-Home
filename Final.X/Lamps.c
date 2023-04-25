/*
 * File:   Lamps.c
 * Author: TOKA
 *
 * Created on March 24, 2023, 3:46 PM
 */

#define F_CPU 16000000UL
#include <xc.h>
#include"Lamps.h"
#include"DIO.h"
#include"mlcd.h"
#include "UART.h"
#include<util/delay.h>
#include <stdlib.h>


char on1[] = "LED1 IS ON*" ;
char on2[] = "LED2 IS ON*" ;
char on3[] = "LED3 IS ON*" ;
char on4[] = "LED4 IS ON*" ;
char on5[] = "LED5 IS ON*" ;

char all_on[] = "ALL LEDS ARE ON" ;




void init_LEDs() {
    // IO Configurations
    setpinOUT(LED1_PORT, LED1);
    setpinOUT(LED2_PORT, LED2);
    setpinOUT(LED3_PORT, LED3);
    setpinOUT(LED4_PORT, LED4);
    setpinOUT(LED5_PORT, LED5);
    // reset LEDs
    LED_off(LED1);
    LED_off(LED2);
    LED_off(LED3);
    LED_off(LED4);
    LED_off(LED5);
}
void LED_on(char LED_number) {
    switch (LED_number) {
        case LED1:
        {
            setpin(LED1_PORT, LED1);
            lcd_clear();
            lcd_data_str(on1);
            UART_send_string(on1);
            _delay_ms(500);
            break;
        }
            case LED2:
            {
            setpin(LED2_PORT, LED2);
            lcd_clear();
            lcd_data_str(on2);
            UART_send_string(on2);
            _delay_ms(500);
            break;
            }
            case LED3:
            {
                setpin(LED3_PORT, LED3);
            lcd_clear();
            lcd_data_str(on3);
            UART_send_string(on3);
            _delay_ms(500);
            break;
            }
            case LED4:
            {
                setpin(LED4_PORT, LED4);
            lcd_clear();
            lcd_data_str(on4);
            UART_send_string(on4);
            _delay_ms(500);
            break;
            }
            case LED5:
            {
                setpin(LED5_PORT, LED5);
            lcd_clear();
            lcd_data_str(on5);
            UART_send_string(on5);
            _delay_ms(500);
            break;
            }
        case ALL_LEDs:
        {
            setpin(LED1_PORT, LED1);
            setpin(LED2_PORT, LED2);
            setpin(LED3_PORT, LED3);
            setpin(LED4_PORT, LED4);
            setpin(LED5_PORT, LED5);
//            lcd_clear();
//            lcd_data_str(all_on);
            _delay_ms(500);
            break;
        }
        default:
            ;
    }

}

void LED_off(char LED_number) {
    switch (LED_number) {
        case LED1:
            resetpin(LED1_PORT, LED1);
            break;
        case LED2:
            resetpin(LED2_PORT, LED2);
            break;
        case LED3:
            resetpin(LED3_PORT, LED3);
            break;
        case LED4:
            resetpin(LED4_PORT, LED4);
            break;
        case LED5:
            resetpin(LED5_PORT, LED5);
            break;
        case ALL_LEDs:
            resetpin(LED1_PORT, LED1);
            resetpin(LED2_PORT, LED2);
            resetpin(LED3_PORT, LED3);
            resetpin(LED4_PORT, LED4);
            resetpin(LED5_PORT, LED5);
            break;
    }
    
}


