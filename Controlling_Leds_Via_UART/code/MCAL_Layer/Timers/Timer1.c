#include"Timer1.h"
#include "timer0.h"

static inline Return_Status timer1_prescaler_cfg(Timer1_t* timer1);
static inline Return_Status timer1_mode_cfg(Timer1_t* timer1);

static u16 timer1_preload;
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  static void (*timer1_InterruptHandler)(void)=NULL;      
#endif
  

Return_Status timer1_Init(Timer1_t* timer1){
    Return_Status ret=R_NOK;
    if(timer1){
        ret=R_OK;
        TIMER1_DISABLE();
        timer1_mode_cfg(timer1);
        timer1_prescaler_cfg(timer1);
        TMR1H=timer1->preload_value>>8;
        TMR1L=timer1->preload_value;
        timer1_preload=timer1->preload_value;
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_FLAG_CLEAR();
        TIMER1_INTERRUPT_ENABLE();
        timer1_InterruptHandler=timer1->Timer1_InterruptHandler;
#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==INTERRUPT_FEATURE_ENABLE
        if(timer1->priority==Interrupt_High_Priority){
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            TIMER1_HighPrioritySet();
        }        
        else if(Interrupt_Low_Priority==timer1->priority)
        {
            INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
            TIMER1_LowPrioritySet();
            
        }
#else
      INTERRUPT_GLOBAL_ENABLE();
      INTERRUPT_PERIPHERAL_ENABLE();
#endif
        TIMER1_ENABLE();
    }
    return ret;
}
Return_Status timer1_DeInit(Timer1_t* timer1){
    Return_Status ret=R_NOK;
    if(timer1){
        ret=R_OK;
        TIMER1_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}
Return_Status timer1_Write_Value(Timer1_t* timer1,u16 value){
    Return_Status ret=R_NOK;
    if(timer1){
        ret=R_OK;
        TMR1H=(value)>>8;
        TMR1L=(u8)(value);
    }
    return ret;
}
Return_Status timer1_Read_Value(Timer1_t* timer1,u16* value){
    Return_Status ret=R_NOK;
    if(timer1){
        ret=R_OK;
        u8 timer1l=TMR1L;
        u8 timer1h=TMR1H;
        *value=(u16)((timer1h<<8)+timer1l);
    }
    return ret;
}
static inline Return_Status timer1_prescaler_cfg(Timer1_t* timer1){
    Return_Status ret=R_NOK;
    if(timer1){
        ret=R_OK;
        TIMER1_PRESCALER_SELECT(timer1->prescaler_value);
    }
    return ret;
}
static inline Return_Status timer1_mode_cfg(Timer1_t* timer1){
    Return_Status ret=R_NOK;
    if(timer1){
        ret=R_OK;
        if(timer1->mode==TIMER1_COUNTER_MODE_CFG){
             TIMER1_COUNTER_MODE();
             if(timer1->counter_mode==TIMER1_SYNC_COUNTER_MODE_CFG) TIMER1_SYNC_COUNTER_MODE();
             else if(timer1->counter_mode==TIMER1_ASYNC_COUNTER_MODE_CFG) TIMER1_ASYNC_COUNTER_MODE();
        }
        else if(timer1->mode==TIMER1_TIMER_MODE_CFG) TIMER1_TIMER_MODE();
    }
    return ret;
}


void Timer1_ISR(void){
    TIMER1_INTERRUPT_FLAG_CLEAR();
    TMR1H=timer1_preload>>8;
    TMR1L=(u8)timer1_preload;
    if(timer1_InterruptHandler)
    timer1_InterruptHandler();
}