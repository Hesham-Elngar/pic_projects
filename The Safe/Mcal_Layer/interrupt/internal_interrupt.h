/* 
 * File:   internal_interrupt.h
 * Author: hesham
 *
 * Created on January 6, 2024, 5:00 PM
 */

#ifndef INTERNAL_INTERRUPT_H
#define	INTERNAL_INTERRUPT_H

#include"interrupt_config.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_ENABLE() INTCONbits.TMR0IE=1
#define TIMER0_INTERRUPT_DISABLE() INTCONbits.TMR0IE=0
#define TIMER0_INTERRUPT_FLAG_CLEAR() INTCONbits.TMR0IF=0
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER0_HighPrioritySet() INTCON2bits.TMR0IP=1
#define TIMER0_LowPrioritySet() INTCON2bits.TMR0IP=0
#endif
#endif


#endif	/* INTERNAL_INTERRUPT_H */

