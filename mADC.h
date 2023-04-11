/* 
 * File:   mADC.h
 * Author: hossa
 *
 * Created on 27 ?????, 2023, 10:48 ?
 */

#ifndef MADC_H
#define	MADC_H

#define CH0     0   // 00000
#define CH1     1   // 00001
#define CH2     2   // 00011
#define CH3     3   // 00100
#define CH4     4   
#define CH5     5
#define CH6     6
#define CH7     7   // 00111
#define CH3_CH1_1   0x13 // 10011

#define Ref_AVCC   1
#define Ref_2_56   3
#define Ref_AREF   0

#define PRE_2      0
#define PRE_4      2
#define PRE_8      3
#define PRE_16     4
#define PRE_32     5
#define PRE_64     6
#define PRE_128    7



void selectCH(char CH);

void selectREF(char REF);

void selectFREQ(char freq);
void ADC_EN();
void ADC_START();
void ADC_INT_EN();

void init_ADC(char CH, char Ref, char freq);



#endif	/* MADC_H */

