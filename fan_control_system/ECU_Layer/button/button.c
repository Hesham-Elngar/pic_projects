/* 
 * File:   button.c
 * Author: hesham
 *
 * Created on October 16, 2023, 5:40 AM
 */

#include"button.h"

Return_Status btn_init(BTN* btn){
    Return_Status ret=R_NOK;
    if(btn!=NULL){
        ret=R_OK;
        gpio_set_pin_direction(&btn->pin_config);
    }
    return ret;        
}
Return_Status btn_read_state(BTN* btn,BTN_STATUS* read_state){
     Return_Status ret=R_NOK;
     if(btn!=NULL&&read_state!=NULL){
        ret=R_OK;
        logic_t log_read;
        gpio_read_pin_logic(&btn->pin_config,&log_read);
        if(btn->active==BTN_ACTIVE_HIGH){
            if(log_read==gpio_logic_high){
                *read_state=BTN_PRESSESD;
            }
            else if(log_read==gpio_logic_low){
                *read_state=BTN_NOT_PRESSESD;
            }
        }
        else if(btn->active==BTN_ACTIVE_LOW){
            if(log_read==gpio_logic_high){
                *read_state=BTN_NOT_PRESSESD;
            }
            else if(log_read==gpio_logic_low){
                *read_state=BTN_PRESSESD;
            }
        }
        
    }
    return ret;
}