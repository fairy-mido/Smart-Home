#include "mADC.h"
#include <xc.h>

void selectCH(char CH) {
    ADMUX &= 0xE0; //11100000
    ADMUX |= CH;
}

void selectREF(char REF) {
    ADMUX &= 0x3F; // 00111111
    ADMUX |= (REF << 6);
}

void selectFREQ(char freq) {
    ADCSRA &= 0xF8; // 11111000
    ADCSRA |= freq;
}

void ADC_EN() {
    ADCSRA |= (1 << ADEN);
}

void ADC_START() {
    ADCSRA |= (1 << ADSC);
}

void ADC_INT_EN() {
    ADCSRA |= (1 << ADIE);
}

void init_ADC(char CH, char Ref, char freq) {
    // Select CH
    // ADMUX ( CH Selection)
    selectCH(CH); // 00000000

    // Select Ref
    selectREF(Ref);
    // Select Freq
    selectFREQ(freq);
    // ADC Interrupt Enable
    ADC_INT_EN();
    // Enable ADC
    ADC_EN();
    // *** Operate .....
}

