/* 
 * File:   adc.h
 * Author: hesham
 *
 * Created on February 9, 2024, 5:04 PM
 */

#ifndef ADC_H
#define	ADC_H

#include"../GPIO/GPIO.h"
#include"../interrupt/internal_interrupt.h"
#include"adc_cfg.h"


#define ADC_AN0_ANALOG_FUNCTIONALITY 0X0E
#define ADC_AN1_ANALOG_FUNCTIONALITY 0X0D
#define ADC_AN2_ANALOG_FUNCTIONALITY 0X0C 
#define ADC_AN3_ANALOG_FUNCTIONALITY 0X0B
#define ADC_AN4_ANALOG_FUNCTIONALITY 0X0A
#define ADC_AN5_ANALOG_FUNCTIONALITY 0X09
#define ADC_AN6_ANALOG_FUNCTIONALITY 0X08
#define ADC_AN7_ANALOG_FUNCTIONALITY 0X07
#define ADC_AN8_ANALOG_FUNCTIONALITY 0X06
#define ADC_AN9_ANALOG_FUNCTIONALITY 0X05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0X04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0X03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0X02
#define ADC_ALL_ANALOG_FUNCTIONALITY 0X00
#define ADC_ALL_DIGITAL_FUNCTIONALITY 0X0F

#define ADC_RESULT_RIGHT 1
#define ADC_RESULT_LEFT 0

#define ADC_CONVERSION_IN_PROGRESS 0
#define ADC_CONVERISON_DONE 1

#define ADC_EnablevoltageRefernce 1
#define ADC_DisablevoltageRefernce 0

#define ADC_MODULE_ENABLE() ADCON0bits.ADON=1
#define ADC_MODULE_DISABLE() ADCON0bits.ADON=0

#define ADC_CONVERSION_STATUS() ADCON0bits.GO_nDONE
#define ADC_CONVERSION_START() ADCON0bits.GODONE=1

#define ADC_RIGHT_JUSTIFIED() ADCON2bits.ADFM=1
#define ADC_LEFT_JUSTIFIED() ADCON2bits.ADFM=0
  
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(CHOOSE) (ADCON1bits.PCFG=CHOOSE  )

#define ADC_Enable_Voltage_Reference_Configuration() do{ \
                                                ADCON1bits.VCFG0=1; \
                                                ADCON1bits.VCFG1=1; \
                                                }while(0) \
                                                
#define ADC_Disable_Voltage_Reference_Configuration() do{ \
                                                ADCON1bits.VCFG0=0; \
                                                ADCON1bits.VCFG1=0;  \
                                                }while(0) \
                                                
typedef enum{
    ADC_AN0_CHANNEL,
    ADC_AN1_CHANNEL,
    ADC_AN2_CHANNEL,
    ADC_AN3_CHANNEL,
    ADC_AN4_CHANNEL,
    ADC_AN5_CHANNEL,
    ADC_AN6_CHANNEL,
    ADC_AN7_CHANNEL,
    ADC_AN8_CHANNEL,
    ADC_AN9_CHANNEL,
    ADC_AN10_CHANNEL,
    ADC_AN11_CHANNEL,
    ADC_AN12_CHANNEL,
}ADC_InputChannel_t;

typedef enum{
    ADC_0_TAD,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}ADC_Acquisition_Time;

typedef enum{
    ADC_CONVERSION_FOSC_DIV_BY_2,
    ADC_CONVERSION_FOSC_DIV_BY_8,
    ADC_CONVERSION_FOSC_DIV_BY_32,
    ADC_CONVERSION_FOSC_DIV_BY_FRC,
    ADC_CONVERSION_FOSC_DIV_BY_4,
    ADC_CONVERSION_FOSC_DIV_BY_16,
    ADC_CONVERSION_FOSC_DIV_BY_64,
}ADC_Conversion_Clock_Select;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE ==INTERRUPT_FEATURE_ENABLE
    void (*ADC_InterruptHandler)(void);
    Interrupt_Priority_Levels priority;
#endif
   ADC_Conversion_Clock_Select Conversion_Clock_Select;
   ADC_Acquisition_Time Acquisition_Time; 
   ADC_InputChannel_t Channel; 
   u8 ADC_Voltage_Reference:1;
   u8 ADC_Result_Format:1;
   u8 ADC_Reserved:6;
}ADC_Config_t;

typedef u16 adc_result;

Return_Status ADC_Init(ADC_Config_t* adc);
Return_Status ADC_DeInit(ADC_Config_t* adc);
Return_Status ADC_SelectChannel(ADC_Config_t* adc,ADC_InputChannel_t channel);
Return_Status ADC_StartConversion(ADC_Config_t* adc);
Return_Status ADC_IsConverionDone(ADC_Config_t* adc,u8* ConverionStatus);
Return_Status ADC_GetConverion(ADC_Config_t* adc,ADC_InputChannel_t channel,adc_result* result);

/*INTERRUPT*/
Return_Status ADC_GetConverion_Interrupt(ADC_Config_t* adc,ADC_InputChannel_t channel);
Return_Status ADC_GetConverionResult(ADC_Config_t* adc,adc_result* result);


#endif	/* ADC_H */

  