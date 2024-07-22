/* 
 * File:   calc.h
 * Author: hesham
 *
 * Created on March 18, 2024, 11:48 PM
 */

#ifndef CALC_H
#define	CALC_H

#include"application.h"

#define  MAX_SIZE 50
#define  CALC_MAX_SIZE 6
#define NOT_PRESSED '\0'
#define PRESSED 1
#define FLOATING_POINT '.'
#define UNARY_MINUS  1
#define BINARY_MINUS 0

#define BIN_BASE 2
#define OCT_BASE 8
#define DEC_BASE 10
#define HEX_BASE 16


typedef struct{
	f8 data[CALC_MAX_SIZE];
	u8	top;
}Calculator_t;

Return_Status calc_init(Calculator_t* calc);
void calculator_mode(Calculator_t* calc);
void infixToPostfix(Calculator_t* calc);


 
#endif	/* CALC_H */

