/* 
 * File:   app.h
 * Author: hesham
 *
 * Created on February 19, 2024, 11:16 AM
 */

#ifndef APP_H
#define	APP_H
#include"Hal_Layer/Hal_layer_init/hal_layer_init.h"

#define NOT_PRESSESD '\0'
#define PRESSESD   1
#define EEPROM_STATUS_LOCATION 0x40
#define EEPROM_PASS_START_LOCATION 0x21
#define PASSWORD_MAX_NUMBER 4
#define TRIES_MAX_NUMBER 3

void app_initialize();
u8 is_pass_pressed();
void set_password();
void enter_password(u8 check_values[]);
u8 check_password(u8 check_values[]);

#endif	/* APP_H */

