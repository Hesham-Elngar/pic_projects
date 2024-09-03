#include"dc_motor.h"

Return_Status dc_motor_initialize(const dc_motor_t *_dc_motor){
    Return_Status ret = R_OK;
    if(NULL == _dc_motor){
        ret = R_NOK;
    }
    else{    
        gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret;
}

Return_Status dc_motor_move_right(const dc_motor_t *_dc_motor){
    Return_Status ret = R_OK;
    if(NULL == _dc_motor){
        ret = R_NOK;
    }
    else{
        gpio_write_pin_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), gpio_logic_high);
        gpio_write_pin_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), gpio_logic_low);
    }
    return ret;
}

Return_Status dc_motor_move_left(const dc_motor_t *_dc_motor){
    Return_Status ret = R_OK;
    if(NULL == _dc_motor){
        ret = R_NOK;
    }
    else{
        gpio_write_pin_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), gpio_logic_low);
        gpio_write_pin_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), gpio_logic_high);
    }
    return ret;
}

/**
 * @brief stop the motor movement
 * @param _dc_motor pointer to the motor configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Return_Status dc_motor_stop(const dc_motor_t *_dc_motor){
    Return_Status ret = R_OK;
    if(NULL == _dc_motor){
        ret = R_NOK;
    }
    else{
        gpio_write_pin_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), gpio_logic_low);
        gpio_write_pin_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), gpio_logic_low);
    }
    return ret;
}

