/* 
 * File:   gpio_private.h
 * Author: hesham
 *
 * Created on October 15, 2023, 6:55 PM
 */

#ifndef GPIO_PRIVATE_H
#define	GPIO_PRIVATE_H

#define HTRISA (*(volatile u8*)0XF92)
#define HTRISB (*(volatile u8*)0XF93)
#define HTRISC (*(volatile u8*)0XF94)
#define HTRISD (*(volatile u8*)0XF95)
#define HTRISE (*(volatile u8*)0XF96)

#define HPORTA (*(volatile u8*)0XF80)
#define HPORTB (*(volatile u8*)0XF80)
#define HPORTC (*(volatile u8*)0XF80)
#define HPORTD (*(volatile u8*)0XF80)
#define HPORTE (*(volatile u8*)0XF80)

#define HLATA (*(volatile u8*)0XF89)
#define HLATB (*(volatile u8*)0XF8A)
#define HLATC (*(volatile u8*)0XF8B)
#define HLATD (*(volatile u8*)0XF8C)
#define HLATE (*(volatile u8*)0XF8D)

#endif	/* GPIO_PRIVATE_H */

