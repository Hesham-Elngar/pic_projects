#include"Timer3.h"
#include "timer0.h"

static u16 preload_value;

static inline Return_Status timer3_mode_cfg(Timer3_t* timer3);
static inline Return_Status timer3_counter_mode_cfg(Timer3_t* timer3);


#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
   static void (*Timer3_InterruptHandler)(void)=NULL;
#endif
Return_Status timer3_Init(Timer3_t* timer3){
    Return_Status ret=R_NOK;
    if(timer3){
        ret=R_OK;
        TIMER3_DISABLE();
        TIMER3_PRESCALER_SELECT(timer3->prescaler_value);
        timer3_mode_cfg(timer3);
        timer3_counter_mode_cfg(timer3);
        TMR3H=timer3->preload_value>>8;
        TMR3L=(u8)timer3->preload_value;
        preload_value=timer3->preload_value;
        
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_FLAG_CLEAR();
        TIMER3_INTERRUPT_ENABLE();
        Timer3_InterruptHandler=timer3->Timer3_InterruptHandler;
#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==INTERRUPT_FEATURE_ENABLE
        if(timer3->priority==Interrupt_High_Priority){
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            TIMER3_HighPrioritySet();
        }        
        else if(Interrupt_Low_Priority==timer3->priority)
        {
            INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
            TIMER3_LowPrioritySet();
            
        }
#else
      INTERRUPT_GLOBAL_ENABLE();
      INTERRUPT_PERIPHERAL_ENABLE();
#endif
        TIMER3_ENABLE();
    }
        return ret;   
}
Return_Status timer3_DeInit(Timer3_t* timer3){
    Return_Status ret=R_NOK;
    if(timer3){
        ret=R_OK;
        TIMER3_INTERRUPT_DISABLE();
        TIMER3_DISABLE();
    }
        return ret;   
}
Return_Status timer3_Write_Value(Timer3_t* timer3,u16 value){
    Return_Status ret=R_NOK;
    if(timer3){
        ret=R_OK;
        TMR3H=value>>8;
        TMR3L=(u8)value;
    }
        return ret;   
}
Return_Status timer3_Read_Value(Timer3_t* timer3,u16* value)
{
    Return_Status ret=R_NOK;
    if(timer3){
        ret=R_OK;
        u8 l_tmrl=TMR3L;
        u8 l_tmrh=TMR3H;
        *value=(u16)(l_tmrl+l_tmrh<<8);
        
    }
        return ret;   
}
static inline Return_Status timer3_mode_cfg(Timer3_t* timer3)
{
    if(timer3->mode==TIMER3_COUNTER_MODE_CFG) TIMER3_COUNTER_MODE();
    else if(timer3->mode==TIMER3_TIMER_MODE_CFG) TIMER3_TIMER_MODE();
}

static inline Return_Status timer3_counter_mode_cfg(Timer3_t* timer3)
{
    if(timer3->counter_mode==TIMER3_SYNC_COUNTER_MODE_CFG) TIMER3_SYNC_COUNTER_MODE();
    else if(timer3->counter_mode==TIMER3_ASYNC_COUNTER_MODE_CFG) TIMER3_ASYNC_COUNTER_MODE();
}

void timer3_ISR(void)
{
    TIMER3_INTERRUPT_FLAG_CLEAR();
    TMR3H=preload_value>>8;
    TMR3L=(u8)preload_value;
     if(Timer3_InterruptHandler){
         Timer3_InterruptHandler();
     } 
}