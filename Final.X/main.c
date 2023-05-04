/*
 * File:   main.c
 * Author: TOKA
 *
 * Created on March 22, 2023, 11:06 AM
 */


#define F_CPU 16000000UL
#include<xc.h>
#include<util/delay.h>
#include"DIO.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include"Keypad.h"
#include "mADC.h" 
#include "mTimer.h"
#include "UART.h"
#include "mlcd.h"
#include "Lamps.h"
#include "DC_Motor.h"
#include "I2C.h" 
#include "servo.h" 

//#define Rising_Edge  3   // 0b00000011
//#define Falling_Edge 2   // 0b00000010
//#define Any_Edge     1   // 0b00000001
//#define Low_Level    0 
//
//
//
//void init_INT0(char INT0_mode) {
//    // Select Interrupt Mode (Sense Control)
//    switch (INT0_mode) {
//        case Rising_Edge:
//            //            ISC01 = 1, ISC00 =1
//            MCUCR |= (1<<ISC00);
//            MCUCR |= (1<<ISC01);
//            break;
//        case Falling_Edge:
//            //            ISC01 = 1, ISC00 =0
//            MCUCR &= ~(1 << ISC00);
//            MCUCR |= (1 << ISC01);
//            break;
//        case Any_Edge:
//            //            ISC01 = 0, ISC00 =1
//            MCUCR |= (1 << ISC00);
//            MCUCR &= ~(1 << ISC01);
//            break;
//        case Low_Level:
//            //            ISC01 = 0, ISC00 =0
//            MCUCR &= ~(1 << ISC00);
//            MCUCR &= ~(1 << ISC01);
//            break;
//        default:
//            break;
//    }
//    // Enable for INT0 (Individual Interrupt Enable)
//    GICR |= (1<<INT0);
//}
//
//
//
//ISR(INT0_vect)
//{
//    setpin(PD,3);
//    UART_receive_string();
//}

ISR(TIMER0_OVF_vect) {
    static int times = 0;
    times++;
    if (times == 62) {
        ADC_START();
        times = 0;
    }
}

ISR(ADC_vect) {
    int result = 0;
    result = ADCL;
    result |= (ADCH << 8);

    // setDataPort(PD,result);

    ADC_START();
}

int main() {
    setpinIN(PD, 2);
    //    setpinOUT(PD,3);
    //    init_INT0(Any_Edge);
    // static design

    setpinOUT(PD, 3);



    init_UART();



    //    int z = EEPROM_read_pass();
    //    int a = newuserpass();


    //    
    //    
    init_TWI_master(255, TWI_PRE_TWPS_64, MAddress);
    //    
    lcd_init();
    keypad_init();
    init_LEDs();
    init_ADC(CH1, Ref_AVCC, PRE_128);
    init_ADC(CH0, Ref_AVCC, PRE_128);
    init_Timer0(Timer0_Normal, Timer0_PWM_OC0_disconnect, 50, Timer0_PRE_1024);
    Timer0_enable_OVIE();
    init_Motor(DC_Motor_1);
    servo_init();
    //     sei();
    EEPROM_call(EEPROM_address_write, EEPROM_Admin_Address);
    EEPROM_write_pass(EEPROM_Admin_password);
    _delay_ms(20);
    EEPROM_call(EEPROM_address_write, EEPROM_User1_Address);
    EEPROM_write_pass(0);
    _delay_ms(50);



    char user_pass[] = "enter user ";
    char wrong_pass[] = "wrong password";
    char reset_system[] = "Please Reset The";
    char system_word[] = "System";
    char admin_success_login[] = "Admin  pass";
    char correct_word[] = "correct";
    char pass_word[] = "password";
    char admin_using[] = "Admin using";
    char user_using[] = "User using";
    char login_user_str[] = "Press / to login";
    char access_keypad[] = "Press - 4 keypad";
    char exit_keypad[] = "Press O/C 2 Exit";
    char user_no_pass[] = "No User Found";
    char no_pass_entered[] = "No Permission";
    char pass_required[] = "Pass Required";
    int i_admin = 0;
    int i_user = 0;
    int q, f, pass;
    char login_before = 0;

    //    int check = 0;





    while (1) {
        int pp = admin_pass();
        i_admin++;
        if (pp == EEPROM_Admin_password) {
            lcd_clear();
            lcd_data_str(admin_success_login);
            _delay_ms(5);
            lcd_goto(second_row, 2);
            lcd_data_str(correct_word);
            _delay_ms(500);
            while (1) {

                // dynamic design  

                if (readPin(PD, 2)) {
                    lcd_clear();
                    lcd_data_str(admin_using);
                    //                    _delay_ms(500);
                    //                    lcd_clear();
                    UART_receive_string();
                }
                //UART_receive_string();
                lcd_clear();
                _delay_ms(3);
                //                updated_press_action();
                //                press_action();
                //                lcd_data(Keypad_CheckPress());
                //                _delay_ms(50);

                // Strings for the / and - signs of keypad
                lcd_data_str(login_user_str);
                _delay_ms(5);
                lcd_goto(second_row, 0);
                lcd_data_str(access_keypad);
                _delay_ms(500);
                lcd_clear();
                _delay_ms(3);
                q = Keypad_CheckPress();
                if ((q == '/') || (q == '-')) {
                    pass = 0;
                    EEPROM_call(EEPROM_address_write, EEPROM_User1_Address);
                    EEPROM_call(EEPROM_address_read, EEPROM_User1_Address);
                    _delay_ms(5);
                    f = EEPROM_read_pass(); // UART RETURN PASS
                    if ((f != 0)) {
                        if (q == '/') {
                            //                        if((f != 0))
                            //                        {
                            lcd_clear();
                            _delay_ms(10);
                            lcd_data_str(user_pass);
                            _delay_ms(5);
                            lcd_goto(second_row, 0);
                            lcd_data_str(pass_word);
                            _delay_ms(500);
                            lcd_clear();
                            pass = login_user_pass();
                            lcd_clear();
                            //                        }
                            //                        else
                            //                        {
                            //                            lcd_data_str(user_no_pass);
                            //                            _delay_ms(500);
                            //                            lcd_clear();
                            //                        }
                        }

                        if ((q == '/') || (q == '-')) {
                            if ((i_user < 2) || (f == pass)||(login_before)) {
                                if ((f == pass)||(login_before)) {
                                    login_before = 1;
                                    if (q == '-') {
                                        lcd_data_str(user_using);
                                        _delay_ms(300);
                                    }
                                    while (Keypad_CheckPress() != 'A') {
                                        lcd_clear();
                                        _delay_ms(3);
                                        lcd_data_str(exit_keypad);
                                        _delay_ms(350);
                                        press_action();
                                    }
                                    //                          } 

                                    //                            else 
                                    //                            {
                                    //                                lcd_data_str(wrong_pass);
                                    //                                _delay_ms(100);
                                    //                                i_user++;
                                    //                            }
                                } else {
                                    if (pass != 0) {
                                        lcd_data_str(wrong_pass);
                                        _delay_ms(100);
                                        i_user++;
                                    } else {
                                        lcd_data_str(no_pass_entered);
                                        _delay_ms(5);
                                        lcd_goto(second_row, 0);
                                        lcd_data_str(pass_required);
                                        _delay_ms(350);
                                    }
                                }
                            } else {
                                break;
                            }
                        }
                    } else {
                        lcd_data_str(user_no_pass);
                        _delay_ms(500);
                        lcd_clear();
                    }
                }
                //        if(check == 1)
                //        {
                //            press_action();
                ////            UART_send(13);
                ////            UART_send('o');
                //        }







            }
            break;
        } else {
            lcd_clear();
            lcd_data_str(wrong_pass);
            _delay_ms(200);
            if (i_admin == 3) {
                setpin(PD, 3);
                lcd_clear();
                lcd_data_str(reset_system);
                lcd_goto(second_row, 4);
                lcd_data_str(system_word);
                while (1);
            }
        }
    }
    // User while loop
    setpin(PD, 3);
    lcd_clear();
    lcd_data_str(reset_system);
    lcd_goto(second_row, 4);
    lcd_data_str(system_word);
    while (1);
    return 0;
}


