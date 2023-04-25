#include <xc.h>
#include "DIO.h"

char readPin(char portName, char pinNum) {

    switch (portName) {
        case PA:
            return (PINA & (1 << pinNum)) ? 1 : 0;
            break;
        case PB:
            return (PINB & (1 << pinNum)) ? 1 : 0;
            break;
        case PC:
            return (PINC & (1 << pinNum)) ? 1 : 0;
            break;
        case PD:
            return (PIND & (1 << pinNum)) ? 1 : 0;
            break;
        default:
            return 0;
    }


}

void setportOUT(char portName) {
    switch (portName) {
        case PA:
            DDRA = 0xFF;
            break;
        case PB:
            DDRB = 0xFF;
            break;
        case PD:
            DDRD = 0xFF;
            break;
        case PC:
            DDRC = 0xFF;
            break;
    }
}

void setportIN(char portName) {
    switch (portName) {
        case PA:
            DDRA = 0x00;
            break;
        case PB:
            DDRB = 0x00;
            break;
        case PD:
            DDRD = 0x00;
            break;
        case PC:
            DDRC = 0x00;
            break;
    }
}

void setpinOUT(char portName, char pinNum) {
    switch (portName) {
        case PA:
            DDRA |= (1 << pinNum);
            break;
        case PB:
            DDRB |= (1 << pinNum);
            break;
        case PC:
            DDRC |= (1 << pinNum);
            break;
        case PD:
            DDRD |= (1 << pinNum);
            break;
    }
}

void setpinIN(char portName, char pinNum) {
    switch (portName) {
        case PA:
            DDRA &= ~(1 << pinNum);
            break;
        case PB:
            DDRB &= ~(1 << pinNum);
            break;
        case PD:
            DDRD &= ~(1 << pinNum);
            break;
        case PC:
            DDRC &= ~(1 << pinNum);
            break;
    }
}

void setpin(char portName, char pinNum) {
    //    PORTA |= (1<<N)
    switch (portName) {
        case PA:
            PORTA |= (1 << pinNum);
            break;
        case PB:
            PORTB |= (1 << pinNum);
            break;
        case PC:
            PORTC |= (1 << pinNum);
            break;
        case PD:
            PORTD |= (1 << pinNum);
            break;
    }

}

void resetpin(char portName, char pinNum) {
    //PORTA &= ~(1<<N);
    switch (portName) {
        case PA:
            PORTA &= ~(1 << pinNum);
            break;
        case PB:
            PORTB &= ~(1 << pinNum);
            break;
        case PC:
            PORTC &= ~(1 << pinNum);
            break;
        case PD:
            PORTD &= ~(1 << pinNum);
            break;
    }
}

void setport(char portName) {
    switch (portName) {
        case PA:
            PORTA = 0xFF;
            break;
        case PB:
            PORTB = 0xFF;
            break;
        case PD:
            PORTD = 0xFF;
            break;
        case PC:
            PORTC = 0xFF;
            break;
    }
}

void resetport(char portName) {
    switch (portName) {
        case PA:
            PORTA = 0x00;
            break;
        case PB:
            PORTB = 0x00;
            break;
        case PD:
            PORTD = 0x00;
            break;
        case PC:
            PORTC = 0x00;
            break;
    }
}

void setDataPort(char portName, char data){
        switch (portName) {
        case PA:
            PORTA = data;
            break;
        case PB:
            PORTB = data;
            break;
        case PD:
            PORTD = data;
            break;
        case PC:
            PORTC = data;
            break;
    }
}