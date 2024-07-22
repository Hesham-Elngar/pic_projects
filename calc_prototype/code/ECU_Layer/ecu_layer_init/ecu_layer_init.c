/* 
 * File:   ecu_layer_init.c
 * Author: hesham
 *
 * Created on November 26, 2023, 10:24 AM
 */


#include"../ecu_layer_init/ecu_layer_init.h"

Lcd_4bit lcd1={
  .en.direction=gpio_direction_output,.en.logic=gpio_logic_low,.en.port=PORTC_INDEX,.en.pin=PIN0_INDEX,
.rs.direction=gpio_direction_output,.rs.logic=gpio_logic_low,.rs.port=PORTC_INDEX,.rs.pin=PIN1_INDEX,
.data[0].direction=gpio_direction_output,.data[0].logic=gpio_logic_low,.data[0].port=PORTC_INDEX,.data[0].pin=PIN2_INDEX,  
.data[1].direction=gpio_direction_output,.data[1].logic=gpio_logic_low,.data[1].port=PORTC_INDEX,.data[1].pin=PIN3_INDEX,  
.data[2].direction=gpio_direction_output,.data[2].logic=gpio_logic_low,.data[2].port=PORTC_INDEX,.data[2].pin=PIN4_INDEX,  
.data[3].direction=gpio_direction_output,.data[3].logic=gpio_logic_low,.data[3].port=PORTC_INDEX,.data[3].pin=PIN5_INDEX,  
};

Keypad_t scientfic_keypad={
    .keypad_row[0].direction=gpio_direction_output,.keypad_row[0].logic=gpio_logic_low,
    .keypad_row[0].port=PORTD_INDEX,.keypad_row[0].pin=PIN0_INDEX,
    .keypad_row[1].direction=gpio_direction_output,.keypad_row[1].logic=gpio_logic_low,
    .keypad_row[1].port=PORTD_INDEX,.keypad_row[1].pin=PIN1_INDEX,
    .keypad_row[2].direction=gpio_direction_output,.keypad_row[2].logic=gpio_logic_low,
    .keypad_row[2].port=PORTD_INDEX,.keypad_row[2].pin=PIN2_INDEX,
    .keypad_row[3].direction=gpio_direction_output,.keypad_row[3].logic=gpio_logic_low,
    .keypad_row[3].port=PORTD_INDEX,.keypad_row[3].pin=PIN3_INDEX,
    .keypad_column[0].direction=gpio_direction_input,.keypad_column[0].logic=gpio_logic_low,
    .keypad_column[0].port=PORTD_INDEX,.keypad_column[0].pin=PIN4_INDEX,
    .keypad_column[1].direction=gpio_direction_input,.keypad_column[1].logic=gpio_logic_low,
    .keypad_column[1].port=PORTD_INDEX,.keypad_column[1].pin=PIN5_INDEX,
    .keypad_column[2].direction=gpio_direction_input,.keypad_column[2].logic=gpio_logic_low,
    .keypad_column[2].port=PORTD_INDEX,.keypad_column[2].pin=PIN6_INDEX,
    .keypad_column[3].direction=gpio_direction_input,.keypad_column[3].logic=gpio_logic_low,
    .keypad_column[3].port=PORTD_INDEX,.keypad_column[3].pin=PIN7_INDEX,
    .keypad_column[4].direction=gpio_direction_input,.keypad_column[4].logic=gpio_logic_low,
    .keypad_column[4].port=PORTC_INDEX,.keypad_column[4].pin=PIN6_INDEX,
    .keypad_column[5].direction=gpio_direction_input,.keypad_column[5].logic=gpio_logic_low,
    .keypad_column[5].port=PORTC_INDEX,.keypad_column[5].pin=PIN7_INDEX,
    
};
ADV_Keypad_t adv_keypad={
    .keypad_row[0].direction=gpio_direction_output,.keypad_row[0].logic=gpio_logic_low,
    .keypad_row[0].port=PORTB_INDEX,.keypad_row[0].pin=PIN0_INDEX,
    .keypad_row[1].direction=gpio_direction_output,.keypad_row[1].logic=gpio_logic_low,
    .keypad_row[1].port=PORTB_INDEX,.keypad_row[1].pin=PIN1_INDEX,
    .keypad_row[2].direction=gpio_direction_output,.keypad_row[2].logic=gpio_logic_low,
    .keypad_row[2].port=PORTB_INDEX,.keypad_row[2].pin=PIN2_INDEX,
    .keypad_row[3].direction=gpio_direction_output,.keypad_row[3].logic=gpio_logic_low,
    .keypad_row[3].port=PORTB_INDEX,.keypad_row[3].pin=PIN3_INDEX,
    .keypad_column[0].direction=gpio_direction_input,.keypad_column[0].logic=gpio_logic_low,
    .keypad_column[0].port=PORTB_INDEX,.keypad_column[0].pin=PIN4_INDEX,
    .keypad_column[1].direction=gpio_direction_input,.keypad_column[1].logic=gpio_logic_low,
    .keypad_column[1].port=PORTB_INDEX,.keypad_column[1].pin=PIN5_INDEX,
    .keypad_column[2].direction=gpio_direction_input,.keypad_column[2].logic=gpio_logic_low,
    .keypad_column[2].port=PORTB_INDEX,.keypad_column[2].pin=PIN6_INDEX,
    .keypad_column[3].direction=gpio_direction_input,.keypad_column[3].logic=gpio_logic_low,
    .keypad_column[3].port=PORTB_INDEX,.keypad_column[3].pin=PIN7_INDEX,

};

void ecu_layer_initialize()
{
    lcd_4bit_initialize(&lcd1);
    keypad_initialize(&scientfic_keypad);
    keypad_initialize(&adv_keypad);
}