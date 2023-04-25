
#define F_CPU 16000000UL
#include <xc.h>

//#include <avr/interrupt.h>
#include <util/delay.h>
#include "DIO.h"
#include "servo.h"
#include "UART.h"



void init_UART()
{
    UBRRL = 103;
    UCSRB |= (1<<RXEN)|(1<<TXEN);
    UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
    
}

void UART_send(char data)
{
    while(!(UCSRA & (1<< UDRE)));
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
    for(i=0;i<50;i++)
    {
        UART_send(str[i]);
        
    }
    UART_send(13);
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

int strcomp_led(char str[] , char strin[])
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




void UART_receive_string()
{
    
    // setpinOUT(PB,0);
    
    
   
    
  char  st_servo_open[50]="open servo*";
  char  st_servo_close[50]="close servo*";
  char  st_led_open[50]="led on*";
  char  st_led_close[50]="led off*";
  
  char  st_servo_opened[50]="servo is opened";
  char  st_servo_closed[50]="servo is closed";
  char  st_led_opened[50]="led is on";
  char  st_led_closed[50]="led is off";
  
    char str[50];
    int i;
    while(1)
    {   
        i=0;
    
    for(int x=0l;x<50;x++)
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
         if(strcomp_led(str,st_led_open) == 2)
        {
            setpin(PB,0);
            UART_send_string(st_led_opened);
        }
        else if(strcomp_led(str,st_led_close) == 2)
        {
            resetpin(PB,0);
            UART_send_string(st_led_closed);
        }
         
    }
    
    
}

