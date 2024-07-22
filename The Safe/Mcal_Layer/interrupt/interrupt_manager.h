/* 
 * File:   interrupt_manager.h
 * Author: hesham
 *
 * Created on January 6, 2024, 7:53 PM
 */

#ifndef INTERRUPT_MANAGER_H
#define	INTERRUPT_MANAGER_H

#include "interrupt_gen_cfg.h"
#include"interrupt_config.h"

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(u8 RB4_Source);
void RB5_ISR(u8 RB5_Source);
void RB6_ISR(u8 RB6_Source);
void RB7_ISR(u8 RB7_Source);
void Timer0_ISR(void);

#endif	/* INTERRUPT_MANAGER_H */

