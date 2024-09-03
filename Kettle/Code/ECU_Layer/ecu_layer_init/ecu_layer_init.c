/* 
 * File:   ecu_layer_init.c
 * Author: hesham
 *
 * Created on November 26, 2023, 10:24 AM
 */


#include"../ecu_layer_init/ecu_layer_init.h"



Keypad_t keypad1={
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
};

dc_motor_t DRONE_M1={
.dc_motor_pin[DC_MOTOR_PIN1].logic=gpio_logic_low,.dc_motor_pin[DC_MOTOR_PIN1].direction=gpio_direction_output,
.dc_motor_pin[DC_MOTOR_PIN1].pin=PIN0_INDEX,.dc_motor_pin[DC_MOTOR_PIN1].port=PORTC_INDEX,
.dc_motor_pin[DC_MOTOR_PIN2].logic=gpio_logic_low,.dc_motor_pin[DC_MOTOR_PIN2].direction=gpio_direction_output,
.dc_motor_pin[DC_MOTOR_PIN2].pin=PIN1_INDEX,.dc_motor_pin[DC_MOTOR_PIN2].port=PORTC_INDEX
};
dc_motor_t DRONE_M2={
.dc_motor_pin[DC_MOTOR_PIN1].logic=gpio_logic_low,.dc_motor_pin[DC_MOTOR_PIN1].direction=gpio_direction_output,
.dc_motor_pin[DC_MOTOR_PIN1].pin=PIN2_INDEX,.dc_motor_pin[DC_MOTOR_PIN1].port=PORTC_INDEX,
.dc_motor_pin[DC_MOTOR_PIN2].logic=gpio_logic_low,.dc_motor_pin[DC_MOTOR_PIN2].direction=gpio_direction_output,
.dc_motor_pin[DC_MOTOR_PIN2].pin=PIN3_INDEX,.dc_motor_pin[DC_MOTOR_PIN2].port=PORTC_INDEX
};
dc_motor_t DRONE_M3={
.dc_motor_pin[DC_MOTOR_PIN1].logic=gpio_logic_low,.dc_motor_pin[DC_MOTOR_PIN1].direction=gpio_direction_output,
.dc_motor_pin[DC_MOTOR_PIN1].pin=PIN4_INDEX,.dc_motor_pin[DC_MOTOR_PIN1].port=PORTC_INDEX,
.dc_motor_pin[DC_MOTOR_PIN2].logic=gpio_logic_low,.dc_motor_pin[DC_MOTOR_PIN2].direction=gpio_direction_output,
.dc_motor_pin[DC_MOTOR_PIN2].pin=PIN5_INDEX,.dc_motor_pin[DC_MOTOR_PIN2].port=PORTC_INDEX
};

dc_motor_t Elec_Heater_motor={
.dc_motor_pin[DC_MOTOR_PIN1].logic=gpio_logic_low,.dc_motor_pin[DC_MOTOR_PIN1].direction=gpio_direction_output,
.dc_motor_pin[DC_MOTOR_PIN1].pin=PIN6_INDEX,.dc_motor_pin[DC_MOTOR_PIN1].port=PORTD_INDEX,
.dc_motor_pin[DC_MOTOR_PIN2].logic=gpio_logic_low,.dc_motor_pin[DC_MOTOR_PIN2].direction=gpio_direction_output,
.dc_motor_pin[DC_MOTOR_PIN2].pin=PIN7_INDEX,.dc_motor_pin[DC_MOTOR_PIN2].port=PORTD_INDEX
};

Lcd_4bit lcd1={
  .en.direction=gpio_direction_output,.en.logic=gpio_logic_low,.en.port=PORTD_INDEX,.en.pin=PIN0_INDEX,
.rs.direction=gpio_direction_output,.rs.logic=gpio_logic_low,.rs.port=PORTD_INDEX,.rs.pin=PIN1_INDEX,
.data[0].direction=gpio_direction_output,.data[0].logic=gpio_logic_low,.data[0].port=PORTD_INDEX,.data[0].pin=PIN2_INDEX,  
.data[1].direction=gpio_direction_output,.data[1].logic=gpio_logic_low,.data[1].port=PORTD_INDEX,.data[1].pin=PIN3_INDEX,  
.data[2].direction=gpio_direction_output,.data[2].logic=gpio_logic_low,.data[2].port=PORTD_INDEX,.data[2].pin=PIN4_INDEX,  
.data[3].direction=gpio_direction_output,.data[3].logic=gpio_logic_low,.data[3].port=PORTD_INDEX,.data[3].pin=PIN5_INDEX,  
};
LED led2={.pin=PIN1_INDEX,.port=PORTC_INDEX,.status=LED_OFF};
LED led3={.pin=PIN2_INDEX,.port=PORTC_INDEX,.status=LED_OFF};
BTN start_btn={.active=BTN_ACTIVE_HIGH,.status=BTN_NOT_PRESSESD,
.pin_config.direction=gpio_direction_input,.pin_config.logic=gpio_logic_low,.pin_config.pin=PIN0_INDEX,
.pin_config.port=PORTB_INDEX};
void ecu_layer_initialize()
{
      lcd_4bit_initialize(&lcd1);
      dc_motor_initialize(&Elec_Heater_motor);
      btn_init(&start_btn);
}