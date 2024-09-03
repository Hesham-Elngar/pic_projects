#include "ccp1.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ccp1_InterruptHandler)(void) = NULL;
#endif

Return_Status ccp1_Init(ccp1_t *ccp1) {
    Return_Status ret = R_NOK;
    if (ccp1) {
        ret = R_OK;
        if (ccp1->mode == CCP1_CAPTURE_MODE_CFG_SELECTED) {
            switch (ccp1->ccp1_mode_variant) {
                case CCP_CAPTURE_MODE_1_FALLING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
                case CCP_CAPTURE_MODE_1_RISING_EDGE:  CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
                case CCP_CAPTURE_MODE_4_RISING_EDGE:  CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
                case CCP_CAPTURE_MODE_16_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            }
        } else if (ccp1->mode == CCP1_COMPARE_MODE_CFG_SELECTED) {
            switch (ccp1->ccp1_mode_variant) {
                case CCP_COMPARE_MODE_GEN_EVENT: CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT); break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:  CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);  break;
                case CCP_COMPARE_MODE_SET_PIN_HIGH:  CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);  break;
                case CCP_COMPARE_MODE_SET_PIN_LOW: CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW); break;
                case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH); break;
            }
        } else if (ccp1->mode == CCP1_PWM_MODE_CFG_SELECTED) {
            if (ccp1->ccp1_mode_variant == CCP1_PWM_MODE_SELECTED) {
                CCP1_SET_MODE(CCP_PWM_MODE);

                #if CCP1_CFG_MODE_SELECTED == CCP1_PWM_MODE_CFG_SELECTED
                PR2 = (u8)((_XTAL_FREQ / (ccp1->pwm_frequency * 4.0 * ccp1->timer2_prescaler_value)) - 1);
                #endif
            }
        }

        gpio_pin_initialize(&(ccp1->pin));

        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_FLAG_CLEAR();
        ccp1_InterruptHandler = ccp1->ccp1_interrupt_hanlder;
        #endif

        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if (ccp1->priority == Interrupt_High_Priority) {
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            ccp1_HighPrioritySet();
        } else if (Interrupt_Low_Priority == ccp1->priority) {
            INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
            ccp1_LowPrioritySet();
        }
        #else
        INTERRUPT_GLOBAL_ENABLE();
        INTERRUPT_PERIPHERAL_ENABLE();
        #endif
    }
    return ret;
}

Return_Status ccp1_DeInit(ccp1_t *ccp1) {
    Return_Status ret = R_NOK;
    if (ccp1) {
        ret = R_OK;
        CCP1_INTERRUPT_DISABLE();

        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        #define CCP1_HighPrioritySet()    IPR1bits.CCP1IP = 1
        #define CCP1_LowPrioritySet()     IPR1bits.CCP1IP = 0
        #endif
    }
    return ret;
}

#if CCP1_CFG_MODE_SELECTED == CCP1_CAPTURE_MODE_CFG_SELECTED
Return_Status ccp1_IsCapturedDataReady(u8 *capture_status) {
    Return_Status ret = R_NOK;
    if (PIR1bits.CCP1IF == CCP1_CAPTURE_READY) {
        *capture_status = CCP1_CAPTURE_READY;
    } else {
        *capture_status = CCP1_CAPTURE_NOT_READY;
    }
    return ret;
}

Return_Status ccp1_CaptureModeReadValue(u16 *value) {
    Return_Status ret = R_NOK;
    ccp1_period_reg_t temp = {.ccp1_16Bit = 0};
    temp.ccp1_low = CCPR1L;
    temp.ccp1_high = CCPR1H;
    *value = temp.ccp1_16Bit;
    return ret;
}
#endif

#if CCP1_CFG_MODE_SELECTED == CCP1_COMPARE_MODE_CFG_SELECTED
Return_Status ccp1_CompareModeSetValue(u16 CompareValue) {
    Return_Status ret = R_NOK;
    ccp1_period_reg_t temp = {.ccp1_16Bit = CompareValue};
    CCPR1L = temp.ccp1_low;
    CCPR1H = temp.ccp1_high;
    return ret;
}

Return_Status ccp1_IsCompareComplete(u8 *compare_status) {
    Return_Status ret = R_NOK;
    if (PIR1bits.CCP1IF == CCP1_COMPARE_READY) {
        *compare_status = CCP1_COMPARE_READY;
    } else {
        *compare_status = CCP1_COMPARE_NOT_READY;
    }
    return ret;
}
#endif

#if CCP1_CFG_MODE_SELECTED == CCP1_PWM_MODE_CFG_SELECTED
Return_Status ccp1_Start_pwm() {
    Return_Status ret = R_OK;
    CCP1CONbits.CCP1M = CCP_PWM_MODE;
    return ret;
}

Return_Status ccp1_Stop_pwm() {
    Return_Status ret = R_OK;
    CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
    return ret;
}

Return_Status ccp1_setDuty(u8 Duty) {
    Return_Status ret = R_OK;
    u16 l_temp_duty = (u16)((4 * (PR2 + 1) * Duty) / 100);
    CCP1CONbits.DC1B = (u8)(l_temp_duty & 0x03); // Set the 2 LSBs
    CCPR1L = (u8)(l_temp_duty >> 2); // Set the 8 MSBs
    return ret;
}
#endif
