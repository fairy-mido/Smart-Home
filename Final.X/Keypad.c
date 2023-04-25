/*
 * File:   Keypad.c
 * Author: TOKA
 *
 * Created on March 20, 2023, 7:58 PM
 */


#define F_CPU 16000000UL
#include"Keypad.h"
#include"DIO.h"
#include "Lamps.h"
#include "DC_Motor.h"
#include "mlcd.h"
#include "I2C.h"
#include "servo.h"
#include "mADC.h"
#include<util/delay.h>
#include <stdlib.h>

char led1_already_on[] = "Led1 is already on";
char led2_already_on[] = "Led2 is already on";
char led3_already_on[] = "Led3 is already on";
char led4_already_on[] = "Led4 is already on";
char led5_already_on[] = "Led5 is already on";

char led1_already_off[] = "Led1 is already off";
char led2_already_off[] = "Led2 is already off";
char led3_already_off[] = "Led3 is already off";
char led4_already_off[] = "Led4 is already off";
char led5_already_off[] = "Led5 is already off";

char motor_running[] = "motor is already on";
char motor_not_running[] = "motor is already off";

char servo_already_open[] = "servo is already open";
char servo_already_closed[] = "servo is already closed";

char led_intensity[] = "Getting Led";
char intensity_word[] = "intensity";
char read_led_intense[] = "Led intensity is ";
char percent_sign[] = "%";

char temp[] = "Reading Temperature";
char read_temp[] = "Temperature is ";

char led_on_choice[] = "1- Led On";
char led_off_choice[] = "2- Led Off";

char led1_choice[] = "1-Led1 On/Off";
char led2_choice[] = "2-Led2 On/Off";
char led3_choice[] = "3-Led3 On/Off";
char led4_choice[] = "4-Led4 On/Off";
char led5_choice[] = "5-Led5 On/Off";
char motor_choice[] = "6-Motor On/Off";
char servo_choice[] = "7-servo On/Off";
char temp_sens_choice[] = "8-Temp Read";
char dimmer_choice[] = "9-Lamp intensity";
char next_choice[] = "0-Next page";
char home_choice[] = "0-Home page";
char continue_press[] = "Press 0 for next";
char plus_sign[] = "Press + to exit";
char back_to_temp_sens[] = "Press 8 to back";
char back_to_led_intense[] = "Press 9 to back";
char result_word[] = "result";
char not_pressed_char = 'ÿ';
char Volt_char[] = "V";
char check_keypad_status = 0;

void connect_pullup(char PortName, char PinNum, char connect_pullup) {
    switch (PortName) {

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

void keypad_init() {
    // Set Ports as output
    setpinOUT(keypad_out_port, keypad_First_Pin);
    setpinOUT(keypad_out_port, keypad_second_Pin);
    setpinOUT(keypad_out_port, keypad_Third_Pin);
    setpinOUT(keypad_out_port, keypad_Fourth_Pin);

    // Set Ports as Input

    setpinIN(keypad_in_port, keypad_Fifth_Pin);
    setpinIN(keypad_in_port, keypad_sixth_Pin);
    setpinIN(keypad_in_port, keypad_Seventh_Pin);
    setpinIN(keypad_in_port, keypad_Eighth_Pin);

    // SET CONNECT PULL_UP
    // set coln as input (high 0xff by default)
    connect_pullup(keypad_in_port, keypad_Fifth_Pin, 1);
    connect_pullup(keypad_in_port, keypad_sixth_Pin, 1);
    connect_pullup(keypad_in_port, keypad_Seventh_Pin, 1);
    connect_pullup(keypad_in_port, keypad_Eighth_Pin, 1);

}

char Keypad_CheckPress() {
    char arr[4][4] = {
        {'7', '8', '9', '/'},
        {'4', '5', '6', '*'},
        {'1', '2', '3', '-'},
        {'A', '0', '=', '+'}}; //keypad buttons
    char row; //which indicate the given output  pin
    char coloumn; //which indicate the given input pin
    char key_pressed_indicator; //the variable  which contain the key pressed

    char returnval = NOT_PRESSED; //the variable contain the value which will be returned which will be key pressed or not pressed in case of no key pressed

    for (row = 0; row < 4; row++) {
        /*stop the work of keypad firstly*/
        setpin(keypad_out_port, keypad_First_Pin);
        setpin(keypad_out_port, keypad_second_Pin);
        setpin(keypad_out_port, keypad_Third_Pin);
        setpin(keypad_out_port, keypad_Fourth_Pin);

        /*************************************/
        _delay_ms(13);

        resetpin(keypad_out_port, row); //write 0 to the first pin in keypad (output pin from MC)
        for (coloumn = 0; coloumn < 4; coloumn++) {
            key_pressed_indicator = readPin(keypad_in_port, (coloumn + 4)); // read the input pins of MC which connected to keypad
            if (key_pressed_indicator == 0)// will be 0 only if any key pressed
            {
                returnval = arr[row][coloumn]; //put the selected pressed key to the returnval
                break; // break from the loop
            }
        }
    }
    return returnval; //return the pressed key in case of key pressed or return 0xff in case of no key pressed
}

void press_action() {
    float result = 0;
    int result_bits = 0;
    char check_keypad;
    lcd_clear();
    lcd_data_str(next_choice);
    _delay_ms(150);
    lcd_clear();
    lcd_data_str(led1_choice);
    _delay_ms(3);
    lcd_goto(second_row, 0);
    _delay_ms(3);
    lcd_data_str(led2_choice);
    _delay_ms(500);
    check_keypad = Keypad_CheckPress();
    while ((check_keypad != not_pressed_char) && (check_keypad != 'A')) {
        while (Keypad_CheckPress() != '0') {
            _delay_ms(20);
            if (Keypad_CheckPress() == '1') {
                if (readPin(PC, 2))
                {
                    _delay_ms(130);
                    LED_off(LED1);
                }
                else
                {
                    _delay_ms(130);
                    LED_on(LED1);
                }
            }
            else if (Keypad_CheckPress() == '2') {
                if (readPin(PC, 3))
                {
                    _delay_ms(130);
                    LED_off(LED2);
                    
                }
                else
                {
                    _delay_ms(130);
                    LED_on(LED2);
            
                }
            }
            check_keypad_status = 0;
        }
        lcd_clear();
        _delay_ms(3);
        lcd_data_str(led3_choice);
        _delay_ms(3);
        lcd_goto(second_row, 0);
        _delay_ms(3);
        lcd_data_str(led4_choice);
        _delay_ms(200);
        while (Keypad_CheckPress() != '0') {
            _delay_ms(20);
            if (Keypad_CheckPress() == '3') {
                if (readPin(PC, 4))
                {
                    _delay_ms(130);
                    LED_off(LED3);
                }
                else
                {
                    _delay_ms(130);
                    LED_on(LED3);
                }
            } else if (Keypad_CheckPress() == '4') {
                if (readPin(PD, 6))
                {
                    _delay_ms(130);
                    LED_off(LED4);
                }
                else
                {
                    _delay_ms(130);
                    LED_on(LED4);
                }
                    

            }
        }

        lcd_clear();
        _delay_ms(3);
        lcd_data_str(led5_choice);
        _delay_ms(3);
        lcd_goto(second_row, 0);
        _delay_ms(3);
        lcd_data_str(motor_choice);
        _delay_ms(200);
        while (Keypad_CheckPress() != '0') {
            _delay_ms(20);
            if (Keypad_CheckPress() == '5') {
                if (readPin(PD, 5))
                {
                    _delay_ms(130);
                    LED_off(LED5);
                }
                else
                {
                    _delay_ms(130);
                    LED_on(LED5);
                }
            } else if (Keypad_CheckPress() == '6') {
                if (readPin(PA, 2))
                {
                    _delay_ms(130);
                    Motor_stop();
                }
                else
                {
                    _delay_ms(130);
                    Motor_Forward();
                }

            }
        }

        lcd_clear();
        _delay_ms(3);
        lcd_data_str(servo_choice);
        _delay_ms(3);
        lcd_goto(second_row, 0);
        _delay_ms(3);
        lcd_data_str(temp_sens_choice);
        _delay_ms(200);
        while (Keypad_CheckPress() != '0') {
            _delay_ms(20);
            if (Keypad_CheckPress() == '7') {
                if(readPin(PD,7))
                {
                    _delay_ms(130);
                    servo_close();
                }
                    else
                    {
                    _delay_ms(130);
                    servo_open();
                    }

            } else if (Keypad_CheckPress() == '8') {
                 _delay_ms(200);
                  lcd_clear();
                lcd_data_str(temp);
                _delay_ms(3);
                lcd_goto(second_row,0);
                lcd_data_str(plus_sign);
                 _delay_ms(500);
                while (1) {
                    lcd_clear();
                    _delay_ms(5);
                    selectCH(CH1);
                    ADC_START();
                    result_bits = ADC_result();
                    //result = (result_bits * 50) / 1024;
                    _delay_ms(3);
                    lcd_data_num(result_bits);
                    _delay_ms(300);
                     lcd_clear();
                    if (Keypad_CheckPress() == '+') {
                        break;
                    }
                }
                 lcd_clear();
                 _delay_ms(3);
                 lcd_data_str(continue_press);
                 _delay_ms(5);
                 lcd_goto(second_row,0);
                 _delay_ms(3);
                 lcd_data_str(back_to_temp_sens);
                 _delay_ms(300);
            }
        }
        lcd_clear();
        _delay_ms(3);
        lcd_data_str(dimmer_choice);
        _delay_ms(5);
        lcd_goto(second_row, 0);
        _delay_ms(3);
        lcd_data_str(home_choice);
        _delay_ms(200);
        while (Keypad_CheckPress() != '0') {
            if (Keypad_CheckPress() == '9') {
                result = 0;
                lcd_clear();
                _delay_ms(3);
                lcd_data_str(led_intensity);
                _delay_ms(5);
                lcd_goto(second_row,0);
                _delay_ms(3);
                lcd_data_str(intensity_word);
                _delay_ms(250);
                    
                while (1) {
                    lcd_clear();
                    selectCH(CH0);
                     ADC_START();
                    result_bits = ADC_result();
                    result = (result_bits * 5000) / 1024;
                    lcd_data_num((result/1000));
//                    lcd_data((result/1000));
                    _delay_ms(3);
                    lcd_data_str(Volt_char);
                    _delay_ms(500);
                    if (Keypad_CheckPress() == '+') {
                        break;
                    }
                }
                lcd_clear();
                _delay_ms(3);
                lcd_data_str(continue_press);
                _delay_ms(5);
                lcd_goto(second_row,0);
                _delay_ms(3);
                lcd_data_str(back_to_led_intense);
                _delay_ms(300);
            }
        }
        lcd_clear();
//        check_keypad_status = 0; // This is a problem fix for the first while block, as it was letting it execute
        _delay_ms(200);
        break;
    }
}

//
//void updated_press_action()
//{
//    if(Keypad_CheckPress()=='1')
//    {
//        lcd_clear();
//        _delay_ms(100);
//        lcd_data_str(led_on_choice);
//        _delay_ms(5);
//        lcd_goto(second_row,0);
//        _delay_ms(5);
//        lcd_data_str(led_off_choice);
//        _delay_ms(1000);
//        while(1)
//        {
//        char button = Keypad_CheckPress(); 
//        if(button == '1')
//        {
//            if(readPin(PC,2))
//            {
//                lcd_clear();
//                lcd_data_str(led1_already_on);
//                break;
//            }
//            else
//            {
//                LED_on(LED1);
//                break;
//            }
//        }
//        else if(button == '2')
//        {
//            if(readPin(PC,2))
//            {
//                LED_off(LED1);
//                break;
//            }
//            else
//            {
//                lcd_clear();
//                lcd_data_str(led1_already_off);
//                break;
//            }
//        }
//        }
////        if(readPin(PC,2))
////           LED_off(LED1);
////        else
////            LED_on(LED1);
//    }
//    else if(Keypad_CheckPress()=='2')
//    {
//        if(readPin(PC,3))
//           LED_off(LED2);
//        else
//            LED_on(LED2);
//
//    }
//    else if(Keypad_CheckPress()=='3')
//    {
//        if(readPin(PC,4))
//           LED_off(LED3);
//        else
//            LED_on(LED3);
//
//    }
//    else if(Keypad_CheckPress()=='4')
//    {
//        if(readPin(PD,6))
//           LED_off(LED4);
//        else
//            LED_on(LED4);
//
//    }
//    else if(Keypad_CheckPress()=='5')
//    {
//        if(readPin(PD,5))
//           LED_off(LED5);
//        else
//            LED_on(LED5);
//
//    }
//    else if(Keypad_CheckPress()=='6')
//    {
//        if(readPin(PA,2))
//            Motor_stop();
//        else
//            Motor_Forward();
//
//    }
//    else if(Keypad_CheckPress()=='7')
//    {
//        if(readPin(PD,7))
//        {
//            servo_close();
//        }
//        else
//            servo_open();
//
//    }
//    else if(Keypad_CheckPress()== '8')
//    {
//        init_ADC(CH1,Ref_AVCC,PRE_64);
//         _delay_ms(10);
//        selectCH(CH1);
//        lcd_clear();
//        lcd_data_str(temp);
//        _delay_ms(100);
//        ADC_START();
//        short int adc_reading = (ADCL | (ADCH << 8));
//        lcd_data_str(read_temp);
//        _delay_ms(5);
//        lcd_data_num(adc_reading);
////        _delay_ms(100);
////        lcd_clear();
//    }
//    else if(Keypad_CheckPress()== '9')
//    {
//        init_ADC(CH0,Ref_AVCC,PRE_64);
//        _delay_ms(10);
//        lcd_clear();
//        selectCH(CH0);
//        lcd_data_str(led_intensity);
//        ADC_START();
//        short int adc_reading = (ADCL | (ADCH << 8));
//        _delay_ms(100);
//        lcd_data_str(read_led_intense);
//        _delay_ms(5);
//        lcd_data_num(adc_reading);
//        _delay_ms(5);
//        lcd_data_str(percent_sign);
//        _delay_ms(100);
//        lcd_clear();
//    }
//}
//void login_pass()
//{
//    char arr_pass[4];
//    int i=0;
//    int e = 0;
//    char z = 1;
//    while(z!='0')
//    {
//        z=Keypad_CheckPress();
//        switch(z)
//        {
//            case '1':
//                arr_pass[i]='1';
//                break;
//                
//            case '2':
//                arr_pass[i]='2';
//                break;
//            case '3':
//                arr_pass[i]='3';
//                break;
//            case '4':
//                arr_pass[i]='4';
//                break;
//            case '0':
//                z='0';
//                break;    
//        }
//        i++;
//        if(z=='0')
//        {
//            break;
//        }
//        
//        lcd_clear();
//        lcd_data(z);
//        
//        
//    }
//    UART_send_string(arr_pass);
//    lcd_clear();
//    lcd_data_str(arr_pass);
//
//    
//    for(e = 0; e<11;e++)
//    {
//        arr_pass[e] == '\0';
//               
//    }
//    while(z != '0')
//    {
//        if(Keypad_CheckPress()=='1')
//        {
//            arr_pass[i]='1';
//        }
//        else if(Keypad_CheckPress()=='2')
//        {
//            arr_pass[i]='2';
//        }
//        else if(Keypad_CheckPress()=='3')
//        {
//            arr_pass[i]='3';
//        }
//        else if(Keypad_CheckPress()=='4')
//        {
//            arr_pass[i]='4';
//        }
//        else if(Keypad_CheckPress()=='5')
//        {
//            arr_pass[i]='5';
//        }
//        else if(Keypad_CheckPress()=='6')
//        {
//            arr_pass[i]='6';
//        }
//        else if(Keypad_CheckPress()=='7')
//        {
//            arr_pass[i]='7';
//        }
//        else if(Keypad_CheckPress()=='8')
//        {
//            arr_pass[i]='8';
//        }
//        else if(Keypad_CheckPress()=='9')
//        {
//            arr_pass[i]='9';
//        }
//        else if(Keypad_CheckPress()=='0')
//        {
//            arr_pass[i]='0';
//        }
//        else if(Keypad_CheckPress() =='/')
//        {
//            arr_pass[i]='/';
//        }
//        
//        else if(Keypad_CheckPress() =='0')
//        {
//            z = '0';
//            break;
//        }
//        else if(Keypad_CheckPress() == 'k')
//        {
//            
//        }
//        lcd_clear();
//        lcd_data(arr_pass[i]);
//        _delay_ms(10);
//        i++;
//    }
//    
//    UART_send_string(arr_pass);
//    lcd_data_str(arr_pass);
//    _delay_ms(100);
//        int pp = atoi(arr_pass);
//        lcd_data_num(pp);
//    return pp;
//}

int login_user_pass() {
    char pass_counter = 0;
    int password = 0;
    char pass[pass_size] = {NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED};
    char key_pressed = NOT_PRESSED;
    while (pass_counter < pass_size) {
        key_pressed = NOT_PRESSED;
        while (key_pressed == NOT_PRESSED) {
            key_pressed = Keypad_CheckPress();
        }
        pass[pass_counter] = key_pressed;
        lcd_data(key_pressed);
        _delay_ms(300);
        lcd_goto(0, pass_counter);
        lcd_data('*');
        _delay_ms(100);
        pass_counter++;
    }
    password = atoi(pass);
    _delay_ms(100);
    return password;
}

void lcd_choices_display() {
    lcd_data_str(led1_choice);
    _delay_ms(3);
    lcd_goto(second_row, 0);
    _delay_ms(3);
    lcd_data_str(led2_choice);
    _delay_ms(250);

    lcd_clear();
    _delay_ms(3);
    lcd_data_str(led3_choice);
    _delay_ms(3);
    lcd_goto(second_row, 0);
    _delay_ms(3);
    lcd_data_str(led4_choice);
    _delay_ms(250);

    lcd_clear();
    _delay_ms(3);
    lcd_data_str(led5_choice);
    _delay_ms(3);
    lcd_goto(second_row, 0);
    _delay_ms(3);
    lcd_data_str(motor_choice);
    _delay_ms(250);

    lcd_clear();
    _delay_ms(3);
    lcd_data_str(servo_choice);
    _delay_ms(3);
    lcd_goto(second_row, 0);
    _delay_ms(3);
    lcd_data_str(temp_sens_choice);
    _delay_ms(250);

    lcd_clear();
    lcd_data_str(dimmer_choice);
}
