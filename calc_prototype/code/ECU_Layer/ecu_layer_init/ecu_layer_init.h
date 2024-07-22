/* 
 * File:   ecu_layer_init.h
 * Author: hesham
 *
 * Created on November 26, 2023, 10:24 AM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H


#include"../../MCAL_Layer/GPIO/GPIO.h"
#include"../LCD/LCD.h"
#include"../keypad/scientific_keypad.h"
#include"../keypad/keypad.h"

void ecu_layer_initialize();
extern Keypad_t scientfic_keypad;
extern ADV_Keypad_t adv_keypad;
extern Lcd_4bit lcd1;



#endif	/* ECU_LAYER_INIT_H */

