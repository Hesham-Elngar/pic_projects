/* 
 * File:   dc_motor.h
 * Author: hesham
 *
 * Created on May 10, 2024, 1:54 AM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H


/* ----------------- Includes -----------------*/
#include"../../MCAL_Layer/GPIO/GPIO.h"
/* ----------------- Macro Declarations -----------------*/
#define DC_MOTOR_ON_STATUS  1
#define DC_MOTOR_OFF_STATUS 0

#define DC_MOTOR_PIN1 0
#define DC_MOTOR_PIN2 1

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_info dc_motor_pin[2];
}dc_motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Return_Status dc_motor_initialize(const dc_motor_t *_dc_motor);
Return_Status dc_motor_move_right(const dc_motor_t *_dc_motor);
Return_Status dc_motor_move_left(const dc_motor_t *_dc_motor);
Return_Status dc_motor_stop(const dc_motor_t *_dc_motor);
    

#endif	/* DC_MOTOR_H */

