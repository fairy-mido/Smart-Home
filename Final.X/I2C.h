/* 
 * File:   I2C.h
 * Author: moham
 *
 * Created on March 25, 2023, 3:40 PM
 */

#ifndef I2C_H
#define	I2C_H


// TWI Config 

#define MAddress                                         0x06
#define SLA_W                                            0x04
#define SLA_R                                            0x05
#define SAddress_without_GC                              0x04
#define SAddress_with_GC                                 0x05


// EEPROM characteristics 
#define EEPROM_address_write                             0xA2               // 1010 001 + 0 -> 10100010
#define EEPROM_address_read                              0xA3               // 1010 001 + 1 -> 10100011

// Attributes of Users & Admin 
#define EEPROM_Admin_Address                             0x0119
#define EEPROM_User1_Address                             0x011C

#define EEPROM_Admin_password                            2307
#define EEPROM_User1_password                            2611

#define EEPROM_WRITE                                      1
#define EEPROM_READ                                       2


//  TWPS bits
#define TWI_PRE_TWPS_1                                    0
#define TWI_PRE_TWPS_4                                    1
#define TWI_PRE_TWPS_16                                   2
#define TWI_PRE_TWPS_64                                   3

// Status Register hex codes
#define TWI_status_start                                      0x08
#define TWI_status_rep_start                                  0x10
#define TWI_status_bus_error                                  0xF8

// Master Transmitter status
#define TWI_status_Master_SLA_W_Ack_Rec                       0x18
#define TWI_status_Master_SLA_W_Ack_Not_Rec                   0x20
#define TWI_status_Master_Data_Ack_Rec                        0x28
#define TWI_status_Master_Data_Ack_Not_Rec                    0x30
#define TWI_status_Master_Arb_lost                            0x38

// Master Receiver status 
#define TWI_status_Master_SLA_R_Ack_Rec                       0x40
#define TWI_status_Master_SLA_R_Ack_Not_Rec                   0x48
#define TWI_status_Master_Data_Ack_Ret                        0x50
#define TWI_status_Master_Data_Ack_Not_Ret                    0x58

// Slave Receiver status
#define TWI_status_Slave_SLA_W_Ack_Ret                        0x60
#define TWI_status_Slave_Arb_lost_SLA_W_Ack_Ret               0x68
#define TWI_status_Slave_GC_Address_Ack_Ret                   0x70
#define TWI_status_Slave_Arb_lost_GC_Address_Ack_Ret          0x78
#define TWI_status_Slave_SLA_W_Data_Rec_Ack_Ret               0x80
#define TWI_status_Slave_SLA_W_Data_Rec_Ack_Not_Ret           0x88
#define TWI_status_SLave_GC_Address_Data_Rec_Ack_Ret          0x90
#define TWI_status_SLave_GC_Address_Data_Rec_Ack_Not_Ret      0x98
#define TWI_status_Slave_stop_repeated_start                  0xA0

//Slave Transmitter
#define TWI_status_Slave_SLA_R_Ack_Ret                        0xA8
#define TWI_status_Slave_Arb_lost_SLA_R_Ack_Ret               0xB0
#define TWI_status_Slave_Data_Ack_Rec                         0xB8
#define TWI_status_Slave_Data_Ack_Not_Rec                     0xC0
#define TWI_status_Slave_Data_last_Ack_Rec                    0xC8


// Functions
void init_TWI_master(int bit_rate,int pre_scale,int master_address);
char TWI_Send_SLA(char address);
char TWI_Master_write(char data);
char TWI_Master_read();
void init_TWI_slave(char address);
char TWI_slave_check_address(); 
char TWI_slave_read();
char TWI_slave_write(char data);

char EEPROM_call(char eeprom_address,short int address_bytes);
char EEPROM_write_byte(char data);
char EEPROM_retrieve_byte();
char EEPROM_write_pass(short int password);
short int EEPROM_read_pass();

void TWI_ACK();
void TWI_STA();
void TWI_STO();
void TWI_wait();

#endif	/* I2C_H */

