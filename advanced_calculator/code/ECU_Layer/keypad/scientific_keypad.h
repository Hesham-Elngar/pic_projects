/* 
 * File:   scientific_keypad.h
 * Author: hesham
 *
 * Created on March 20, 2024, 11:20 AM
 */

#ifndef SCIENTIFIC_KEYPAD_H
#define	SCIENTIFIC_KEYPAD_H

#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 6

#define SQRT_SYMBOL     '?'
#define DEL_SYMBOL      'd'
#define DEL_ALL_SYMBOL  '#'
#define EXP_SYMBOL      'e'
#define ANS_SYMBOL      'w'

#define SQRT_STRING     "sqrt("
#define EXP_STRING      "M_E"
#define ANS_STRING     "ANS"


#include"../../MCAL_Layer/GPIO/GPIO.h"

typedef struct{
    pin_config_info keypad_row[KEYPAD_ROWS];
    pin_config_info keypad_column[KEYPAD_COLUMNS];
}Keypad_t;

Return_Status keypad_initialize(Keypad_t* keypad);
Return_Status keypad_get_value(Keypad_t *keypad,u8 *value);


#endif	/* SCIENTIFIC_KEYPAD_H */

