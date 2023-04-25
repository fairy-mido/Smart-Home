
#define F_CPU 16000000UL
#include <xc.h>

//#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "DIO.h"
#include "servo.h"
#include "UART.h"
#include "mlcd.h"
#include "DC_Motor.h"
#include "Lamps.h"
#include "I2C.h"

//#define GET_BIT(VAR,BITNO) ((VAR>>BITNO)&1)
void init_UART()
{
    UBRRL = 103;
    UCSRB |= (1<<RXEN)|(1<<TXEN);
    UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
    
}

//void UART_send(char data)
//{
//    if(!(UCSRA & (1<< UDRE)));
//    UDR = data;
//}

void UART_send(char data )
{

while ( !( UCSRA & (1<<UDRE)) );
UDR = data;
}

char UART_receive()
{
    while(!(UCSRA & (1<<RXC)));
    return UDR;
}

void UART_send_string (char str[])
{
     int i;
    
    
   
    for(i=0;str[i]!='*';i++)
    {
        UART_send(str[i]);
        
    }
    UART_send(13);
    
      for(i=0;i<50;i++)
    {
          str[i] = '\0';
        
    }
    
    
    
}



int strcomp_servo(char str[] , char strin[])
{
    int i=0;
    while(str[i]!='*' || strin[i]!='*')
    {
        if(str[i]==strin[i])
        {
            i++;
        }
        else
        {
            i=100;
            break;
        }
        
    }
    
    if(i<51)
    {
        return 0;
    }
    else return 1;
}

int strcomp_motor(char str[] , char strin[])
{
    int i=0;
    while(str[i]!='*' || strin[i]!='*')
    {
        if(str[i]==strin[i])
        {
            i++;
        }
        else
        {
            i=100;
            break;
        }
        
    }
    
    if(i<51)
    {
        return 2;
    }
    else return 3;
}

int strcomp_newuser(char str[] , char strin[])
{
    int i=0;
    while(str[i]!='*' || strin[i]!='*')
    {
        if(str[i]==strin[i])
        {
            i++;
        }
        else
        {
            i=100;
            break;
        }
        
    }
    
    if(i<51)
    {
        return 4;
    }
    else return 5;
}


int strcomp_lamp1(char str[] , char strin[])
{
    int i=0;
    while(str[i]!='*' || strin[i]!='*')
    {
        if(str[i]==strin[i])
        {
            i++;
        }
        else
        {
            i=100;
            break;
        }
        
    }
    
    if(i<51)
    {
        return 6;
    }
    else return 7;
}
int strcomp_lamp2(char str[] , char strin[])
{
    int i=0;
    while(str[i]!='*' || strin[i]!='*')
    {
        if(str[i]==strin[i])
        {
            i++;
        }
        else
        {
            i=100;
            break;
        }
        
    }
    
    if(i<51)
    {
        return 8;
    }
    else return 9;
}
int strcomp_lamp3(char str[] , char strin[])
{
    int i=0;
    while(str[i]!='*' || strin[i]!='*')
    {
        if(str[i]==strin[i])
        {
            i++;
        }
        else
        {
            i=100;
            break;
        }
        
    }
    
    if(i<51)
    {
        return 10;
    }
    else return 11;
}
int strcomp_lamp4(char str[] , char strin[])
{
    int i=0;
    while(str[i]!='*' || strin[i]!='*')
    {
        if(str[i]==strin[i])
        {
            i++;
        }
        else
        {
            i=100;
            break;
        }
        
    }
    
    if(i<51)
    {
        return 12;
    }
    else return 13;
}
int strcomp_lamp5(char str[] , char strin[])
{
    int i=0;
    while(str[i]!='*' || strin[i]!='*')
    {
        if(str[i]==strin[i])
        {
            i++;
        }
        else
        {
            i=100;
            break;
        }
        
    }
    
    if(i<51)
    {
        return 14;
    }
    else return 15;
}

int new_user_pass;


void UART_receive_string()
{
    
    setpinOUT(PB,0);
    
    
   
    
  char  st_servo_open[50]="open servo*";
  char  st_servo_close[50]="close servo*";
  char  st_newuser[50]="create new user*";
  char  st_led1_open[50]="led1 on*";
  char  st_led1_close[50]="led1 off*";
    char  st_led2_open[50]="led2 on*";
  char  st_led2_close[50]="led2 off*";
    char  st_led3_open[50]="led3 on*";
  char  st_led3_close[50]="led3 off*";
    char  st_led4_open[50]="led4 on*";
  char  st_led4_close[50]="led4 off*";
    char  st_led5_open[50]="led5 on*";
  char  st_led5_close[50]="led5 off*";
  
  char st_DCmotor_on[50]="run motor*";
  char st_DCmotor_off[50]="stop motor*";
  
  
  
  
  char  st_servo_opened[50]="servo is opened*";
  char  st_servo_closed[50]="servo is closed*";
  char  st_led_opened[50]="led is on*";
  char  st_led_closed[50]="led is off*";
  char st_DCmotor_running[50]="motor running*";
  char st_DCmotor_stop[50]="motor stop*";
  
  
    char str[50];
    int i;
    //while(1)
       
        i=0;
    
//    for(int x=0;x<50;x++)
//    {
//        str[x] = '\0';
//    }
        
        while(1)
        {
            
            
          str[i]=UART_receive();
          
          if(str[i]=='*')
          {
              UART_send(13); // to new line
              break;
              
          }
          i++;
          
        }
        
  
        
        if(strcomp_servo(str,st_servo_open) == 0)
        {
                    servo_open();
            UART_send_string(st_servo_opened);
        }
        else if(strcomp_servo(str,st_servo_close) == 0)
        {
            servo_close();
            UART_send_string(st_servo_closed);
        }
        if(strcomp_motor(str,st_DCmotor_on) == 2)
        {
             Motor_Forward();
            UART_send_string(st_DCmotor_running);
        }
        else if(strcomp_motor(str,st_DCmotor_off) == 2)
        {
            Motor_stop();
            UART_send_string(st_DCmotor_stop);
        }
        else if(strcomp_newuser(str,st_newuser)==4)
        {
            new_user_pass = create_new_user();
        }
        else if(strcomp_lamp1(str,st_led1_open)==6)
        {
             LED_on(LED1);
        }
        else if(strcomp_lamp1(str,st_led1_close)==6)
        {
             LED_off(LED1);
        }
        else if(strcomp_lamp2(str,st_led2_open)==8)
        {
             LED_on(LED2);
        }
        else if(strcomp_lamp2(str,st_led2_close)==8)
        {
             LED_off(LED2);
        }
        else if(strcomp_lamp3(str,st_led3_open)==10)
        {
             LED_on(LED3);
        }
        else if(strcomp_lamp3(str,st_led3_close)==10)
        {
             LED_off(LED3);
        }
        else if(strcomp_lamp4(str,st_led4_open)==12)
        {
             LED_on(LED4);
        }
        else if(strcomp_lamp4(str,st_led4_close)==12)
        {
             LED_off(LED4);
        }
        else if(strcomp_lamp5(str,st_led5_open)==14)
        {
             LED_on(LED5);
        }
        else if(strcomp_lamp5(str,st_led5_close)==14)
        {
             LED_off(LED5);
        }
         
    
    
    
}



//void receive_string()
//{
//
////    char str[50];
////    int i=0;
//    // if(UART_receive())
//    //if(!UART_receive()) 
////    {
////         lcd_data(UART_receive());
////     }
// 
////    if(UART_receive())
////    {
//////        for(int i =0;str[i]=='*';i++)
//////        {
//////            str[i]=UART_receive();
//////        }
////        
////        while (str[i] != '*') {
////            str[i]=UART_receive();
////            i++;
////
////        }
////
////        
////        lcd_data_str(str);
////        UART_receive(13);
////    }
//    
//}
//


int admin_pass()
{
    char str_admin[50] = "enter admin pass*";
    UART_send_string(str_admin);
    
    char str[50];
   char str2[50]; // to copy string with out *
    int i;
    
      
        i=0;
    
    for(int x=0;x<50;x++)
    {
        str[x] = '\0';
    }
        
        while(1)
        {
            
           
          str[i]=UART_receive();
            
          if(str[i]=='*')
          {
              
              UART_send(13); // to new line
              break;
              
          }
          i++;
          
        }
        int z;
        for(z=0;z<i;z++)
        {
            str2[z]=str[z];  // to copy string with out *
        }
        //int pass = atoi(str2);
        //UART_send_string(str2);  /////////// send to EEPROM
        int pp = atoi(str2);
        
        return pp;
    
}
int kk;


int create_new_user()
{
    
    char str_user_added[50] = "user is added*";
    char str_userpass[50] = "enter user pass*";
    
    UART_send_string(str_userpass);
    
 
    
    char str[50];
    char str2[50]; // to copy string with out *
    int i;
    
      
    i=0;
    
    for(int x=0;x<50;x++)
    {
        str[x] = '\0';
    }
        
        while(1)
        {
            
           
          str[i]=UART_receive();
            
          if(str[i]=='*')
          {
              
              UART_send(13); // to new line
              break;
              
          }
          i++;
          
        }
        int z;
        for(z=0;z<i;z++)
        {
            str2[z]=str[z];  // to copy string with out *
        }
        //int pass = atoi(str2);
       // UART_send_string(str2); /////////// send to EEPROM
        kk = atoi(str2);
        EEPROM_call(EEPROM_address_write,EEPROM_User1_Address);
        EEPROM_write_pass(kk);
        _delay_ms(10);
        UART_send_string(str_user_added); 
        return kk;
    
}

int  newuserpass()
{
    return kk;
}