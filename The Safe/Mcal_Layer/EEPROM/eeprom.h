/* 
 * File:   eeprom.h
 * Author: hesham
 *
 * Created on February 1, 2024, 2:34 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include"pic18f4620.h"
#include"../STD_Types.h"
#include"../interrupt/internal_interrupt.h"
#include"../GPIO/GPIO.h"



Return_Status EEPROM_WriteByte(u16 address,u8 data);
Return_Status EEPROM_ReadByte(u16 address,u8 *data);
#endif	/* EEPROM_H */

