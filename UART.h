/* 
 * File:   UART.h
 * Author: Kimo Store
 *
 * Created on March 27, 2023, 11:19 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

void init_UART();
void UART_send(char data);
char UART_receive();
int compare_servo(char a[],char b[]);
int compare_led(char a[],char b[]);
void UART_receive_string();


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

