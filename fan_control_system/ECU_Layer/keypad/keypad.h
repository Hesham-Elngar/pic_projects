/* 
 * File:   keypad.h
 * Author: hesham
 *
 * Created on November 27, 2023, 5:01 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 4


#include"../../MCAL_Layer/GPIO/GPIO.h"

typedef struct{
    pin_config_info keypad_row[KEYPAD_ROWS];
    pin_config_info keypad_column[KEYPAD_COLUMNS];
}Keypad_t;

Return_Status keypad_initialize(Keypad_t* keypad);
Return_Status keypad_get_value(Keypad_t *keypad,u8 *value);


#endif	/* KEYPAD_H */

