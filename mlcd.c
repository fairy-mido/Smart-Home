#define F_CPU 16000000UL
#include "mlcd.h"
#include <stdlib.h>
#include <util/delay.h>

/**
 * This function is used to Clear the whole LCD.
 */
void lcd_clear() {
    lcd_cmd(LCD_cmd_CLEAR);
}

/**
 * This Function is used to display String 'pData' on LCD.
 * @param pData : Pointer to char 
 * 
 * char * pData = "Hello"; \n
 * lcd_data_str(pData);
 */
void lcd_data_str(char * pData) {

    for (int index = 0; pData[index] != '\0'; index++) {
        lcd_data(pData[index]);
    }
}

void lcd_enable() {
    setpin(LCD_CONTROL, LCD_EN);
    _delay_ms(10);
    resetpin(LCD_CONTROL, LCD_EN);
}

/**
 * This function is to initialize LCD device to Microcontroller
 */
void lcd_init() {
    // PIN Configuration

    // set LCD_DATA as OUT
    setportOUT(LCD_DATA);
    // set RS as output
    setpinOUT(LCD_CONTROL, LCD_RS);
    // set RW as output
    setpinOUT(LCD_CONTROL, LCD_RW);
    _delay_ms(5);
    resetpin(LCD_CONTROL, LCD_RW); // (RW =0)
    // set EN as output
    setpinOUT(LCD_CONTROL, LCD_EN);
    _delay_ms(5);
    resetpin(LCD_CONTROL, LCD_EN); // (EN =0)



    // LCD initialization ...
    lcd_cmd(LCD_cmd_MODE);
    lcd_cmd(LCD_cmd_CLEAR); // CLEAR command
    
    lcd_cmd(LCD_cmd_ENTRY_MODE);
    lcd_cmd(0x28);
    lcd_cmd(LCD_cmd_D_ON_C_OFF);

    _delay_ms(50);

}

void lcd_data(char data) {

#ifdef LCD_8bit_MODE
    // put data on DATA BUS
    setDataPort(LCD_DATA, data);
    // select LCD Data Register   (RS =1)
    setpin(LCD_CONTROL, LCD_RS);
    // Enable
    lcd_enable();

#else
    // select LCD Instruction Register   (RS =0)
    setpin(LCD_CONTROL, LCD_RS);
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
    // Enable
    lcd_enable();

    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data << 4);
    // Enable
    lcd_enable();
#endif

}

void lcd_cmd(char cmd) {

#ifdef LCD_8bit_MODE
    // put data on DATA BUS
    setDataPort(LCD_DATA, cmd);
    // select LCD Instruction Register   (RS =0)
    resetpin(LCD_CONTROL, LCD_RS);
    // Enable
    lcd_enable();
#else
    // select LCD Instruction Register   (RS =0)
    resetpin(LCD_CONTROL, LCD_RS);
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd & 0xF0);
    // Enable
    lcd_enable();

    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd << 4);
    // Enable
    lcd_enable();
#endif







    // Cmd 0x01    00000001
    //0x0f == 00001111
    //PORTA = xxxxxxxx
    //(PORTA & 0x0F) == 0000xxxx
}

void lcd_data_num(int num) {
    char str[11];
    itoa(num, str, 10);
    lcd_data_str(str);
}


void lcd_goto(char row, char coln){
    // 1st line  >> 0
    // 2nd line  >> 1
    if(row == 0){
        // 0x8X
        lcd_cmd(0x80+coln);
    }else if(row == 1){
        lcd_cmd(0xC0+coln);
    }
}