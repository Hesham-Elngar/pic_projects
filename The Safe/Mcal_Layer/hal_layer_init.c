#include"../Hal_Layer/Hal_layer_init/hal_layer_init.h"

LED yellow_led={.status=LED_OFF,.port=PORTD_INDEX,.pin=PIN6_INDEX};
LED red_led={.status=LED_OFF,.port=PORTD_INDEX,.pin=PIN7_INDEX};

Lcd_4bit lcd_obj={
.rs.direction=gpio_direction_output,.rs.logic=gpio_logic_low,.rs.port=PORTC_INDEX,.rs=PIN0_INDEX,
.en.direction=gpio_direction_output,.en.logic=gpio_logic_low,.en.port=PORTC_INDEX,.en=PIN1_INDEX,
.data[0].direction=gpio_direction_output,.data[0].logic=gpio_logic_low,.data[0].port=PORTC_INDEX,.data[0].pin=PIN2_INDEX,
.data[1].direction=gpio_direction_output,.data[1].logic=gpio_logic_low,.data[1].port=PORTC_INDEX,.data[1].pin=PIN3_INDEX,
.data[2].direction=gpio_direction_output,.data[2].logic=gpio_logic_low,.data[2].port=PORTC_INDEX,.data[2].pin=PIN4_INDEX,
.data[3].direction=gpio_direction_output,.data[3].logic=gpio_logic_low,.data[3].port=PORTC_INDEX,.data[3].pin=PIN5_INDEX,
};

Keypad_t keypad_obj={
  .keypad_row[0].direction=gpio_direction_output,.keypad_row[0].logic=gpio_logic_low,
  .keypad_row[0].port=PORTC_INDEX,.keypad_row[0].pin=PIN6_INDEX,
  .keypad_row[1].direction=gpio_direction_output,.keypad_row[1].logic=gpio_logic_low,
  .keypad_row[1].port=PORTC_INDEX,.keypad_row[1].pin=PIN7_INDEX,
  .keypad_row[2].direction=gpio_direction_output,.keypad_row[2].logic=gpio_logic_low,
  .keypad_row[2].port=PORTD_INDEX,.keypad_row[2].pin=PIN0_INDEX,
  .keypad_row[3].direction=gpio_direction_output,.keypad_row[3].logic=gpio_logic_low,
  .keypad_row[3].port=PORTD_INDEX,.keypad_row[3].pin=PIN1_INDEX,
  .keypad_column[0].direction=gpio_direction_input,.keypad_column[0].logic=gpio_logic_low,
  .keypad_column[0].port=PORTD_INDEX,.keypad_column[0].pin=PIN2_INDEX,
  .keypad_column[1].direction=gpio_direction_input,.keypad_column[1].logic=gpio_logic_low,
  .keypad_column[1].port=PORTD_INDEX,.keypad_column[1].pin=PIN3_INDEX,
  .keypad_column[2].direction=gpio_direction_input,.keypad_column[2].logic=gpio_logic_low,
  .keypad_column[2].port=PORTD_INDEX,.keypad_column[2].pin=PIN4_INDEX,
  .keypad_column[3].direction=gpio_direction_input,.keypad_column[3].logic=gpio_logic_low,
  .keypad_column[3].port=PORTD_INDEX,.keypad_column[3].pin=PIN5_INDEX,
    
};

void hal_init(){
    lcd_4bit_initialize(&lcd_obj);
    keypad_initialize(&keypad_obj); 
    LED_init(&yellow_led);
    LED_init(&red_led);
}