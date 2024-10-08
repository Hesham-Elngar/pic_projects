/* 
 * File:   buzzer.h
 * Author: super magic
 *
 * Created on August 18, 2024, 6:31 PM
 */

#ifndef BUZZER_H
#define	BUZZER_H

#include"../../MCAL_Layer/GPIO/GPIO.h"

typedef enum{
    BUZ_OFF,
    BUZ_ON
}BUZ_STATUS;

typedef struct{
    u8 port:3;
    u8 pin:3;
    BUZ_STATUS status; 
}BUZ;

Return_Status BUZ_init(BUZ *buz);
Return_Status BUZ_on(BUZ *buz);
Return_Status BUZ_off(BUZ *buz);

#endif	/* BUZZER_H */

