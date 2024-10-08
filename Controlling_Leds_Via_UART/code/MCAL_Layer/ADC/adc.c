#include <string.h>
#include"adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void)=NULL;
#endif

static inline Return_Status adc_input_channel_port_cofigure(ADC_InputChannel_t channel);
static inline Return_Status adc_select_format(ADC_Config_t* adc);
static inline Return_Status adc_select_voltage_reference(ADC_Config_t* adc);


Return_Status ADC_Init(ADC_Config_t* adc){
    Return_Status ret=R_NOK;
    if(adc!=NULL){
        ret=R_OK;
        ADC_MODULE_DISABLE();
        ADCON2bits.ACQT=adc->Acquisition_Time;
        ADCON2bits.ADCS=adc->Conversion_Clock_Select;
        ADCON0bits.CHS=adc->Channel;   
        adc_input_channel_port_cofigure(adc->Channel); 
        adc_select_format(adc);
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_GLOBAL_ENABLE();
        INTERRUPT_PERIPHERAL_ENABLE();
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_FLAG_CLEAR();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if(adc->priority==Interrupt_High_Priority) {ADC_HighPrioritySet();}
        else if(adc->priority==Interrupt_Low_Priority) {ADC_LowPrioritySet();}
#endif
        ADC_InterruptHandler=adc->ADC_InterruptHandler;
#endif
         ADCON1bits.VCFG=adc->ADC_Voltage_Reference;
        ADC_MODULE_ENABLE();
    }
    return ret;
}
Return_Status ADC_DeInit(ADC_Config_t* adc){
    Return_Status ret=R_NOK;
    if(adc!=NULL){
        ret=R_OK;
        ADC_MODULE_DISABLE();
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}
Return_Status ADC_SelectChannel(ADC_Config_t* adc,ADC_InputChannel_t channel){
    Return_Status ret=R_NOK;
    if(adc!=NULL){
        ret=R_OK;
        ADCON0bits.CHS=channel;
        adc_input_channel_port_cofigure(adc->Channel); 
    }
    return ret;
}
Return_Status ADC_StartConversion(ADC_Config_t* adc){
    Return_Status ret=R_NOK;
    if(adc!=NULL){
        ret=R_OK;
        ADC_CONVERSION_START();
    }
    return ret;
}
Return_Status ADC_IsConverionDone(ADC_Config_t* adc,u8* ConverionStatus){
    Return_Status ret=R_NOK;
    if(adc!=NULL&&ConverionStatus!=NULL){
        ret=R_OK;
        *ConverionStatus=(u8)(!(ADCON0bits.GO_nDONE));
    }
    return ret;
}
 Return_Status ADC_GetConverionResult(ADC_Config_t* adc,adc_result* result){
    Return_Status ret=R_NOK;
    if(adc!=NULL&&result){
        ret=R_OK;
        if(adc->ADC_Result_Format==ADC_RESULT_RIGHT){
            *result=(u16)(ADRESL+(ADRESH<<8));
        }
        else if(adc->ADC_Result_Format==ADC_RESULT_LEFT) {
            *result=(u16)((ADRESL+(ADRESH<<8))>>6);
        }
        else{
            *result=(u16)(ADRESL+(ADRESH<<8));
        }
    }
    return ret;
}
Return_Status ADC_GetConverion(ADC_Config_t* adc,ADC_InputChannel_t channel,adc_result* result){
    Return_Status ret=R_NOK;
    u8 l_ADC_conversion_status;
    if(adc!=NULL&&result!=NULL){
        ret=R_OK;
        ADC_SelectChannel(adc,channel);
        ADC_StartConversion(adc);
        while(ADCON0bits.GO_nDONE);
        ADC_GetConverionResult(adc,result);

    }
    return ret;
}

Return_Status ADC_GetConverion_Interrupt(ADC_Config_t* adc,ADC_InputChannel_t channel)
{
    Return_Status ret=R_NOK;
    u8 l_ADC_conversion_status;
    if(adc!=NULL){
        ret=R_OK;
        ADC_INTERRUPT_FLAG_CLEAR();
        ADC_SelectChannel(adc,channel);
        ADC_StartConversion(adc);
    }
    return ret;
}

static inline Return_Status adc_input_channel_port_cofigure(ADC_InputChannel_t channel){
    Return_Status ret=R_OK;
        switch(channel){
            case ADC_AN0_CHANNEL: SET_BIT(TRISA,_TRISA_RA0_POSN); break;
            case ADC_AN1_CHANNEL: SET_BIT(TRISA,_TRISA_RA1_POSN); break;
            case ADC_AN2_CHANNEL: SET_BIT(TRISA,_TRISA_RA2_POSN); break;
            case ADC_AN3_CHANNEL: SET_BIT(TRISA,_TRISA_RA3_POSN); break;
            case ADC_AN4_CHANNEL: SET_BIT(TRISA,_TRISA_RA5_POSN); break;
            case ADC_AN5_CHANNEL: SET_BIT(TRISE,_TRISE_RE0_POSN); break;
            case ADC_AN6_CHANNEL: SET_BIT(TRISE,_TRISE_RE1_POSN); break;
            case ADC_AN7_CHANNEL: SET_BIT(TRISE,_TRISE_RE2_POSN); break;
            case ADC_AN8_CHANNEL: SET_BIT(TRISB,_TRISB_RB2_POSN); break;
            case ADC_AN9_CHANNEL: SET_BIT(TRISB,_TRISB_RB3_POSN); break;
            case ADC_AN10_CHANNEL: SET_BIT(TRISB,_TRISB_RB1_POSN); break;
            case ADC_AN11_CHANNEL: SET_BIT(TRISB,_TRISB_RB4_POSN); break;
            case ADC_AN12_CHANNEL: SET_BIT(TRISB,_TRISB_RB0_POSN); break;
            default: ret=R_NOK; break;
        }
    return ret;
}
static inline Return_Status adc_select_format(ADC_Config_t* adc){
    Return_Status ret=R_NOK;
    if(adc!=NULL){
        ret=R_OK;
        if(adc->ADC_Result_Format==ADC_RESULT_RIGHT) ADC_RIGHT_JUSTIFIED();
        else if(adc->ADC_Result_Format==ADC_RESULT_LEFT) ADC_LEFT_JUSTIFIED();
        else ADC_RIGHT_JUSTIFIED();
    }
    return ret;
}
static Return_Status adc_select_voltage_reference(ADC_Config_t* adc){
    Return_Status ret=R_NOK;
    if(adc!=NULL){
        ret=R_OK;
        if(adc->ADC_Voltage_Reference==ADC_EnablevoltageRefernce) ADC_Enable_Voltage_Reference_Configuration();
        else if(adc->ADC_Voltage_Reference==ADC_DisablevoltageRefernce) ADC_Disable_Voltage_Reference_Configuration();
        else ADC_Disable_Voltage_Reference_Configuration();
    }
    return ret;
}

void adc_ISR(void)
{
    ADC_INTERRUPT_FLAG_CLEAR();
     if(ADC_InterruptHandler){
         ADC_InterruptHandler();
     } 
}