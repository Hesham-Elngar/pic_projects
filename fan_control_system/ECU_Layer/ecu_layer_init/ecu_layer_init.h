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
#include"../SSD/ssd_interface.h"
#include"../button/button.h"
#include"../keypad/keypad.h"
#include"../DC_Motor/dc_motor.h"

#include"../LED/LED.h"
void ecu_layer_initialize();
extern Keypad_t keypad1;
extern Lcd_4bit lcd1;
extern dc_motor_t Fan_motor;

#endif	/* ECU_LAYER_INIT_H */

