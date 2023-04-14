/* 
 * File:   DIO.h
 * Author: moham
 *
 * Created on February 4, 2023, 9:51 AM
 */

#ifndef DIO_H
#define	DIO_H


#define PA 0
#define PB 1
#define PC 2
#define PD 3

// Functions prototypes
void setportOUT(char portName);
void setportIN(char portName);

void setpinOUT(char portName, char pinNum);
void setpinIN(char portName, char pinNum);

void setpin(char portName, char pinNum);
void resetpin(char portName, char pinNum);

void setport(char portName);
void resetport(char portName);

char readPin(char portName, char pinNum);
void setDataPort(char portName, char data);

#endif	/* DIO_H */

