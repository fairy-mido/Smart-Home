#define F_CPU 16000000
#include "xc.h"
#include "I2C.h"
#include "DIO.h"
#include <util/delay.h>



void init_TWI_master(int bit_rate,int pre_scale,int master_address)
{
    TWBR = bit_rate;
    TWSR |= (1<<TWPS0)|(1<<TWPS1);  // TWPS pre 64
    TWAR = master_address;
    
//    if(pre_scale == TWI_PRE_TWPS_1)
//    {
////        TWSR &= 0xFC;  //0b11111100
//        TWSR &= ~(1<<TWPS0);
//        TWSR &= ~(1<<TWPS1);
//    }
//    if(pre_scale == TWI_PRE_TWPS_4)
//    {
////        TWSR &= 0xFD;     //ob1111 1101
//        TWSR |= (1<<TWPS0);
//        TWSR &= ~(1<<TWPS1);
//    }
//    if(pre_scale == TWI_PRE_TWPS_16)
//    {
////        TWSR &= 0xFE;    // ob1111 1110
//        TWSR &= ~(1<<TWPS0);
//        TWSR |= (1<<TWPS1);
//    }
//    if(pre_scale == TWI_PRE_TWPS_16)
//    {
////        TWSR &= 0xFF;    // ob1111 1110
//        TWSR |= (1<<TWPS0)|(1<<TWPS1);
//    }
    _delay_ms(100);
}

// Two Wired Interface == I2C
void TWI_ACK()
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
}

void TWI_STA()
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
}

void TWI_STO()
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void TWI_wait()
{
    while(!(TWCR &(1<<TWINT))); 
}

char TWI_Send_SLA(char address)
{
    char bus_stats;
    // Started previously with the TWI_sta
    TWI_STA();
    TWI_wait();
    bus_stats = TWSR & 0xF8;
    if((bus_stats == TWI_status_start)|(bus_stats == TWI_status_rep_start))
    {
        TWDR = address;
        TWCR = (1<<TWINT)|(1<<TWEN);
        TWI_wait();
        bus_stats = TWSR & 0xF8;
        if( bus_stats == TWI_status_Master_SLA_W_Ack_Rec)
        {
            return 1;
        }
        else if(bus_stats == TWI_status_Master_SLA_W_Ack_Not_Rec)
        {
            // Not Ack command 
            // Here, we would do it as it would do Nothing!
            return 2;
        }
        else if(bus_stats == TWI_status_Master_SLA_R_Ack_Rec)
        {
            return 3;
        }
        else if(bus_stats == TWI_status_Master_SLA_R_Ack_Not_Rec)
        {
            return 4;
        }
    }
    else if(bus_stats == TWI_status_Master_Arb_lost)
    {
        //???? i would assume it's right
//        TWI_Send_SLA(address);
        return 0;
    }
}
char TWI_Master_write(char data)
{
    char bus_stats;
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    TWI_wait();
    bus_stats = TWSR & 0xF8;
    if(bus_stats == TWI_status_Master_Data_Ack_Rec)
    {
//        TWI_STO();
        return 1;
//        TWI_STO();
        // You can add repeated start code here to add up
    }
    else if(bus_stats == TWI_status_Master_Data_Ack_Not_Rec)
    {
//        TWI_STO();
        return 0;
//        TWI_STO();
    }
}
// Master Receiver
char TWI_Master_read()
{
    char bus_stats;
    TWI_ACK();
    TWI_wait();
    bus_stats = TWSR & 0xF8;
    if(bus_stats == TWI_status_Master_Data_Ack_Ret)
    {        
        return TWDR;

    }
    else if(bus_stats == TWI_status_Master_Data_Ack_Not_Ret)
    {
        TWI_STO();
//        return TWDR;
    }
}

/////////////////////////////////////////////////////////////////////

void init_TWI_slave(char address)
{
    TWAR = address;
    TWI_ACK();
}

char TWI_slave_check_address()
{
    // You can do in the nothing conditions. -> you could return numbers and with these numbers... add to function to change to whether you want
    // And in the not ack part... as you have a function that asks if you want to ack or not... and then it would implement at this point
    char bus_stats;
    TWI_wait();
    bus_stats = TWSR & 0xF8;
    if((bus_stats == TWI_status_Slave_SLA_W_Ack_Ret)|(bus_stats == TWI_status_Slave_Arb_lost_SLA_W_Ack_Ret))
    {
        return 1;
    }
//    else if(bus_stats == TWI_status_Slave_Arb_lost_SLA_W_Ack_Ret)
//    {
//        //Nothing
//        return 2;
//    }
    
    else if((bus_stats == TWI_status_Slave_GC_Address_Ack_Ret)|(bus_stats == TWI_status_Slave_Arb_lost_GC_Address_Ack_Ret))
    {
        return 3;
    }
//    else if(bus_stats == TWI_status_Slave_Arb_lost_GC_Address_Ack_Ret)
//    {
//        return 4;
//    }
    else if((bus_stats == TWI_status_Slave_SLA_R_Ack_Ret)|(bus_stats == TWI_status_Slave_Arb_lost_SLA_R_Ack_Ret))
    {
        return 5;
    }
//    else if(bus_stats == TWI_status_Slave_Arb_lost_SLA_R_Ack_Ret)
//    {
//        return 6;
//    }
}

// Slave Receiver
char TWI_slave_read()
{
    // Slave Receiver
    char bus_stats;
    TWI_ACK();
    TWI_wait();
    bus_stats = TWSR & 0xF8;
    if(bus_stats == TWI_status_Slave_SLA_W_Data_Rec_Ack_Ret)
    {
//        return TWDR;
        return TWDR;
    }
    else if(bus_stats == TWI_status_Slave_SLA_W_Data_Rec_Ack_Not_Ret)
    {
//        return TWDR;
        return TWDR;
        // Do anything you want
    }
    if(bus_stats == TWI_status_Slave_stop_repeated_start)
    {
        //Nothing or anything you want to
//        TWI_ACK();
    }  
//    if(bus_stats == TWI_status_Slave_SLA_W_Data_Rec_Ack_Ret)
//    {
//        return TWDR;
//    }
//    else if(bus_stats == TWI_status_Slave_SLA_W_Data_Rec_Ack_Not_Ret)
//    {
//        return 4;
//    }
}
char TWI_slave_write(char data)
{
    char bus_stats;
    TWDR = data;
//    TWI_ACK();
    TWCR |= (1<<TWINT)|(1<<TWEN);
    TWI_wait();
    bus_stats = TWSR & 0xF8;
    if(bus_stats == TWI_status_Slave_Data_Ack_Rec)
    {
        return 1;
    }
    else if(bus_stats == TWI_status_Slave_Data_Ack_Not_Rec)
    {
        //Nothing
        return 2;
    }
    else if(bus_stats == TWI_status_bus_error)
    {
        return 0;
    }

//    char bus_status ;
//    TWDR = data;
//    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
//    while(!(TWCR & (1<<TWINT)));
//    bus_status = TWSR & 0xF8;
//    if( bus_status == 0xB8)
//        return 1;
//    else 
//        return 0;
}
//     0b 0000 0011 1111 1111  -> 0b00000011
char EEPROM_call(char eeprom_address,short int address_bytes)
{
    // 0b 0000 0000 0000 0011
    char check_stats;
    check_stats = TWI_Send_SLA(eeprom_address);
    if(check_stats == 1)      // SLA_W was sent and acknowledge returned 
    {
        TWDR = (char)(address_bytes>>8);  // High Byte
        TWCR = (1<<TWINT)|(1<<TWEN);
        TWI_wait();
        check_stats = TWSR & 0xF8;
        if(check_stats == TWI_status_Master_Data_Ack_Rec)
        {
            TWDR = (char)address_bytes;
            TWCR = (1<<TWINT)|(1<<TWEN);
            TWI_wait();
            check_stats = TWSR & 0xF8;
            if(check_stats == TWI_status_Master_Data_Ack_Rec)
            {
                return EEPROM_WRITE;
                // Address is Successfully sent :>
            }
        }
        else if(check_stats == TWI_status_Master_Data_Ack_Not_Rec)
        {
            return 0;
        }
    }
    else if(check_stats == 3) // SLA_R was sent and acknowledge returned
    {
        return EEPROM_READ;
    }
}
char EEPROM_write_byte(char data)
{
    char check_stats;
    check_stats = TWI_Master_write(data);  // 1 or 0
    if(check_stats == 1)      // Acknowledge is received :>
    {
        TWI_STO();
        return 1;
    }
    else if(check_stats == 0) // Acknowledge not received 
    {
        // Nothing to do 
        TWI_STO();
        return 0;
    }
}
char EEPROM_write_page(char arr[32])
{
    // Algorithm of it, is to have an array include the page you want to write and increment in a loop till the last element in the array
//    char check_stats;
    // Here instead of sending 
}

char EEPROM_write_pass(short int password)
{
    // Sends two bytes instead of one byte (char) as pass exceeds the bytes 
    char check_stats;
    // Sends 1st byte of password
    check_stats = TWI_Master_write((char)password);  // First Pass Byte
    if(check_stats == 1)   // Acknowledge is received :>
    {
        // Acknowledge received
        // Sends 2nd byte of password 
        check_stats = TWI_Master_write((char)(password>>8)); // Second pass Byte
        if(check_stats == 1)
        {
            // Stop Condition
            TWI_STO();
        }
    }
    else if(check_stats == 0) // Not Ack
    {
        // Stop Condition 
    } 
}

short int EEPROM_read_pass()
{
    short int pass;
    pass = TWI_Master_read();        // 0b 0000 0000  xxxx xxxx
    pass |= (TWI_Master_read()<<8); // 0b xxxx xxxx 0000 0000
    TWI_STO();
    return pass;
}

char EEPROM_retrieve_byte()
{
    // we already sent the address of the byte that we want to read and then retrieve the data :>
    char data;
    data = TWI_Master_read();  // return TWDR (data)
    TWI_STO();    
    return data;
    
    // Data might be zero if no acknowledge is not received
}

char EEPROM_Check_empty()
{
    
}
