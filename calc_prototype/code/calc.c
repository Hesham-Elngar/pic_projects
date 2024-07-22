#include <ctype.h>
#include <math.h>
#include <string.h>
#include "calc.h"

static char infix_exp[MAX_SIZE];
static u8 exp_counter = 0;

static u8 current_system= NOT_PRESSED;
static u8 convert_to= NOT_PRESSED;
static u8 converter_enable= NOT_PRESSED;
static u8 isFloat = 0;
static f8 ans_val = 0;

static Return_Status calc_push(Calculator_t* calc, f8 value);
static void calc_pop(Calculator_t* calc) ;
static inline f8 calc_top(Calculator_t* calc);
static inline void reset_calc(Calculator_t* calc);
static u8 inline calc_is_full(Calculator_t* calc);
static inline u8 calc_is_empty(Calculator_t* calc);
static void scan_exp(u8 end_symbol);
static void evaluate_post_exp(Calculator_t *calc ,char* post_exp);
static f8 perform_operation(f8 op1,f8 op2,char operator1);
static inline u8 precedence(char x);
static inline u8 isOperand(char x);
static  u8 check_balamced_brackets(u8* exp1);
static u8 check_minus_for_infix_expression(u8* infix,u8 index);
static u8 check_minus_for_postfix_expression(u8* post,u8 index);
static u8 check_forScientficCalc_customs(u8 keypad_value);
static u8 check_forAdvancedCalc_customs(u8 keypad_value);
static void replace_constants(char *infix_expression,u8* str,u8 symbol);
static f8 evaluate_constants(u8 symbol);

static u8 is_in_converter_mode(u8 value);
static void converter_mode(u8 adv_keypad_value);
static u8* binaryToHex(u8* binary);
static u8* BinaryToDecimal(u8* bin);
static u8* BinaryToOctal(u8* bin);
static u8* decimalToBinary(u8* dec);
static u8* decimalToOctal(u8* dec);
static u8* decimalToHex(u8* dec);
static u8* hexToBinary(u8* hex);
static u8* HexToDecimal(u8* hex);
static u8* hexDigitToBinary(u8 hexDigit);
static u8* OctalToDecimal(u8* oct);
static inline u8 is_binary(u8* bin);
static inline u8 is_oct(u8* oct);

void calculator_mode(Calculator_t* calc)
{
    volatile u8 keypad_value = NOT_PRESSED;
    static u8 first_time = 0;
    calc->top = 0;
    converter_enable=NOT_PRESSED;
    current_system=NOT_PRESSED;
    convert_to=NOT_PRESSED;    
    reset_calc(calc);
    while (keypad_value != '#')
    {
        keypad_get_value(&scientfic_keypad, &keypad_value);
    }
    if (first_time == 0)
    {
        lcd_4bit_send_string_pos(&lcd1, 1, 3, "Welcome Hesham");
        for (int i = 0; i < 3; i++)
        {
            lcd_4bit_send_char_data(&lcd1, '.');
            __delay_ms(500);
        }
        first_time = 1;
    }
    lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON);
    lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
}

void infixToPostfix(Calculator_t* calc)
{
         scan_exp('=');  
        if(converter_enable==PRESSED)
        {
            return; 
        }
    if (!check_balamced_brackets(infix_exp))
    {
        lcd_4bit_send_string_pos(&lcd1, 4, 9, "SYNTAX ERROR!!");
        return;
    }

    u8 len = strlen(infix_exp);
   // lcd_4bit_send_string_pos(&lcd1, 2, 1, infix_exp);
    u8* output = (u8*)malloc(len * 2 + 1); // Allocate memory for output
    if (output == NULL)
    {
        // Handle memory allocation failure
        lcd_4bit_send_string_pos(&lcd1, 4, 9, "MEMORY ERROR!!");
        return;
    }
    u8 output_counter = 0;

    for (u8 i = 0; i < len; ++i)
    {
        if (infix_exp[i] == FLOATING_POINT)
            isFloat = 1;
        if (isdigit(infix_exp[i]) || infix_exp[i] == '.'||check_minus_for_infix_expression(infix_exp,i)==UNARY_MINUS)
        {
            output[output_counter++] = infix_exp[i];
        }
        else if (infix_exp[i] == '(')
        {
            calc_push(calc, infix_exp[i]);
        }
        else if (infix_exp[i] == ' ')
        {
            continue;
        }
        else if (infix_exp[i] == ')')
        {
            while (!calc_is_empty(calc) && calc_top(calc) != '(')
            {
                output[output_counter++] = calc_top(calc);
                calc_pop(calc);
            }
            if (!calc_is_empty(calc))
                calc_pop(calc); // Pop '('
        }
        else if (isOperand(infix_exp[i]))
        {
                while (!calc_is_empty(calc) && precedence(infix_exp[i]) <= precedence(calc_top(calc)))
                {
                output[output_counter++] = ' ';
                output[output_counter++] = calc_top(calc);
                calc_pop(calc);
                }
                output[output_counter++] = ' ';
                calc_push(calc, infix_exp[i]);
        }
    }

    while (!calc_is_empty(calc))
    {
        output[output_counter++] = ' ';
        output[output_counter++] = calc_top(calc);
        calc_pop(calc);
    }

    output[output_counter] = '\0'; // Null-terminate the output string
 //   lcd_4bit_send_string_pos(&lcd1, 3, 1, output);
    evaluate_post_exp(calc, output);
    free(output);
}

static void evaluate_post_exp(Calculator_t *calc, char* post_exp)
{
    u8 length = strlen(post_exp);
    for (u8 i = 0; i < length; ++i)
    {
        if (isdigit(post_exp[i]) || post_exp[i] == '.'||check_minus_for_postfix_expression(post_exp,i)==UNARY_MINUS)
        {
            f8 num = 0.0;
            f4 decimal_factor = 0.1;
            u8 decimal_point = 0;
            s8 sign=1;
            if(check_minus_for_postfix_expression(post_exp,i)==UNARY_MINUS)
            {
                sign=-1;
                ++i;
            }
            while (isdigit(post_exp[i]) || post_exp[i] ==FLOATING_POINT)
            {
                if (post_exp[i] ==FLOATING_POINT)
                {
                    decimal_point = 1; // Mark that a decimal point has been encountered
                }
                else
                {
                    if (decimal_point)
                    {
                        // Decimal part
                        num += (post_exp[i] - '0') * decimal_factor;
                        decimal_factor *= 0.1; // Adjust decimal factor
                    }
                    else
                    {
                        // Integer part
                        num = num * 10.0 + (post_exp[i] - '0');
                    }
                }
                i++;
            }
            num*=sign;
            i--; // Decrement i to account for the loop incrementing past the last digit
            calc_push(calc, num); // Assuming calc is a pointer or reference
        }
        else if (post_exp[i] == ' ') continue;
        else if (isOperand(post_exp[i]))
        {
            if (calc_is_empty(calc))
            {
                lcd_4bit_send_string_pos(&lcd1, 4, 9, "SYNTAX ERROR!!");
                return;
            }

            f8 operand2 = calc_top(calc);
            calc_pop(calc);

            if (calc_is_empty(calc))
            {
                lcd_4bit_send_string_pos(&lcd1, 4, 9, "SYNTAX ERROR!!");
                return;
            }

            f8 operand1 = calc_top(calc);
            calc_pop(calc);

            f8 result = perform_operation(operand1, operand2, post_exp[i]);
            calc_push(calc, result);
        }
    }
    
    u8* lcd_result=(u8*)malloc(11);
    if (calc_top(calc) == (s32)calc_top(calc))
            sprintf(lcd_result, "%d", (s32)calc_top(calc)); // Display result with 6 decimal places
    else
        sprintf(lcd_result, "%.5f", calc_top(calc)); // Display result with 6 decimal places
    // Display the result on the LCD

    reset_calc(calc);
    ans_val = atof(lcd_result);
    lcd_4bit_send_string_pos(&lcd1, 4, 20 - strlen(lcd_result), lcd_result);
    free(lcd_result);
}

static inline void reset_calc(Calculator_t* calc)
{
    while (!calc_is_empty(calc)) calc_pop(calc);
    memset(infix_exp, '\0', strlen(infix_exp));
    exp_counter=0;
}

f8 perform_operation(f8 op1, f8 op2, char operator1)
{
    if ('+' == operator1)      return op1 + op2;
    else if ('-' == operator1) return op1 - op2;
    else if ('/' == operator1)
    {
        if (op2 == 0)
        {
            lcd_4bit_send_string_pos(&lcd1, 4, 9, "MATH ERROR!!");
            __delay_ms(2000);
        }
        else
        {
            return op1 / op2;
        }
    }
    else if ('*' == operator1) return op1 * op2;
    else if('^'==operator1) return pow(op1,op2);
    return 0; // For simplicity, returning 0 here
}

static inline u8 isOperand(char x)
{
    if (x == '*' || x == '/' || x == '+' || x == '-' || x == '^')
        return 1;
    else
        return 0;
}

static inline u8 precedence(char x)
{
    if (x == '^')
        return 3;
    else if (x == '*' || x == '/')
        return 2;
    else if (x == '+' || x == '-')
        return 1;
    return 0; // Default return value when x is not an operator
}

static u8 inline calc_is_full(Calculator_t* calc)
{
    return (calc->top == MAX_SIZE);
}

static u8 calc_is_empty(Calculator_t* calc)
{
    return !(calc->top);
}

Return_Status calc_init(Calculator_t* calc)
{
    Return_Status ret = R_NOK;
    if (calc != NULL)
    {
        ret = R_OK;
        calc->top = 0;
    }
    return ret;
}

static Return_Status calc_push(Calculator_t* calc, f8 value)
{
    if (calc != NULL && !calc_is_full(calc))
    {
        calc->data[(calc->top)++] = value;
        return R_OK;
    }
    return R_NOK;
}

static void calc_pop(Calculator_t* calc)
{
    if (calc != NULL && calc->top > 0)
    {
        (calc->top)--;
    }
}

static inline f8 calc_top(Calculator_t* calc)
{
    if (calc != NULL && !calc_is_empty(calc))
    {
        return calc->data[calc->top - 1];
    }
    return 0;
}

static void delete_all_numbers()
{
    memset(infix_exp,' ', strlen(infix_exp));
    current_system=NOT_PRESSED;
    convert_to=NOT_PRESSED;
    converter_enable= NOT_PRESSED;
    lcd_4bit_send_command(&lcd1, _LCD_CLEAR); // Clear the entire LCD screen
    lcd_4bit_send_string(&lcd1, infix_exp); // Display the updated string on the LCD
    lcd_4bit_send_command(&lcd1, _LCD_RETURN_HOME);
    
}

static void delete_num()
{
    if (exp_counter >= 0)
    { // Check if there's at least one character to delete
        infix_exp[exp_counter-1] = '\0'; // Decrement counter and null-terminate the string
    lcd_4bit_send_command(&lcd1, _LCD_CLEAR); // Clear the entire LCD screen
    lcd_4bit_send_command(&lcd1, _LCD_CURSOR_MOVE_SHIFT_LEFT);
    lcd_4bit_send_string(&lcd1, infix_exp);
    }
}

static  u8 check_balamced_brackets(u8* exp1)
{
    u8 opened_brackets = 0;
    u8 closed_brackets = 0;
    u8 len = strlen(exp1);
    for (u8 i = 0; i < len; ++i)
    {
        if (exp1[i] == '(') 
            ++opened_brackets;
        else if (exp1[i] == ')') 
            ++closed_brackets;
    }
    return opened_brackets == closed_brackets;
}

static u8 check_forScientficCalc_customs(u8 keypad_value)
{
    switch (keypad_value)
    {
    case SQRT_SYMBOL:
        lcd_4bit_send_string(&lcd1, "sqrt(");
        strcat(infix_exp, SQRT_STRING);  
       replace_constants(infix_exp,SQRT_STRING,SQRT_SYMBOL);
       return 1;
    case DEL_SYMBOL:
        delete_num();
        return 1;
    case DEL_ALL_SYMBOL:
        delete_all_numbers();
        return 1;
    case EXP_SYMBOL:
        lcd_4bit_send_string(&lcd1, "e");
        strcat(infix_exp, EXP_STRING);
        replace_constants(infix_exp,EXP_STRING,EXP_SYMBOL);
        return 1;
    case ANS_SYMBOL:
        lcd_4bit_send_string(&lcd1, "ANS");
        strcat(infix_exp, ANS_STRING);
        replace_constants(infix_exp,ANS_STRING,ANS_SYMBOL);
        return 1;
    }
    return NOT_PRESSED;
}

static void replace_constants(char *infix_expression, u8* str, u8 symbol) {
    u8 numeric_length;
    u8 identifier_length;
    u8* numeric_value=(u8*)malloc(20);
    memset(numeric_value,'\0', strlen(numeric_value));
    s32 num=0;
    char *ptr = strstr(infix_expression, str);
    if (ptr != NULL)
    {
        switch(symbol)
        {
            case EXP_SYMBOL:
                sprintf(numeric_value, "%.9f", M_E); // Convert M_E to a string
                break;
            case ANS_SYMBOL:
                sprintf(numeric_value, "%f", ans_val); // Convert ans_val to a string
                //exp_counter -=6;
                break;
            case SQRT_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
                exp_counter +=2;
                break;
            case SIN_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(SIN_SYMBOL)); // Convert sqrt result to a string
                break;
            case COS_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
                break;
            case TAN_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
                break;
            case SINH_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
                exp_counter +=2;
                break;
                case COSH_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
               exp_counter +=2;
                break;
                case TANH_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
                exp_counter +=2;
                break;
                case ASIN_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
                exp_counter +=2;
                break;
                case ACOS_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
                exp_counter +=2;
                break;
                case ATAN_SYMBOL:
                sprintf(numeric_value, "%.9f", evaluate_constants(symbol)); // Convert sqrt result to a string
                exp_counter +=2;
                break;                
        }
           numeric_length = strlen(numeric_value);
                identifier_length = strlen(str);
        u8 offset = numeric_length - identifier_length;
        if (numeric_length != identifier_length)
        {
            u8 remaining_length = strlen(ptr + identifier_length);
            memmove(ptr + numeric_length, ptr + identifier_length, remaining_length +1); // Move the rest of the string

            // Copy the numeric value
            memcpy(ptr, numeric_value, numeric_length);

            // Update the length of the string
            u8 string_length = strlen(infix_expression);
            string_length += offset;

            // Update exp_counter
              exp_counter += offset-2;
              exp_counter += offset-2;
        }
    }
    free(numeric_value);
}
static u8 check_forAdvancedCalc_customs(u8 keypad_value)
{
    switch(keypad_value)
    {
        case SIN_SYMBOL:
        lcd_4bit_send_string(&lcd1, "sin(");
        strcat(infix_exp, "sin(");  
       replace_constants(infix_exp,"sin(",SIN_SYMBOL);
       return 1;
          case COS_SYMBOL:
        lcd_4bit_send_string(&lcd1, "cos(");
        strcat(infix_exp, "cos(");  
       replace_constants(infix_exp,"cos(",COS_SYMBOL);
       return 1;
        case TAN_SYMBOL:
        lcd_4bit_send_string(&lcd1, "tan(");
        strcat(infix_exp, "tan(");  
       replace_constants(infix_exp,"tan(",TAN_SYMBOL);
       return 1;
         case SINH_SYMBOL:
        lcd_4bit_send_string(&lcd1, "sinh(");
        strcat(infix_exp, "sinh(");  
       replace_constants(infix_exp,"sinh(",SINH_SYMBOL);
       return 1;
          case COSH_SYMBOL:
        lcd_4bit_send_string(&lcd1, "cosh(");
        strcat(infix_exp, "cosh(");  
       replace_constants(infix_exp,"cosh(",COSH_SYMBOL);
       return 1;
        case TANH_SYMBOL:
        lcd_4bit_send_string(&lcd1, "tanh(");
        strcat(infix_exp, "tanh(");  
       replace_constants(infix_exp,"tanh(",TANH_SYMBOL);
       return 1;
       case ASIN_SYMBOL:
        lcd_4bit_send_string(&lcd1, "asin(");
        strcat(infix_exp, "asin(");  
       replace_constants(infix_exp,"asin(",ASIN_SYMBOL);
       return 1;
          case ACOS_SYMBOL:
        lcd_4bit_send_string(&lcd1, "acos(");
        strcat(infix_exp, "acos(");  
       replace_constants(infix_exp,"acos(",ACOS_SYMBOL);
       return 1;
        case ATAN_SYMBOL:
        lcd_4bit_send_string(&lcd1, "atan(");
        strcat(infix_exp, "atan(");  
       replace_constants(infix_exp,"atan(",ATAN_SYMBOL);
       return 1;
    }
}

static u8 check_minus_for_infix_expression(u8* infix,u8 index)
{
    if(infix[index]=='-')
    {
        if(infix[index-1]=='('||index==0||isOperand(infix[index-1]))
            return UNARY_MINUS;
        else
            return BINARY_MINUS;
    }
    return 0;
}

static u8 check_minus_for_postfix_expression(u8* post,u8 index)
{
    if(post[index]=='-')
    {
        if(isdigit(post[index+1])||post[index+1]=='.')
            return UNARY_MINUS;
        else
            return BINARY_MINUS;
    }
    return 0;
}

static f8 evaluate_constants(u8 symbol) {
    u8* value=(u8*)malloc(15);
    memset(value, '\0', 15);
    u8 counter = 0;
    u8 ret = NOT_PRESSED;
    // Collect digits until closing parenthesis is pressed
    while (ret != ')') {
        ret = NOT_PRESSED;
        while (ret == NOT_PRESSED) {
            keypad_get_value(&scientfic_keypad, &ret);
            __delay_us(350);
        }
        lcd_4bit_send_char_data(&lcd1, ret);
        value[counter++] = ret;
        __delay_ms(100);
    }
    f8 num = atof(value);
    free(value);
    f8 result;  
    switch(symbol)
    {
        case SQRT_SYMBOL:  result = sqrt(num); break;
        case SIN_SYMBOL:   result = sin(num*M_PI/180); break;
        case COS_SYMBOL:   result = cos(num*M_PI/180); break;
        case SINH_SYMBOL:  result = sinh(num*M_PI/180); break;
        case COSH_SYMBOL:  result = cosh(num*M_PI/180); break;          
        case TAN_SYMBOL:   result = tan(num*M_PI/180); break;
        case TANH_SYMBOL:  result = tanh(num*M_PI/180); break;          
        case ASIN_SYMBOL:  result = asin(num); result*= 180/M_PI; break;
        case ACOS_SYMBOL:  result = acos(num); result*= 180/M_PI; break;           
        case ATAN_SYMBOL:  result = atan(num); result*= 180/M_PI; break;
    }
    return result;
}

static void scan_exp(u8 end_symbol)
{
     volatile u8 keypad_value = NOT_PRESSED;
     volatile u8 adv_keypad_value = NOT_PRESSED;    
     while (keypad_value == NOT_PRESSED&&adv_keypad_value == NOT_PRESSED)
        {
                keypad_get_value(&scientfic_keypad, &keypad_value);
                adv_keypad_get_value(&adv_keypad,&adv_keypad_value);
        }
     while(keypad_value!=end_symbol){
         keypad_value = NOT_PRESSED;
         adv_keypad_value= NOT_PRESSED;
        while (keypad_value == NOT_PRESSED&&adv_keypad_value == NOT_PRESSED)
        {
               keypad_get_value(&scientfic_keypad, &keypad_value);
               adv_keypad_get_value(&adv_keypad,&adv_keypad_value);
        }         
        if(adv_keypad_value==POWER_SYMBOL)
        {
            lcd_4bit_send_char_data(&lcd1, POWER_SYMBOL);
            infix_exp[exp_counter++] = POWER_SYMBOL;
        }
        else if(adv_keypad_value==SHIFT_CURSOR_LFET) 
        {
            infix_exp[exp_counter+1]=infix_exp[exp_counter];
            infix_exp[exp_counter]=' ';
            exp_counter--;
            lcd_4bit_send_command(&lcd1,_LCD_CURSOR_MOVE_SHIFT_LEFT);
        }
        else if(adv_keypad_value==SHIFT_CURSOR_RIGHT) 
        {
            infix_exp[exp_counter]=infix_exp[exp_counter+1];
            infix_exp[exp_counter+1]=' ';
            exp_counter--;
            lcd_4bit_send_command(&lcd1,_LCD_CURSOR_MOVE_SHIFT_RIGHT);
        }
        else if(is_in_converter_mode(adv_keypad_value))
        {
                            lcd_4bit_send_string_pos(&lcd1,4,1,"                    ");
            converter_mode(adv_keypad_value);
        }
        else if (check_forAdvancedCalc_customs(adv_keypad_value) == PRESSED)
        {
            exp_counter--;
            adv_keypad_value = NOT_PRESSED;
        }
        else if (check_forScientficCalc_customs(keypad_value) == PRESSED)
        {
            exp_counter--;
            keypad_value = NOT_PRESSED;
        }
        else if (keypad_value == end_symbol)
        {
            break;
        }
        else if(convert_to!=NOT_PRESSED)
        {
            lcd_4bit_send_string_pos(&lcd1,2,1,"NO");
             continue;
             
        }
        else
        {
            lcd_4bit_send_char_data(&lcd1, keypad_value);
            infix_exp[exp_counter++] = keypad_value;
        }
        __delay_us(30); // Adjust delay time as needed       
    }
}

void converter_mode(u8 adv_keypad_value)
{
     u8 arr[22]={};
     if(adv_keypad_value==DEC_SYS)
        {
            lcd_4bit_send_string_pos(&lcd1,3,17,"DEC");
            if(converter_enable==NOT_PRESSED)
            {
                converter_enable=PRESSED;
                lcd_4bit_send_string_pos(&lcd1,4,20-strlen(infix_exp),infix_exp);
            }
            else
            {
                lcd_4bit_send_string_pos(&lcd1,4,1,"                    ");
                convert_to=DEC_SYS;
                switch(current_system)
                {
                 case BIN_SYS:
                    strcpy(arr,BinaryToDecimal(infix_exp)); 
                    break;
                case HEX_SYS:
                    strcpy(arr,HexToDecimal(infix_exp)); 
                    break;
                case OCT_SYS:
                    strcpy(arr,OctalToDecimal(infix_exp));
                    break;   
                } 
                 lcd_4bit_send_string_pos(&lcd1,4,20-strlen(arr),arr);
            }
        }
         else if(adv_keypad_value==HEX_SYS)
         {
             
            lcd_4bit_send_string_pos(&lcd1,3,17,"HEX");
            if(converter_enable==NOT_PRESSED)
            {
                converter_enable=PRESSED;
                lcd_4bit_send_string_pos(&lcd1,4,20-strlen(infix_exp),infix_exp);
            }
            else
            {
                u8 temp[22]={} ;
                lcd_4bit_send_string_pos(&lcd1,4,1,"                    ");
                convert_to=HEX_SYS;
                switch(current_system)
                {
                 case BIN_SYS:
                    strcpy(temp,BinaryToDecimal(infix_exp));
                    strcpy(arr,decimalToHex(temp));
                    break;
                case DEC_SYS:
                    strcpy(arr,decimalToHex(infix_exp));
                    break;
                case OCT_SYS:
                    strcpy(temp,OctalToDecimal(infix_exp));
                    strcpy(arr,decimalToHex(temp)); 
                   break;    
                }   
                lcd_4bit_send_string_pos(&lcd1,4,1,"                    ");
                lcd_4bit_send_string_pos(&lcd1,4,20-strlen(arr),arr);
            }
         }
        else if(adv_keypad_value==BIN_SYS)
        {
            lcd_4bit_send_string_pos(&lcd1,3,17,"BIN");
            if(converter_enable==NOT_PRESSED)
            {
                converter_enable=PRESSED;
                if(is_binary(infix_exp))
                {
                    lcd_4bit_send_string_pos(&lcd1,4,20-strlen(infix_exp),infix_exp);
                }
                else
                {
                    lcd_4bit_send_string_pos(&lcd1, 4, 9, "MATH ERROR!!");
                    return;
                }
            }
            else
            {
                u8 temp[22]={} ;
                lcd_4bit_send_string_pos(&lcd1,4,1,"                    ");
                convert_to=BIN_SYS;
                switch(current_system)
                {
                 case DEC_SYS:
                   strcpy(arr,decimalToBinary(infix_exp)); 
                   break;
                case HEX_SYS:
                   strcpy(arr,hexToBinary(infix_exp)); 
                   break;
                case OCT_SYS:
                    strcpy(temp,OctalToDecimal(infix_exp));
                    strcpy(arr,decimalToBinary(temp)); 
                     break;                      
                }
                 lcd_4bit_send_string_pos(&lcd1,4,1,"                    ");
                lcd_4bit_send_string_pos(&lcd1,4,20-strlen(arr),arr);
            }
        }
         else if(adv_keypad_value==OCT_SYS)
        {
            lcd_4bit_send_string_pos(&lcd1,3,17,"OCT");
            if(converter_enable==NOT_PRESSED)
            {
                converter_enable=PRESSED;
                if(is_oct(infix_exp))
                {
                    lcd_4bit_send_string_pos(&lcd1,4,20-strlen(infix_exp),infix_exp);
                }
                else
                {
lcd_4bit_send_string_pos(&lcd1, 4, 9, "MATH ERROR!!");
                    return;
                }
            }
            else
            {
                convert_to=OCT_SYS;
                lcd_4bit_send_string_pos(&lcd1,4,1,"                    ");
                switch(current_system)
                {
                 case DEC_SYS:
                    strcpy(arr, decimalToOctal(infix_exp));
                    break;
                case HEX_SYS:
                    strcpy(arr, HexToDecimal(infix_exp));
                    strcpy(arr, decimalToOctal(infix_exp));
                    break;
                case BIN_SYS:
                    strcpy(arr, BinaryToOctal(infix_exp));
                    break;                      
                }
            }
             lcd_4bit_send_string_pos(&lcd1,4,1,"                    ");
                lcd_4bit_send_string_pos(&lcd1,4,20-strlen(arr),arr);
                
        }
        current_system=adv_keypad_value;
}
 



u8 is_in_converter_mode(u8 value)
{
    return (value==BIN_SYS||value==OCT_SYS||value==HEX_SYS||value==DEC_SYS);
}




static u8* BinaryToDecimal(u8* bin) {
     u8 len = strlen(bin);
     u32 num = 0;
    u8 keypad_value=NOT_PRESSED;
    for (u8 i = 0; i < len; ++i) {
        if (bin[len - i - 1] == '1') {
            num += pow(BIN_BASE, i);
        }
    }
    u8 num_arr[5]={};
    sprintf(num_arr,"%d",num);
    return num_arr;
}

static u8* hexDigitToBinary(u8 hexDigit) {
    switch(hexDigit) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        
    }
}

// Function to convert a hexadecimal string to binary
static u8* hexToBinary(u8* hex) {
    u8 hexLength = strlen(hex);
    u8* binary=(u8*) malloc(20);
    u8 binaryIndex = 0;
    for (u8 i = 0; i < hexLength; i++) {
        // Convert the current hexadecimal character to binary and append to the binary string
        char* binaryDigit = hexDigitToBinary(hex[i]);
        strcpy(&binary[binaryIndex], binaryDigit);
        binaryIndex += 4;
    }
    // Add null terminator to the binary string
    binary[hexLength * 4] = '\0';
    return binary;
}

static u8* decimalToBinary(u8* dec) {
    u32 x = atoi(dec); // Convert decimal string to integer
    u8 Bin[21] = {};
    u8 i = 0;
    do {
        Bin[i++] = (x % 2) + '0'; // Convert binary digit to character '0' or '1'
        x /= 2;
    } while (x > 0 && i < 20);
    // Add null terminator to create a proper string
    Bin[i] = '\0';
    // Reverse the binary string
    u8 start = 0;
    u8 end = i - 1;
    while (start < end) {
        u8 temp = Bin[start];
        Bin[start] = Bin[end];
        Bin[end] = temp;
        start++;
        end--;
    }
    return Bin;
}

// Function to convert binary to hexadecimal
static u8* binaryToHex(u8* binary) {
    const char hexDigits[] = "0123456789ABCDEF";  // Hexadecimal digits
    u8 binaryLength = strlen(binary);
    u8 paddedLength = binaryLength + (4 - (binaryLength % 4)) % 4; // Calculate the padded length
    u8 hexLength = (paddedLength + 3) / 4;
    u8* hex=(u8*)malloc(hexLength+1);
    // Pad the binary string with leading zeros if necessary
    u8* paddedBinary=(u8*)malloc(paddedLength+1);
    memset(paddedBinary, '0', paddedLength - binaryLength); // Pad with leading zeros
    strcpy(paddedBinary + paddedLength - binaryLength, binary); // Copy the original binary string

    // Convert padded binary to hexadecimal
    for (u8 i = 0, j = 0; i < paddedLength; i += 4, j++) {
        u8 value = 0;
        for (u8 k = 0; k < 4; k++) {
            value = (value << 1) | (paddedBinary[i + k] - '0');
        }
        hex[j] = hexDigits[value];
        hexLength=j;
    }
    hex[hexLength+1] = '\0'; // Null-terminate the hex string
    free(paddedBinary);
    return hex;
}


static u8* BinaryToOctal(u8* bin) {
    // Check if the binary string is empty
    // Get the length of the binary string
    u8 len = strlen(bin);
    // Allocate memory for the octal string (maximum length is len/3 + 1)
    u8* octal = (u8*)malloc((len / 3 + 1) * sizeof(u8));
    // Initialize variables
    u8 octalIndex = 0;
    u8 octalDigit = 0;
    u8 bitIndex = 0;
    // Loop through the binary string from right to left
    for (u8 i = len - 1; i >= 0; i--) {
        // Convert character to integer (0 or 1)
        u8 bit = bin[i] - '0';
        // Calculate the octal digit by adding the binary bits
        octalDigit += bit << bitIndex;
        bitIndex++;
        // If we have accumulated 3 bits or reached the left end of the string
        if (bitIndex == 3 || i == 0) {
            // Store the octal digit in the result string
            octal[octalIndex++] = octalDigit + '0';
            // Reset variables for the next octal digit
            octalDigit = 0;
            bitIndex = 0;
        }
    }
    // Reverse the octal string
    for (u8 i = 0; i < octalIndex / 2; i++) {
        u8 temp = octal[i];
        octal[i] = octal[octalIndex - i - 1];
        octal[octalIndex - i - 1] = temp;
    }

    // Null-terminate the octal string
    octal[octalIndex] = '\0';
    return octal;
}

static u8* decimalToOctal(u8* dec) {
    u32 decimal = atoi(dec); // Convert input string to integer
    u8* octal=(u8*)malloc(20);
    u8 index = 0; // Index to store octal digits
    if (decimal == 0) {
        octal[index++] = '0'; // Special case for decimal 0
    } else {
        // Convert decimal to octal
        while (decimal != 0) {
            u8 remainder = decimal % 8; // Calculate remainder
            octal[index++] = remainder + '0'; // Convert remainder to character
            decimal /= 8; // Update decimal by dividing it by 8
        }
    }
    octal[index] = '\0'; // Null-terminate the octal string
    // Reverse the octal string
    u8 start = 0;
    u8 end = index - 1;
    while (start < end) {
        u8 temp = octal[start];
        octal[start] = octal[end];
        octal[end] = temp;
        start++;
        end--;
    }
    return octal;
}

static u8* decimalToHex(u8* dec) {
    u32 x = atoi(dec); // Convert decimal string to integer
    u8* hex=(u8*)malloc(20);
    u8 i = 0; // Index for hexadecimal string
    
    // Convert decimal number to hexadecimal string
    do {
        int remainder = x % 16; // Calculate remainder when divided by 16
        hex[i++] = (remainder < 10) ? remainder + '0' : remainder - 10 + 'A'; // Convert remainder to hexadecimal digit
        x /= 16; // Update quotient for next iteration
    } while (x != 0);
    
    hex[i] = '\0'; // Null-terminate the hexadecimal string
    
    // Reverse the hexadecimal string
    u8 start = 0;
    u8 end = i - 1;
    while (start < end) {
        char temp = hex[start];
        hex[start] = hex[end];
        hex[end] = temp;
        start++;
        end--;
    }
    return hex;
    
}

static u8* OctalToDecimal(u8* oct) {
    u32 decimal = 0; 
    u8 octalLength = strlen(oct); 
    u8 index = 0; 
    while (index < octalLength) {
        u8 digit = oct[index] - '0'; 
        decimal += digit * pow(8, octalLength - index - 1); 
        index++; // Move to the next digit
    }
    u8* dec=(u8*)malloc(20);
    sprintf(dec,"%d",decimal);
    return dec;
}

static u8* HexToDecimal(u8* hex) {
    unsigned long decimal = 0;
    u8 length = strlen((char*)hex);

    // Iterate through each character of the hexadecimal string
    for (u8 i = 0; i < length; i++) {
        // Convert hexadecimal digit to decimal value
        unsigned long digitValue;
        if (hex[i] >= '0' && hex[i] <= '9') {
            digitValue = hex[i] - '0';
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            digitValue = hex[i] - 'A' + 10;
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            digitValue = hex[i] - 'a' + 10;
        }
        // Multiply the current decimal value by 16 and add the digit value
        decimal = decimal * 16 + digitValue;
    }
    u8* dec=(u8*)malloc(6);
    sprintf(dec,"%d",decimal);
    return dec;
}



static inline u8 is_binary(u8* bin)
{
    for(u8 i=0;i<strlen(bin);i++)
    {
        if(bin[i]>'1') return 0;
    }
    return 1;
}
static inline u8 is_oct(u8* oct)
{
    for(u8 i=0;i<strlen(oct);i++)
    {
        if(oct[i]>'7') return 0;
    }
    return 1;
}
