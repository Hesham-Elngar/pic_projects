/* 
 * File:   external_interrupt.c
 * Author: hesham
 *
 * Created on January 6, 2024, 5:02 PM
 */

#include"external_interrupt.h"
void (*INT0_InterruptHandler) (void)=NULL;
void (*INT1_InterruptHandler) (void)=NULL;
void (*INT2_InterruptHandler) (void)=NULL;

void (*RB4_InterruptHandler_High) (void)=NULL;
void (*RB4_InterruptHandler_Low) (void)=NULL;
void (*RB5_InterruptHandler_High) (void)=NULL;
void (*RB5_InterruptHandler_Low) (void)=NULL;
void (*RB6_InterruptHandler_High) (void)=NULL;
void (*RB6_InterruptHandler_Low) (void)=NULL;
void (*RB7_InterruptHandler_High) (void)=NULL;
void (*RB7_InterruptHandler_Low) (void)=NULL;


static Return_Status INTx_Enable (EXT_INTx_t* int_obj);
static Return_Status INTx_Disable(EXT_INTx_t* int_obj);
static Return_Status INTx_Priority(EXT_INTx_t* int_obj);
static Return_Status INTx_Edge(EXT_INTx_t* int_obj);
static Return_Status INTx_pin_Init(EXT_INTx_t* int_obj);
static Return_Status INTx_Clear_Flag(EXT_INTx_t* int_obj);
static Return_Status INTx_SetInterruptHandler(EXT_INTx_t* int_obj);
static Return_Status INT0_SetInterruptHandler(void (*InterruptHandler) (void));
static Return_Status INT1_SetInterruptHandler(void (*InterruptHandler) (void));
static Return_Status INT2_SetInterruptHandler(void (*InterruptHandler) (void) );



static Return_Status RBx_Enable (EXT_RBx_t* int_obj);
static Return_Status RBx_Disable(EXT_RBx_t* int_obj);
static Return_Status RBx_Priority(EXT_RBx_t* int_obj);
static Return_Status RBx_Clear_Flag(EXT_RBx_t* int_obj);
static Return_Status RBx_pin_Init(EXT_RBx_t* int_obj);
static Return_Status RBx_SetInterruptHandler(EXT_RBx_t* int_obj);


Return_Status INTx_Init(EXT_INTx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        INTx_Disable(int_obj);
        INTx_Clear_Flag(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTx_Priority(int_obj);
#endif
        INTx_Edge(int_obj);
        INTx_pin_Init(int_obj);
        INTx_SetInterruptHandler(int_obj);
        INTx_Enable(int_obj);
    }
    return ret;
}
Return_Status INTx_DeInit(EXT_INTx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        INTx_Disable(int_obj);
    }
    return ret;
}
Return_Status RBx_Init(EXT_RBx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        RBx_Disable(int_obj);
        RBx_Clear_Flag(int_obj);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        RBx_Priority(int_obj);
#endif
        RBx_pin_Init(int_obj);
        RBx_SetInterruptHandler(int_obj);
        RBx_Enable(int_obj);
    }
    return ret;
}
Return_Status RBx_DeInit(EXT_RBx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
    }
    return ret;
}

static Return_Status INTx_Enable (EXT_INTx_t* int_obj)
{
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        switch(int_obj->source){
       
            case EXT_INT0:
#if INTERRUPT_FEATURE_ENABLE==INTERRUPT_PRIORITY_LEVELS_ENABLE
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif
                EXT_INT0_INTERRUPT_ENABLE();
                break;
            case EXT_INT1:
#if INTERRUPT_FEATURE_ENABLE==INTERRUPT_PRIORITY_LEVELS_ENABLE
            if(int_obj->priority==Interrupt_High_Priority)INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            else if(int_obj->priority==Interrupt_Low_Priority)INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif 
                EXT_INT1_INTERRUPT_ENABLE();
                break;
            case EXT_INT2:
#if INTERRUPT_FEATURE_ENABLE==INTERRUPT_PRIORITY_LEVELS_ENABLE
            if(int_obj->priority==Interrupt_High_Priority)INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            else if(int_obj->priority==Interrupt_Low_Priority)INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif 
                EXT_INT2_INTERRUPT_ENABLE();
                break;
        }
    }
    return ret;
}
static Return_Status INTx_Disable(EXT_INTx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        switch(int_obj->source){
            case EXT_INT0:
                EXT_INT0_INTERRUPT_DISABLE();
                break;
            case EXT_INT1:
                EXT_INT1_INTERRUPT_DISABLE();
                break;
            case EXT_INT2:
                EXT_INT2_INTERRUPT_DISABLE();
                break;
        }
    }
    return ret;
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Return_Status INTx_Priority(EXT_INTx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        switch(int_obj->source){
            case EXT_INT1:
            if(int_obj->priority==Interrupt_High_Priority)     EXT_INT1_INTERRUPT_HIGH_PRIORITY_SET();
            else if(int_obj->priority==Interrupt_Low_Priority) EXT_INT1_INTERRUPT_LOW_PRIORITY_SET();
                break;
            case EXT_INT2:
            if(int_obj->priority==Interrupt_High_Priority)     EXT_INT2_INTERRUPT_HIGH_PRIORITY_SET();
            else if(int_obj->priority==Interrupt_Low_Priority) EXT_INT2_INTERRUPT_HIGH_PRIORITY_SET();
                break;
        }
    }
    return ret;
}
#endif
static Return_Status INTx_Edge(EXT_INTx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
         switch(int_obj->source){
       
            case EXT_INT0:
                if(int_obj->edge==Interrupt_Falling_Edge) EXT_INT0_INTERRUPT_FallingEdgeSet();
                else if(int_obj->edge==Interrupt_Rising_Edge) EXT_INT0_INTERRUPT_RisingEdgeSet();
                break;
            case EXT_INT1:
                if(int_obj->edge==Interrupt_Falling_Edge) EXT_INT1_INTERRUPT_FallingEdgeSet();
                else if(int_obj->edge==Interrupt_Rising_Edge) EXT_INT1_INTERRUPT_RisingEdgeSet();
                break;
            case EXT_INT2:
                if(int_obj->edge==Interrupt_Falling_Edge) EXT_INT2_INTERRUPT_FallingEdgeSet();
                else if(int_obj->edge==Interrupt_Rising_Edge) EXT_INT2_INTERRUPT_RisingEdgeSet();
                break;
        }
    }
    return ret;
}
static Return_Status INTx_pin_Init(EXT_INTx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        gpio_pin_initialize(&int_obj->mcu_pin);
    }
    return ret;
}
static Return_Status INTx_SetInterruptHandler(EXT_INTx_t* int_obj)
{
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        switch(int_obj->source){
            case EXT_INT0:
                INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case EXT_INT1:
                INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case EXT_INT2:
                INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
        }
    }
    return ret;
}

static Return_Status INT0_SetInterruptHandler(void (*InterruptHandler) (void)){
    Return_Status ret=R_NOK;
    if(InterruptHandler!=NULL){
        ret=R_OK;
        INT0_InterruptHandler=InterruptHandler;
    }
    return ret;
}
static Return_Status INT1_SetInterruptHandler(void (*InterruptHandler) (void)){
    Return_Status ret=R_NOK;
    if(InterruptHandler!=NULL){
        ret=R_OK;
        INT1_InterruptHandler=InterruptHandler;
    }
    return ret;
}
static Return_Status INT2_SetInterruptHandler(void (*InterruptHandler) (void) ){
    Return_Status ret=R_NOK;
    if(InterruptHandler!=NULL){
        ret=R_OK;
        INT2_InterruptHandler=InterruptHandler;
    }
    return ret;
}

static Return_Status INTx_Clear_Flag(EXT_INTx_t* int_obj)
{
    Return_Status ret=R_NOK;
    if(int_obj!=NULL){
        ret=R_OK;
        switch(int_obj->source){
            case EXT_INT0:
                EXT_INT0_INTERRUPT_FLAG_CLEAR();
                break;
            case EXT_INT1:
                EXT_INT1_INTERRUPT_FLAG_CLEAR();
                break;
            case EXT_INT2:
                EXT_INT2_INTERRUPT_FLAG_CLEAR();
                break;
        }
    }
    return ret;
}

void INT0_ISR(void)
{
    EXT_INT0_INTERRUPT_FLAG_CLEAR();
    if(INT0_InterruptHandler) INT0_InterruptHandler();
}
void INT1_ISR(void)
{
    EXT_INT1_INTERRUPT_FLAG_CLEAR();
    if(INT1_InterruptHandler) INT1_InterruptHandler();
}
void INT2_ISR(void)
{
    EXT_INT2_INTERRUPT_FLAG_CLEAR();
    if(INT2_InterruptHandler) INT2_InterruptHandler();
}
/**************************************************************************************************/
static Return_Status RBx_Enable (EXT_RBx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj){
        ret=R_OK;
        EXT_RBx_INTERRUPT_ENABLE();
    }
    return ret;
}
static Return_Status RBx_Disable(EXT_RBx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj){
        ret=R_OK;
     EXT_RBx_INTERRUPT_DISABLE();   
    }
    return ret;
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Return_Status RBx_Priority(EXT_RBx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj){
        ret=R_OK;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if(int_obj->priority==Interrupt_High_Priority)
        {
           INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
           EXT_RBx_INTERRUPT_HIGH_PRIORITY();
        }
        
        else if(int_obj->priority==Interrupt_Low_Priority)
        {
           INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
           EXT_RBx_INTERRUPT_LOW_PRIORITY();   
        }
#else
        INTERRUPT_GLOBAL_ENABLE();
        INTERRUPT_PERIPHERAL_ENABLE();
#endif
    }
    return ret;
}
#endif
static Return_Status RBx_Clear_Flag(EXT_RBx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj){
        ret=R_OK;
        EXT_RBx_INTERRUPT_FLAG_CLEAR();
    }
    return ret;
}
static Return_Status RBx_pin_Init(EXT_RBx_t* int_obj)
{
    Return_Status ret=R_NOK;
    if(int_obj){
        ret=R_OK;
        gpio_pin_initialize(&int_obj->mcu_pin);
    }
    return ret;
}
static Return_Status RBx_SetInterruptHandler(EXT_RBx_t* int_obj){
    Return_Status ret=R_NOK;
    if(int_obj){
        ret=R_OK;
        switch(int_obj->mcu_pin.pin){
            case PIN4_INDEX:
                RB4_InterruptHandler_High=int_obj->EXT_InterruptHandler_High;
                RB4_InterruptHandler_Low=int_obj->EXT_InterruptHandler_Low;
                break;
            case PIN5_INDEX:
                RB5_InterruptHandler_High=int_obj->EXT_InterruptHandler_High;
                RB5_InterruptHandler_Low=int_obj->EXT_InterruptHandler_Low;        
                break;
            case PIN6_INDEX:
                RB6_InterruptHandler_High=int_obj->EXT_InterruptHandler_High;
                RB6_InterruptHandler_Low=int_obj->EXT_InterruptHandler_Low;     
                break;
            case PIN7_INDEX:
                RB7_InterruptHandler_High=int_obj->EXT_InterruptHandler_High;
                RB7_InterruptHandler_Low=int_obj->EXT_InterruptHandler_Low;    
                break;
        }
    }
    return ret;
}

void RB4_ISR(u8 RB4_Source)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(RB4_Source==1&&RB4_InterruptHandler_High)     RB4_InterruptHandler_High();
    else if(RB4_Source==0&&RB4_InterruptHandler_Low) RB4_InterruptHandler_Low();
}
void RB5_ISR(u8 RB5_Source)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(RB5_Source==1&&RB5_InterruptHandler_High)     RB5_InterruptHandler_High();
    else if(RB5_Source==0&&RB5_InterruptHandler_Low) RB5_InterruptHandler_Low();
}
void RB6_ISR(u8 RB6_Source)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(RB6_Source==1&&RB6_InterruptHandler_High)     RB6_InterruptHandler_High();
    else if(RB6_Source==0&&RB6_InterruptHandler_Low) RB6_InterruptHandler_Low();
}
void RB7_ISR(u8 RB7_Source)
{
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
    if(RB7_Source==1&&RB7_InterruptHandler_High)     RB7_InterruptHandler_High();
    else if(RB7_Source==0&&RB7_InterruptHandler_Low) RB7_InterruptHandler_Low();
}