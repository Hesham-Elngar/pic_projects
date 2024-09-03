/* 
 * File:   Timer2.h
 * Author: hesham
 *
 * Created on February 27, 2024, 10:39 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H

#include"../interrupt/internal_interrupt.h"
#include"../GPIO/GPIO.h"

#define TIMER2_POSTSCALER_DIV_BY_1 0
#define TIMER2_POSTSCALER_DIV_BY_2 1
#define TIMER2_POSTSCALER_DIV_BY_3 2
#define TIMER2_POSTSCALER_DIV_BY_4 3
#define TIMER2_POSTSCALER_DIV_BY_5 4
#define TIMER2_POSTSCALER_DIV_BY_6 5
#define TIMER2_POSTSCALER_DIV_BY_7 6
#define TIMER2_POSTSCALER_DIV_BY_8 7
#define TIMER2_POSTSCALER_DIV_BY_9 8
#define TIMER2_POSTSCALER_DIV_BY_10 9
#define TIMER2_POSTSCALER_DIV_BY_11 10
#define TIMER2_POSTSCALER_DIV_BY_12 11
#define TIMER2_POSTSCALER_DIV_BY_13 12
#define TIMER2_POSTSCALER_DIV_BY_14 13
#define TIMER2_POSTSCALER_DIV_BY_15 14
#define TIMER2_POSTSCALER_DIV_BY_16 15

#define TIMER2_PRESCALER_DIV_BY_1 0
#define TIMER2_PRESCALER_DIV_BY_4 1
#define TIMER2_PRESCALER_DIV_BY_16 2

#define TIMER2_PRESCALER_SELECT(pre) (T2CONbits.T2CKPS=pre)
#define TIMER2_POSTCALER_SELECT(post) (T2CONbits.TOUTPS=post)

#define TIMER2_ENABLE() T2CONbits.TMR2ON=1
#define TIMER2_DISABLE() T2CONbits.TMR2ON=0

typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (*Timer2_Interrupt_Handler)(void);
    Interrupt_Priority_Levels priority;
#endif
    u8 preload_value;
    u8 prescaler_value:2;
    u8 postscaler_value:4;
    u8 reserved:2;
}Timer2_t;

Return_Status Timer2_Init(Timer2_t* timer2);
Return_Status Timer2_DeInit(Timer2_t* timer2);
Return_Status Timer2_Read_Value(Timer2_t* timer2,u8 *value);
Return_Status Timer2_Write_Value(Timer2_t* timer2,u8 value);

#endif	/* TIMER2_H */

