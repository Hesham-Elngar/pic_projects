#include"../Buzzer/buzzer.h"
Return_Status BUZ_init(BUZ *buz)
{
      Return_Status ret=R_NOK;
    if(buz!=NULL){
        ret=R_OK;
        pin_config_info buz_obj={
            .direction=gpio_direction_output,
            .logic=gpio_logic_low,
            .pin=buz->pin,
            .port=buz->port
        };
        gpio_set_pin_direction(&buz_obj);
    }
    return ret;
}

Return_Status BUZ_on(BUZ *buz)
{
    Return_Status ret=R_NOK;
    if(buz!=NULL){
        ret=R_OK;
          pin_config_info buz_obj={
            .direction=gpio_direction_output,
            .logic=gpio_logic_high,
            .pin=buz->pin,
            .port=buz->port
        };
          gpio_write_pin_logic(&buz_obj,buz_obj.logic);
        
    }
    return ret;
}
Return_Status BUZ_off(BUZ *buz)
{
    Return_Status ret=R_NOK;
    if(buz!=NULL){
        ret=R_OK;
          pin_config_info led_obj={
            .direction=gpio_direction_output,
            .logic=gpio_logic_low,
            .pin=buz->pin,
            .port=buz->port
        };
            gpio_write_pin_logic(&led_obj,led_obj.logic);
    }
    return ret;
}
