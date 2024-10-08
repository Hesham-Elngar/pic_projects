   /* 
 * File:   ccp1.h
 * Author: hesham
 *
 * Created on February 26, 2024, 11:04 AM
 */

#ifndef CCP1_H
#define	CCP1_H

#include"ccp1_cfg.h"
#include"../GPIO/GPIO.h"
#include"../interrupt/internal_interrupt.h"

#define CCP_MODULE_DISABLE                 ((u8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((u8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((u8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((u8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((u8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((u8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((u8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((u8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((u8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((u8)0x0B)
#define CCP_PWM_MODE                       ((u8)0x0C)

#define CCP_TIMER2_POSTSCALER_DIV_BY_1 1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2 2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3 3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4 4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5 5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6 6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7 7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8 8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9 9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10 10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11 11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12 12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13 13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14 14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15 15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16 16

#define CCP_TIMER2_PRESCALER_DIV_BY_1 1
#define CCP_TIMER2_PRESCALER_DIV_BY_4 4
#define CCP_TIMER2_PRESCALER_DIV_BY_16 16

/* CCP1 Capture Mode State  */
#define CCP1_CAPTURE_NOT_READY              0X00
#define CCP1_CAPTURE_READY                  0X01

/* CCP1 Compare Mode State  */
#define CCP1_COMPARE_NOT_READY              0X00
#define CCP1_COMPARE_READY                  0X01

/* Set the CCP1 Mode Variant */
#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)  (CCP2CONbits.CCP2M = _CONFIG)


typedef enum{
        CCP1_CAPTURE_MODE_SELECTED,
        CCP1_COMPARE_MODE_SELECTED,
        CCP1_PWM_MODE_SELECTED    
}ccp1_mode_t;

typedef union{
    struct{
        u8 ccp1_low;
        u8 ccp1_high;
    };
    struct{
        u16 ccp1_16Bit;
    };
}ccp1_period_reg_t;

typedef struct{
   ccp1_mode_t mode;
   u8 ccp1_mode_variant;
   pin_config_info pin;
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
   void(*ccp1_interrupt_hanlder)(void);
   Interrupt_Priority_Levels priority;
#endif
#if CCP1_CFG_MODE_SELECTED==CCP1_PWM_MODE_CFG_SELECTED
   u32 pwm_frequency;
   u8 timer2_prescaler_value:2;
   u8 timer2_postscaler_value:4;
#endif
}ccp1_t;


Return_Status ccp1_Init(ccp1_t *ccp1);
Return_Status ccp1_DeInit(ccp1_t *ccp1);

#if CCP1_CFG_MODE_SELECTED==CCP1_CAPTURE_MODE_CFG_SELECTED
Return_Status ccp1_IsCapturedDataReady(u8 *capture_status);
Return_Status ccp1_CaptureModeReadValue(u16 *value);
#endif

#if CCP1_CFG_MODE_SELECTED==CCP1_COMPARE_MODE_CFG_SELECTED
Return_Status ccp1_CompareModeSetValue(u16 CompareValue);
Return_Status ccp1_IsCompareComplete(u8* compare_status);
#endif

#if CCP1_CFG_MODE_SELECTED==CCP1_PWM_MODE_CFG_SELECTED
Return_Status ccp1_Start_pwm();
Return_Status ccp1_Stop_pwm();
Return_Status ccp1_setDuty(u8 Duty);
#endif



#endif	/* CCP1_H */

