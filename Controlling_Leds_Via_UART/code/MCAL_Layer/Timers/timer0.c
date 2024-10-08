#include"timer0.h"

static inline Return_Status timer0_prescaler_cfg(TIMER0_t* timer0);
static inline Return_Status timer0_mode_cfg(TIMER0_t* timer0);
static inline Return_Status timer0_Register_size_Config(TIMER0_t* timer0);

static u16 timer0_preload;
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  static void (*timer0_InterruptHandler)(void)=NULL;      
#endif

Return_Status timer0_Init(TIMER0_t* timer0){
    Return_Status ret=R_NOK;
    if(timer0!=NULL){
        ret=R_OK;
        TIMER0_DISABLE_MODULE();
        timer0_prescaler_cfg(timer0);
        timer0_mode_cfg(timer0);
        timer0_Register_size_Config(timer0);
        TMR0H=(timer0->preload_value)>>8;
        TMR0L=(u8)timer0->preload_value;
        timer0_preload=timer0->preload_value;
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_FLAG_CLEAR();
        TIMER0_INTERRUPT_ENABLE();
        timer0_InterruptHandler=timer0->Timer0_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==INTERRUPT_FEATURE_ENABLE
        if(timer0->priority==Interrupt_High_Priority){
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            TIMER0_HighPrioritySet();
        }        
        else if(Interrupt_Low_Priority==timer0->priority)
        {
            INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
            TIMER0_LowPrioritySet();
            
        }
#else
      INTERRUPT_GLOBAL_ENABLE();
      INTERRUPT_PERIPHERAL_ENABLE();
#endif
#endif

        TIMER0_ENABLE_MODULE();
    }
    return ret;
}
Return_Status timer0_DeInit(TIMER0_t* timer0){
    Return_Status ret=R_NOK;
    if(timer0){
        ret=R_OK;
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        
#endif
    }
    return ret;
}
Return_Status timer0_Write_Value(TIMER0_t* timer0,u16 value){
    Return_Status ret=R_NOK;
    if(timer0){
        ret=R_OK;
        TMR0H=(value)>>8;
        TMR0L=(u8)(value);
    }
    return ret;
}
Return_Status timer0_Read_Value(TIMER0_t* timer0,u16* value){
    Return_Status ret=R_NOK;
    if(timer0&&value){
        ret=R_OK;
        u8 timer0l=TMR0L;
        u8 timer0h=TMR0H;
        *value=(u16)((timer0h<<8)+timer0l);
    }
    return ret;
}

static inline Return_Status timer0_prescaler_cfg(TIMER0_t* timer0){
    Return_Status ret=R_NOK;
    if(timer0){
        ret=R_OK;
        if(TIMER0_PRESCALER_ENABLE_CFG==timer0->prescaler_enable){
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS=timer0->prescaler_value;
        }
        else if(TIMER0_PRESCALER_DISABLE_CFG==timer0->prescaler_enable){
            TIMER0_PRESCALER_DISABLE();
        }
    }
        return ret;
}

static inline Return_Status timer0_mode_cfg(TIMER0_t* timer0){
    Return_Status ret=R_NOK;
    if(timer0){
        ret=R_OK;
        if(TIMER0_TIMER_MODE_CFG==timer0->mode){
            TIMER0_TIMER_MODE_SELECT();
        }
        else if(TIMER0_COUNTER_MODE_CFG==timer0->mode){
            TIMER0_COUNTER_MODE_SELECT();
            if(timer0->edge==TIMER0_SelectRisingEdge_CFG){
                TIMER0_SelectRisingEdge();
            }
            else if(timer0->edge==TIMER0_SelectFallingEdge_CFG){
                TIMER0_SelectFallingEdge();
            }
        }
    }
        return ret;
}

static inline Return_Status timer0_Register_size_Config(TIMER0_t* timer0){
    Return_Status ret=R_NOK;
    if(timer0){
        ret=R_OK;
        if(timer0->register_size==TIMER0_16BIT_MODE_CFG){
            TIMER0_16BIT_MODE();
        }
        else if(timer0->register_size==TIMER0_8BIT_MODE_CFG){
            TIMER0_8BIT_MODE();
        }
    }
        return ret;
}


void Timer0_ISR(void){
    TIMER0_INTERRUPT_FLAG_CLEAR();
    TMR0H=timer0_preload>>8;
    TMR0L=(u8)timer0_preload;
    if(timer0_InterruptHandler)
    timer0_InterruptHandler();
}