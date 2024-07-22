/* 
 * File:   LED.h
 * Author: hesham
 *
 * Created on October 11, 2023, 6:59 AM
 */

#ifndef LED_H
#define	LED_H

#include"../../MCAL_Layer/GPIO/GPIO.h"

typedef enum{
    LED_OFF,
    LED_ON
}LED_STATUS;

typedef struct{
    u8 port:3;
    u8 pin:3;
    LED_STATUS status; 
}LED;

Return_Status LED_init(LED *led);
Return_Status LED_on(LED *led);
Return_Status LED_off(LED *led);
Return_Status LED_toggle(LED *led);

       

#endif	/* LED_H */

