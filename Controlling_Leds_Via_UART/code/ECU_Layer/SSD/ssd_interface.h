/* 
 * File:   ssd_interface.h
 * Author: hesham
 *
 * Created on October 18, 2023, 5:04 AM
 */

#ifndef SSD_INTERFACE_H
#define	SSD_INTERFACE_H

#include"../../MCAL_Layer/GPIO/GPIO.h"

typedef enum{
	SSD_COMMON_ANODE,
	SSD_COMMON_CATHODE
	}SSD_Type_t;    

typedef struct{
    pin_config_info SSD_Pins[4];
	SSD_Type_t type;
}SSD;

Return_Status ssd_init(SSD *ssd);
Return_Status ssd_WriteNumber(SSD *ssd,u8 value);

#endif	/* SSD_INTERFACE_H */

