/* 
 * File:   interrupt_manager.h
 * Author: hesham
 *
 * Created on January 6, 2024, 7:53 PM
 */
#include"MCAL_Layer/interrupt/interrupt_manager.h"
u8 volatile RB4_Flag=1,RB5_Flag=1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() manageHigh(void)
{
    if((INTERRUPT_OCCUR==INTCONbits.INT0IF)&&(INTERRUPT_ENABLE==INTCONbits.INT0IE))
    {
        INT0_ISR();
    }
    if((INTERRUPT_OCCUR==INTCON3bits.INT2IF)&&(INTERRUPT_ENABLE==INTCON3bits.INT2IE))
    {
        INT2_ISR();
    }
    if((INTERRUPT_OCCUR==INTCONbits.RBIE)&&(INTERRUPT_ENABLE==INTCONbits.RBIF&&(PORTBbits.RB4==gpio_logic_high))&&(RB4_Flag==1)){
        RB4_Flag=0;
        RB4_ISR(1);
    }
     if((INTERRUPT_OCCUR==INTCONbits.RBIE)&&(INTERRUPT_ENABLE==INTCONbits.RBIF&&(PORTBbits.RB4==gpio_logic_low))&&(RB4_Flag==0)){
         RB4_Flag=1;
         RB4_ISR(0);
    }
    if((INTERRUPT_OCCUR==INTCONbits.RBIE)&&(INTERRUPT_ENABLE==INTCONbits.RBIF&&(PORTBbits.RB5==gpio_logic_high))&&(RB5_Flag==1)){
        RB5_Flag=0;
        RB5_ISR(1);
    }
     if((INTERRUPT_OCCUR==INTCONbits.RBIE)&&(INTERRUPT_ENABLE==INTCONbits.RBIF&&(PORTBbits.RB5==gpio_logic_low))&&(RB5_Flag==0)){
         RB5_Flag=1;
         RB5_ISR(0);
    }
}
void __interrupt(low_priority) manageLow(void)
{
     if((INTERRUPT_OCCUR==INTCON3bits.INT1IF)&&(INTERRUPT_ENABLE==INTCON3bits.INT1IE))
    {
        INT1_ISR();
    }
}
#else
void __interrupt() manage(void)
{
    if((INTERRUPT_OCCUR==INTCONbits.INT0IF)&&(INTERRUPT_ENABLE==INTCONbits.INT0IE))
    {
        INT0_ISR();
    }
    if((INTERRUPT_OCCUR==INTCON3bits.INT1IF)&&(INTERRUPT_ENABLE==INTCON3bits.INT1IE))
    {
        INT1_ISR();
    }
    if((INTERRUPT_OCCUR==INTCON3bits.INT2IF)&&(INTERRUPT_ENABLE==INTCON3bits.INT2IE))
    {
        INT2_ISR();
    }
    /*if((INTERRUPT_OCCUR==INTCONbits.RBIE)&&(INTERRUPT_ENABLE==INTCONbits.RBIF&&(PORTBbits.RB4==gpio_logic_high))){
        RB4_ISR();
    }
     if((INTERRUPT_OCCUR==INTCONbits.RBIE)&&(INTERRUPT_ENABLE==INTCONbits.RBIF&&(PORTBbits.RB4==gpio_logic_low))){
        RB4_ISR();
    }*/
    if((INTERRUPT_OCCUR==INTCONbits.TMR0IF)&&(INTERRUPT_ENABLE==INTCONbits.TMR0IE))
    {
        Timer0_ISR();
    }
    if((INTERRUPT_OCCUR==PIR1bits.TMR1IF)&&(INTERRUPT_ENABLE==PIE1bits.TMR1IE))
    {
        Timer1_ISR();
    }
    if((INTERRUPT_OCCUR==PIR1bits.TMR2IF)&&(INTERRUPT_ENABLE==PIE1bits.TMR2IE))
    {
        Timer2_ISR();
    }
    if((INTERRUPT_OCCUR==PIR2bits.TMR3IF)&&(INTERRUPT_ENABLE==PIE2bits.TMR3IE))
    {
        timer3_ISR();
    }
    if((INTERRUPT_OCCUR==PIR1bits.ADIF)&&(INTERRUPT_ENABLE==PIE1bits.ADIE))
    {
        adc_ISR();
    }
    
}
#endif