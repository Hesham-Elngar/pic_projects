/* 
 * File:   hal_layer_init.h
 * Author: hesham
 *
 * Created on February 19, 2024, 11:31 AM
 */

#ifndef HAL_LAYER_INIT_H
#define	HAL_LAYER_INIT_H

#include"../keypad/keypad.h"
#include"../LCD/LCD.h"
#include"../LED/LED.h"    

void hal_init();

extern Keypad_t keypad_obj;
extern Lcd_4bit lcd_obj;
extern LED red_led;
extern LED yellow_led;


#endif	/* HAL_LAYER_INIT_H */

