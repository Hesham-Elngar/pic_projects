#include"LED.h"

Return_Status LED_init(LED *led){
    Return_Status ret=R_NOK;
    if(led!=NULL){
        ret=R_OK;
        pin_config_info led_obj={
            .direction=gpio_direction_output,
            .logic=gpio_logic_low,
            .pin=led->pin,
            .port=led->port
        };
        gpio_set_pin_direction(&led_obj);
    }
    return ret;
}
Return_Status LED_on(LED *led){
    Return_Status ret=R_NOK;
    if(led!=NULL){
        ret=R_OK;
          pin_config_info led_obj={
            .direction=gpio_direction_output,
            .logic=gpio_logic_high,
            .pin=led->pin,
            .port=led->port
        };
          gpio_write_pin_logic(&led_obj,led_obj.logic);
        
    }
    return ret;
}
Return_Status LED_off(LED *led){
     Return_Status ret=R_NOK;
    if(led!=NULL){
        ret=R_OK;
          pin_config_info led_obj={
            .direction=gpio_direction_output,
            .logic=gpio_logic_low,
            .pin=led->pin,
            .port=led->port
        };
            gpio_write_pin_logic(&led_obj,led_obj.logic);
    }
    return ret;
}
Return_Status LED_toggle(LED *led){
    Return_Status ret=R_NOK;
    if(led!=NULL){
        ret=R_OK;
          pin_config_info led_obj={
            .direction=gpio_direction_output,
            .logic=gpio_logic_low,
            .pin=led->pin,
            .port=led->port
        };
          gpio_toggle_pin_value(&led_obj);
    }
    return ret;
}