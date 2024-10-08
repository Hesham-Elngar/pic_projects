/* 
 * File:   Timer1.h
 * Author: hesham
 *
 * Created on February 24, 2024, 1:06 PM
 */

#ifndef TIMER1_H
#define	TIMER1_H

#include"../interrupt/internal_interrupt.h"

#define TIMER1_TIMER_MODE_CFG 0
#define TIMER1_COUNTER_MODE_CFG 1

#define TIMER1_SYNC_COUNTER_MODE_CFG 0
#define TIMER1_ASYNC_COUNTER_MODE_CFG 1

#define TIMER1_OSCILLATOR_ENABLE_CFG 1
#define TIMER1_OSCILLATOR_DISABLE_CFG 0

#define TIMER1_8BIT_MODE_CFG 0
#define TIMER1_16BIT_MODE_CFG 1

#define TIMER1_ENABLE() T1CONbits.TMR1ON=1
#define TIMER1_DISABLE() T1CONbits.TMR1ON=0

#define TIMER1_TIMER_MODE() T1CONbits.TMR1CS=0
#define TIMER1_COUNTER_MODE() T1CONbits.TMR1CS=1

#define TIMER1_SYNC_COUNTER_MODE() T1CONbits.T1SYNC=0
#define TIMER1_ASYNC_COUNTER_MODE() T1CONbits.T1SYNC=1

#define TIMER1_OSCILLATOR_ENABLE() T1CONbits.T1OSCEN=1
#define TIMER1_OSCILLATOR_DISABLE() T1CONbits.T1OSCEN=0

#define TIMER1_SYSTEM_CLOCK_STATUS() T1CONbits.T1RUN

#define TIMER1_PRESCALER_SELECT(pre) (T1CONbits.T1CKPS=pre)

#define TIMER1_8BIT_MODE() T1CONbits.RD16=0
#define TIMER1_16BIT_MODE() T1CONbits.RD16=1

typedef enum{
    TIMER1_PRESCALER_DIV_BY_1,
    TIMER1_PRESCALER_DIV_BY_2,
    TIMER1_PRESCALER_DIV_BY_4,
    TIMER1_PRESCALER_DIV_BY_8,
}Timer1_Prescaler_select_t;

typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*Timer1_InterruptHandler)(void);
    Interrupt_Priority_Levels priority;
#endif
    Timer1_Prescaler_select_t prescaler_value;
    u16 preload_value;
    u8 mode:1;
    u8 edge:1;
    u8 counter_mode:1;
    u8 oscillator_cfg:1;
    u8 wr_mode:1;
    u8 reserved:3;
}Timer1_t; 


Return_Status timer1_Init(Timer1_t* timer1);
Return_Status timer1_DeInit(Timer1_t* timer1);
Return_Status timer1_Write_Value(Timer1_t* timer1,u16 value);
Return_Status timer1_Read_Value(Timer1_t* timer1,u16* value);
#endif	/* TIMER1_H */

