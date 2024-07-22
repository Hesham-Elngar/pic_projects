/*
 * STD_types.h
 *
 * Created: 10/9/2023 10:20:51 PM
 *  Author: hesham
 */ 

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s8;
typedef signed int s16;
typedef signed int s32;
typedef float f4;
typedef double f8;
typedef u8 STD_ReturnType;

/**BIT MATH*/
#define SET_BIT(REG,BIT)    REG|=(1<<BIT)
#define CLR_BIT(REG,BIT)    REG&=~(1<<BIT)
#define TOG_BIT(REG,BIT)    REG^=(1<<BIT)
#define GET_BIT(REG,BIT)    (REG&(1<<BIT))>>BIT
#define READ_BIT(REG,BIT)   ((REG>>BIT)&1)
#define IS_BIT_SET(REG,BIT) REG&(1<<BIT)>>BIT
#define IS_CLR_BIT(REG,BIT) !(REG&(1<<BIT)>>BIT)


#endif /* STD_TYPES_H_ */