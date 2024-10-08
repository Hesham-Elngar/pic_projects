/* 
 * File:   external_interrupt.h
 * Author: hesham
 *
 * Created on January 6, 2024, 5:02 PM
 */

#ifndef EXTERNAL_INTERRUPT_H
#define	EXTERNAL_INTERRUPT_H
#include"interrupt_config.h"
#if INTERRUPT_EXTERNAL_INTx_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXT_INT0_INTERRUPT_FLAG_CLEAR()         INTCONbits.INT0IF=0
#define EXT_INT0_INTERRUPT_ENABLE()             INTCONbits.INT0IE=1
#define EXT_INT0_INTERRUPT_DISABLE()            INTCONbits.INT0IE=0
#define EXT_INT0_INTERRUPT_RisingEdgeSet()      INTCON2bits.INTEDG0=1
#define EXT_INT0_INTERRUPT_FallingEdgeSet()     INTCON2bits.INTEDG0=0

#define EXT_INT1_INTERRUPT_FLAG_CLEAR()         INTCON3bits.INT1IF=0
#define EXT_INT1_INTERRUPT_ENABLE()             INTCON3bits.INT1IE=1
#define EXT_INT1_INTERRUPT_DISABLE()            INTCON3bits.INT1IE=0
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXT_INT1_INTERRUPT_HIGH_PRIORITY_SET()    INTCON3bits.INT1IP=1
#define EXT_INT1_INTERRUPT_LOW_PRIORITY_SET()   INTCON3bits.INT1IP=0
#endif
#define EXT_INT1_INTERRUPT_RisingEdgeSet()      INTCON2bits.INTEDG1=1
#define EXT_INT1_INTERRUPT_FallingEdgeSet()     INTCON2bits.INTEDG1=0

#define EXT_INT2_INTERRUPT_FLAG_CLEAR()       INTCON3bits.INT2IF=0
#define EXT_INT2_INTERRUPT_ENABLE()           INTCON3bits.INT2IE=1
#define EXT_INT2_INTERRUPT_DISABLE()          INTCON3bits.INT2IE=0
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXT_INT2_INTERRUPT_HIGH_PRIORITY_SET()  INTCON3bits.INT2IP=1
#define EXT_INT2_INTERRUPT_LOW_PRIORITY_SET() INTCON3bits.INT2IP=0
#endif
#define EXT_INT2_INTERRUPT_RisingEdgeSet()    INTCON2bits.INTEDG2=1
#define EXT_INT2_INTERRUPT_FallingEdgeSet()   INTCON2bits.INTEDG2=0
#endif

#if INTERRUPT_EXTERNAL_RBx_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXT_RBx_INTERRUPT_FLAG_CLEAR()      INTCONbits.RBIF=0
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXT_RBx_INTERRUPT_HIGH_PRIORITY()   INTCON2bits.RBIP=1 
#endif
#define EXT_RBx_INTERRUPT_LOW_PRIORITY()    INTCON2bits.RBIP=0
#define EXT_RBx_INTERRUPT_ENABLE()          INTCONbits.RBIE=1
#define EXT_RBx_INTERRUPT_DISABLE()         INTCONbits.RBIE=0           
#endif

typedef enum{
    EXT_INT0,
    EXT_INT1,
    EXT_INT2
}EXT_INTx_src;
typedef enum{
       Interrupt_Falling_Edge=0,     
       Interrupt_Rising_Edge,
}Interrupt_Intx_Edge;

typedef struct{
    void (*EXT_InterruptHandler) (void);
    EXT_INTx_src source;
    Interrupt_Intx_Edge edge;
    Interrupt_Priority_Levels priority;
    pin_config_info mcu_pin;
}EXT_INTx_t;

typedef struct{
    void (*EXT_InterruptHandler_High) (void);
    void (*EXT_InterruptHandler_Low) (void);
    Interrupt_Priority_Levels priority;
    pin_config_info mcu_pin;
}EXT_RBx_t;

Return_Status INTx_Init(EXT_INTx_t* int_obj);
Return_Status INTx_DeInit(EXT_INTx_t* int_obj);
Return_Status RBx_Init(EXT_RBx_t* int_obj);
Return_Status RBx_DeInit(EXT_RBx_t* int_obj);



#endif	/* EXTERNAL_INTERRUPT_H */

