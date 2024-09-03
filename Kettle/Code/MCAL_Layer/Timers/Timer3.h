/* 
 * File:   Timer3.h
 * Author: hesham
 *
 * Created on February 27, 2024, 10:40 PM
 */

#ifndef TIMER3_H
#define	TIMER3_H

#include"../interrupt/internal_interrupt.h"
#include"../GPIO/GPIO.h"

#define TIMER3_8BIT_MODE_CFG  0 
#define TIMER3_16BIT_MODE_CFG 1 

#define TIMER3_ENABLE_CFG  1
#define TIMER3_DISABLE_CFG 0

#define TIMER3_TIMER_MODE_CFG   0
#define TIMER3_COUNTER_MODE_CFG 1

#define TIMER3_SYNC_COUNTER_MODE_CFG   0
#define TIMER3_ASYNC_COUNTER_MODE_CFG  1

#define TIMER3_PRESCALER_DIV_BY_1 0
#define TIMER3_PRESCALER_DIV_BY_2 1
#define TIMER3_PRESCALER_DIV_BY_4 2
#define TIMER3_PRESCALER_DIV_BY_8 3

#define TIMER3_PRESCALER_SELECT(pre) (T3CONbits.T3CKPS=pre)

#define TIMER3_8BIT_MODE  T3CONbits.RD16=0 
#define TIMER3_16BIT_MODE T3CONbits.RD16=1 
    
#define TIMER3_ENABLE() T3CONbits.TMR3ON=1
#define TIMER3_DISABLE() T3CONbits.TMR3ON=0

#define TIMER3_TIMER_MODE() T3CONbits.TMR3CS=0
#define TIMER3_COUNTER_MODE() T3CONbits.TMR3CS=1

#define TIMER3_SYNC_COUNTER_MODE() T3CONbits.T3SYNC=0
#define TIMER3_ASYNC_COUNTER_MODE() T3CONbits.T3SYNC=1

typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*Timer3_InterruptHandler)(void);
    Interrupt_Priority_Levels priority;
#endif
    u16 preload_value;
    u8 prescaler_value:2;
    u8 mode:1;
    u8 register_size:1;
    u8 counter_mode:1;
    u8 reserved :3;
}Timer3_t;

Return_Status timer3_Init(Timer3_t* timer3);
Return_Status timer3_DeInit(Timer3_t* timer3);
Return_Status timer3_Write_Value(Timer3_t* timer3,u16 value);
Return_Status timer3_Read_Value(Timer3_t* timer3,u16* value);


#endif	/* TIMER3_H */

