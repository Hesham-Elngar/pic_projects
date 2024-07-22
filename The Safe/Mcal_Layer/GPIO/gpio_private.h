/* 
 * File:   gpio_private.h
 * Author: hesham
 *
 * Created on October 15, 2023, 6:55 PM
 */

#ifndef GPIO_PRIVATE_H
#define	GPIO_PRIVATE_H

#define TRISA (*(volatile u8*)0XF92)
#define TRISB (*(volatile u8*)0XF93)
#define TRISC (*(volatile u8*)0XF94)
#define TRISD (*(volatile u8*)0XF95)
#define TRISE (*(volatile u8*)0XF96)

#define PORTA (*(volatile u8*)0XF80)
#define PORTB (*(volatile u8*)0XF80)
#define PORTC (*(volatile u8*)0XF80)
#define PORTD (*(volatile u8*)0XF80)
#define PORTE (*(volatile u8*)0XF80)

#define LATA (*(volatile u8*)0XF89)
#define LATB (*(volatile u8*)0XF8A)
#define LATC (*(volatile u8*)0XF8B)
#define LATD (*(volatile u8*)0XF8C)
#define LATE (*(volatile u8*)0XF8D)

#endif	/* GPIO_PRIVATE_H */

