/* 
 * File:   DIO.h
 * Author: hossa
 *
 * Created on 23 ??????, 2022, 09:52 ?
 */

#ifndef DIO_H
#define	DIO_H

#define led0 0
#define led1 1
#define led2 2
#define led3 3
#define led4 4
#define led5 5
#define led6 6
#define led7 7

#define push_btn0   0
#define push_btn1   6

#define PA    0
#define PB    1
#define PC    2
#define PD    3

void setportOUT(char portName);
void setportIN(char portName);

void setpinOUT(char portName, char pinNum);
void setpinIN(char portName, char pinNum);

// Special
char readPin(char portName, char pinNum);

void setpin(char portName, char pinNum);
void resetpin(char portName, char pinNum);

void setport(char portName);
void resetport(char portName);

void setDataPort(char portName, char data);


#endif	/* DIO_H */

