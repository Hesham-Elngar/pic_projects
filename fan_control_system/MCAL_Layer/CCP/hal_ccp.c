/* ----------------- Includes -----------------*/
#include "hal_ccp.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_InterruptHandler)(void) = NULL;
#endif
    
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*CCP2_InterruptHandler)(void) = NULL;
#endif
  
static void CCP_Interrupt_Config(const ccp_t *_ccp_obj);
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj);
#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP2_CFG_CAPTURE_MODE_SELECTED)
static Return_Status CCP_Capture_Mode_Config(const ccp_t *_ccp_obj);
#endif
static Return_Status CCP_Compare_Mode_Config(const ccp_t *_ccp_obj);
   
Return_Status CCP_Init(const ccp_t *_ccp_obj){
    Return_Status ret = R_NOK;
    if(NULL == _ccp_obj){
        ret = R_NOK;
    }
    else{
        /* CCP Module Disable */
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else { /* Nothing */ }
        
        /* CCP Module Capture Mode Initialization */
        if(CCP_CAPTURE_MODE_SELECTED == _ccp_obj->ccp_mode){
           #if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP2_CFG_CAPTURE_MODE_SELECTED)
            ret = CCP_Capture_Mode_Config(_ccp_obj);
#endif
        }
        /* CCP Module Compare Mode Initialization */
        else if(CCP_COMPARE_MODE_SELECTED == _ccp_obj->ccp_mode){
            ret = CCP_Compare_Mode_Config(_ccp_obj);
        }
#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
        /* CCP Module PWM Mode Initialization */
        else if(CCP_PWM_MODE_SELECTED == _ccp_obj->ccp_mode){
            CCP_PWM_Mode_Config(_ccp_obj);
            PR2 = (u8)((_XTAL_FREQ / (_ccp_obj->PWM_Frequency * 4.0 * _ccp_obj->timer2_prescaler_value * _ccp_obj->timer2_postscaler_value)) - 1);
        }
#endif
        else {/* Nothing */}
        
        /* PIN Configurations */
        ret = gpio_pin_initialize(&(_ccp_obj->ccp_pin));
        /* Interrupt Configurations for CCP1 and CCP2 Modules */
        CCP_Interrupt_Config(_ccp_obj);
        
        /* CCP Module Disable */
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else { /* Nothing */ }

        ret = R_OK;
    }
    return ret;
}

Return_Status CCP_DeInit(const ccp_t *_ccp_obj){
    Return_Status ret = R_NOK;
    if(NULL == _ccp_obj){
        ret = R_NOK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE); /* CCP1 Module Disable */
/* Interrupt Configurations */ 
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE();
#endif 
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE); /* CCP2 Module Disable */
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE();
#endif  
        }
        else { /* Nothing */ }
 
        ret = R_OK;
    }
    return ret;
}

#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED)
Return_Status CCP1_IsCapturedDataReady(u8 *_capture_status){
    Return_Status ret = R_NOK;
    if(NULL == _capture_status){
        ret = R_NOK;
    }
    else{
        if(CCP1_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status = CCP1_CAPTURE_READY;
            CCP1_InterruptFlagClear();
        }
        else{
            *_capture_status = CCP1_CAPTURE_NOT_READY;
        }
        ret = R_OK;
    }
    return ret;
}

Return_Status CCP1_Capture_Mode_Read_Value(u16 *capture_value){
    Return_Status ret = R_NOK;
    CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    if(NULL == capture_value){
        ret = R_NOK;
    }
    else{
        /* Copy captured value */
        capture_temp_value.ccpr_low = CCPR1L;
        capture_temp_value.ccpr_high = CCPR1H;
        /* Write the 16-bit capture value */
        *capture_value = capture_temp_value.ccpr_16Bit;
        ret = R_OK;
    }
    return ret;
}
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
Return_Status CCP_IsCompareComplete(u8 *_compare_status){
    Return_Status ret = R_NOK;
    if(NULL == _compare_status){
        ret = R_NOK;
    }
    else{
        if(CCP1_COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status = CCP1_COMPARE_READY;
            CCP1_InterruptFlagClear();
        }
        else{
            *_compare_status = CCP1_COMPARE_NOT_READY;
        }
        ret = R_OK;
    }
    return ret;
}

Return_Status CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, u16 compare_value){
    Return_Status ret = R_NOK;
    CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    
    if(NULL == _ccp_obj){
        ret = R_NOK;
    }
    else{
        /* Copy compared value */
        capture_temp_value.ccpr_16Bit = compare_value;

        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCPR1L = capture_temp_value.ccpr_low;
            CCPR1H = capture_temp_value.ccpr_high;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCPR2L = capture_temp_value.ccpr_low;
            CCPR2H = capture_temp_value.ccpr_high;
        }
        else{ /* Nothing */ }
        
        ret = R_OK;
    }
    return ret;
}
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
Return_Status CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const u8 _duty){
    Return_Status ret = R_NOK;
    u16 l_duty_temp = 0;
    
    if(NULL == _ccp_obj){
        ret = R_NOK;
    }
    else{
        l_duty_temp = (u16)((float)4 * ((float)PR2 + 1.0) * ((float)_duty / 100.0));
        
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.DC1B = (u8)(l_duty_temp & 0x0003);
            CCPR1L = (u8)(l_duty_temp >> 2);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.DC2B = (u8)(l_duty_temp & 0x0003);
            CCPR2L = (u8)(l_duty_temp >> 2);
        }
        else{ /* Nothing */ }
        
        ret = R_OK;
    }

    return ret;
}

Return_Status CCP_PWM_Start(const ccp_t *_ccp_obj){
    Return_Status ret = R_NOK;
    
    if(NULL == _ccp_obj){
        ret = R_NOK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else{ /* Nothing */ }
        ret = R_OK;
    }
    
    return ret;
}

Return_Status CCP_PWM_Stop(const ccp_t *_ccp_obj){
    Return_Status ret = R_NOK;
    
    if(NULL == _ccp_obj){
        ret = R_NOK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        }
        else{ /* Nothing */ }
        ret = R_OK;
    }

    return ret;
}
#endif

void CCP1_ISR(void){
    CCP1_INTERRUPT_FLAG_CLEAR();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
    else{ /* Nothing */ }
}
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void CCP2_ISR(void){
    CCP2_InterruptFlagClear();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
    else{ /* Nothing */ }
}
#endif
  


#if (CCP1_CFG_SELECTED_MODE==CCP1_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP2_CFG_CAPTURE_MODE_SELECTED)
static Return_Status CCP_Capture_Mode_Config(const ccp_t *_ccp_obj){
    Return_Status ret = R_NOK;
    if(NULL == _ccp_obj){
        ret = R_NOK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            switch(_ccp_obj->ccp_submode){
                case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_1_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_4_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_16_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                    break;
                default: ret = R_NOK; break;
            }
            ret = R_OK;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            switch(_ccp_obj->ccp_submode){
                case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                    CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_1_RISING_EDGE:
                    CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_4_RISING_EDGE:
                    CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_16_RISING_EDGE:
                    CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
                    break;
                default: ret = R_NOK; break;
            }
            ret = R_OK;
        }
        else{ /* Nothing */ }
    }
    return ret;
}
#endif

static Return_Status CCP_Compare_Mode_Config(const ccp_t *_ccp_obj){
    Return_Status ret = R_NOK;
    if(NULL == _ccp_obj){
        ret = R_NOK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            switch(_ccp_obj->ccp_mode_variant){
                case CCP_COMPARE_MODE_SET_PIN_HIGH:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                    break;
                case CCP_COMPARE_MODE_SET_PIN_LOW:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                    break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                    break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_GEN_EVENT:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                    break;
                default: ret = R_NOK; break;
            }
            ret = R_OK;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            switch(_ccp_obj->ccp_mode_variant){
                case CCP_COMPARE_MODE_SET_PIN_HIGH:
                    CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
                    break;
                case CCP_COMPARE_MODE_SET_PIN_LOW:
                    CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
                    break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                    CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
                    break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_GEN_EVENT:
                    CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
                    break;
                default: ret = R_NOK; break;
            }
            ret = R_OK;
        }
        else{ /* Nothing */ }
    }
    return ret;
}

static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj){
    if(CCP1_INST == _ccp_obj->ccp_inst){
        CCP1_SET_MODE(CCP_PWM_MODE);
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        CCP2_SET_MODE(CCP_PWM_MODE);
    }
    else{ /* Nothing */ }
}

static void CCP_Interrupt_Config(const ccp_t *_ccp_obj){
    if(CCP1_INST == _ccp_obj->ccp_inst){
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_FLAG_CLEAR();
        CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            CCP1_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            CCP1_LowPrioritySet();
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GLOBAL_ENABLE();
        INTERRUPT_PERIPHERAL_DISABLE();
#endif  
#endif  
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        CCP2_InterruptEnable();
        CCP2_InterruptFlagClear();
        CCP2_InterruptHandler = _ccp_obj->CCP_Handler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            CCP2_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            CCP2_LowPrioritySet();
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GLOBAL_ENABLE();
        INTERRUPT_PERIPHERAL_ENABLE();
#endif
#endif 
    }
    else { /* Nothing */ }
}

