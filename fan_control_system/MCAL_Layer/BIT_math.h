
/*
 * BIT_math.h
 *
 * Created: 10/7/2023 8:54:18 PM
 *  Author: hesham
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(REG,BIT)    REG|=(1<<BIT)
#define CLR_BIT(REG,BIT)    REG&=~(1<<BIT)
#define TOG_BIT(REG,BIT)    REG^=(1<<BIT)
#define GET_BIT(REG,BIT)    (REG&(1<<BIT))>>BIT
#define READ_BIT(REG,BIT)   ((REG>>BIT)&1)
#define IS_BIT_SET(REG,BIT) REG&(1<<BIT)>>BIT
#define IS_CLR_BIT(REG,BIT) !(REG&(1<<BIT)>>BIT)



#endif /* BIT_MATH_H_ */