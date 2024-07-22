/* 
 * File:   GPIO.h
 * Author: hesham
 *
 * Created on October 11, 2023, 6:45 AM
 */

#ifndef GPIO_H
#define	GPIO_H
#include"../STD_Types.h"
#define _XTAL_FREQ 8000000UL

#define PIN_CONFIGURATIONS  CONFIG_ENABLE
#define PORT_CONFIGURATIONS CONFIG_ENABLE

typedef enum{
    gpio_logic_low,
    gpio_logic_high
}logic_t;

typedef enum{
    gpio_direction_output,
    gpio_direction_input
}direction_t;

typedef enum{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX, 
    PORTE_INDEX,
}port_index_t;

typedef enum{
    PIN0_INDEX,
    PIN1_INDEX,
    PIN2_INDEX,
    PIN3_INDEX,
    PIN4_INDEX,
    PIN5_INDEX,
    PIN6_INDEX,
    PIN7_INDEX,
}pin_index_t;

typedef enum{
    R_NOK,
    R_OK
}Return_Status;

typedef struct{
    u8 pin;
    u8 port;
    logic_t logic;
    direction_t direction;
}pin_config_info;

Return_Status gpio_set_pin_direction( pin_config_info *pin_config);
Return_Status gpio_get_pin_direction(pin_config_info *pin_config,direction_t *direction);
Return_Status gpio_write_pin_logic(pin_config_info* pin_config,logic_t logic);
Return_Status gpio_read_pin_logic(pin_config_info* pin_config,logic_t *logic);
Return_Status gpio_toggle_pin_value(pin_config_info *pin_config);
Return_Status gpio_pin_initialize(pin_config_info *pin_config);



#endif	/* GPIO_H */

