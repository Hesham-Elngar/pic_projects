/* 
 * File:   application.h
 * Author: hesham
 *
 * Created on October 20, 2023, 7:20 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H


#include"ECU_Layer/ecu_layer_init/ecu_layer_init.h"
#include "MCAL_Layer/Timers/timer0.h"

void app_initialize();

#define MAX_INPUT 2
#define NOT_PRESSED '\0'
#define PRESSED 1




#endif	/* APPLICATION_H */

