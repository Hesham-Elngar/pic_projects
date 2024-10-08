/* 
 * File:   timer0.h
 * Author: hesham
 *
 * Created on February 9, 2024, 9:42 AM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#include"../GPIO/GPIO.h"
#include"../interrupt/internal_interrupt.h"

#define TIMER0_PRESCALER_ENABLE_CFG 1
#define TIMER0_PRESCALER_DISABLE_CFG 0

#define TIMER0_SelectRisingEdge_CFG  1
#define TIMER0_SelectFallingEdge_CFG 0

#define TIMER0_TIMER_MODE_CFG 1
#define TIMER0_COUNTER_MODE_CFG 0

#define TIMER0_8BIT_MODE_CFG 1
#define TIMER0_16BIT_MODE_CFG 0

#define TIMER0_PRESCALER_ENABLE() T0CONbits.PSA=0
#define TIMER0_PRESCALER_DISABLE() T0CONbits.PSA=1

#define TIMER0_SelectRisingEdge() T0CONbits.T0SE=0
#define TIMER0_SelectFallingEdge() T0CONbits.T0SE=1

#define TIMER0_8BIT_MODE() T0CONbits.T08BIT=1
#define TIMER0_16BIT_MODE() T0CONbits.T08BIT=0

#define TIMER0_ENABLE_MODULE() T0CONbits.TMR0ON=1
#define TIMER0_DISABLE_MODULE() T0CONbits.TMR0ON=0

#define TIMER0_TIMER_MODE_SELECT() T0CONbits.T0CS=0
#define TIMER0_COUNTER_MODE_SELECT() T0CONbits.T0CS=1

typedef  enum{
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
}timer0_prescaler_select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
     void (*Timer0_InterruptHandler)(void);
    Interrupt_Priority_Levels priority;
#endif
    timer0_prescaler_select_t prescaler_value;
    u16 preload_value;
    u8 prescaler_enable:1;
    u8 edge:1;
    u8 mode:1;
    u8 register_size:1;
    u8 resrved:4;
    
}TIMER0_t;

Return_Status timer0_Init(TIMER0_t* timer0);
Return_Status timer0_DeInit(TIMER0_t* timer0);
Return_Status timer0_Write_Value(TIMER0_t* timer0,u16 value);
Return_Status timer0_Read_Value(TIMER0_t* timer0,u16* value);


#endif	/* TIMER0_H */

