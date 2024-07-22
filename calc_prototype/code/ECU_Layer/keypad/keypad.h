/* 
 * File:   keypad.h
 * Author: hesham
 *
 * Created on November 27, 2023, 5:01 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H
#include"../../MCAL_Layer/GPIO/GPIO.h"

#define ADV_KEYPAD_ROWS    4
#define ADV_KEYPAD_COLUMNS 4    

#define SIN_SYMBOL 'a'
#define COS_SYMBOL 's'
#define TAN_SYMBOL 'd'
#define ATAN_SYMBOL 'f'
#define SINH_SYMBOL 'g'
#define COSH_SYMBOL 'h'
#define TANH_SYMBOL 'j'
#define ACOS_SYMBOL 'k'
#define SHIFT_CURSOR_LFET 'l'
#define SHIFT_CURSOR_RIGHT 'z'
#define POWER_SYMBOL '^'
#define ASIN_SYMBOL 'c'
#define DEC_SYS 'v'
#define BIN_SYS 'b'
#define HEX_SYS 'n'
#define OCT_SYS 'm'

typedef struct{
    pin_config_info keypad_row[ADV_KEYPAD_ROWS];
    pin_config_info keypad_column[ADV_KEYPAD_COLUMNS];
}ADV_Keypad_t;

Return_Status adv_keypad_initialize(ADV_Keypad_t* keypad);
Return_Status adv_keypad_get_value(ADV_Keypad_t *keypad,u8 *value);


#endif	/* KEYPAD_H */

