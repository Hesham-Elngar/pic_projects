#include"Timer2.h"

static void (*Timer2_Interrupt_Handler)(void);
static u8 Timer2_preload;

Return_Status Timer2_Init(Timer2_t* timer2){
    Return_Status ret=R_NOK;
    if(timer2){
        ret=R_OK;        
        TIMER2_DISABLE();
        TIMER2_PRESCALER_SELECT(timer2->prescaler_value); 
        TIMER2_POSTCALER_SELECT(timer2->postscaler_value);
        TMR2=timer2->preload_value;
        Timer2_preload=timer2->preload_value;
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_FLAG_CLEAR();
        TIMER2_INTERRUPT_ENABLE();
        timer2->Timer2_Interrupt_Handler=Timer2_Interrupt_Handler;
#endif
#if INTERRUPT_PRIORITY_LEVELS_ENABLE ==INTERRUPT_FEATURE_ENABLE
        if(timer2->priority==Interrupt_High_Priority){
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            TIMER2_HighPrioritySet();
        }        
        else if(Interrupt_Low_Priority==timer2->priority)
        {
            INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
            TIMER2_LowPrioritySet();
            
        }
#else
      INTERRUPT_GLOBAL_ENABLE();
      INTERRUPT_PERIPHERAL_ENABLE();
#endif  
        TIMER2_ENABLE();
    }
    return ret;
}
Return_Status Timer2_DeInit(Timer2_t* timer2){
    Return_Status ret=R_NOK;
    if(timer2){
        ret=R_OK;
        TIMER2_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}
Return_Status Timer2_Read_Value(Timer2_t* timer2,u8 *value){
    Return_Status ret=R_NOK;
    if(timer2){
        ret=R_OK;
        *value=TMR2;
    }
    return ret;
}
Return_Status Timer2_Write_Value(Timer2_t* timer2,u8 value){
    Return_Status ret=R_NOK;
    if(timer2){
        ret=R_OK;
        TMR2=value;
    }
    return ret;
}

void Timer2_ISR(void){
    TIMER2_INTERRUPT_FLAG_CLEAR();
    TMR2=Timer2_preload;
    if(Timer2_Interrupt_Handler)
    Timer2_Interrupt_Handler();
}

