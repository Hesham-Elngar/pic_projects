/* 
 * File:   keypad.?
 * Author: hesham
 *
 * Created on November 27, 2023, 5:01 AM
 */
#include <builtins.h>
#include <string.h>
#include"keypad.h"

u8 adv_keypad_values[ADV_KEYPAD_ROWS][ADV_KEYPAD_COLUMNS]={
                                    {'a','s','d','f'},
                                    {'g','h','j','k'},
                                    {'l','z','^','c'},
                                    {'v','b','n','m'}
                                              };

Return_Status adv_keypad_initialize(ADV_Keypad_t* keypad)
{
    Return_Status ret = R_NOK;
    if(keypad!=NULL)
    {
        for(int i=0;i<ADV_KEYPAD_ROWS;i++)
        {
            gpio_pin_initialize(&(keypad->keypad_row[i]));
        }
        for(int i=0;i<ADV_KEYPAD_COLUMNS;i++)
        {
            gpio_pin_initialize(&(keypad->keypad_column[i]));
        }
    }
    return ret;
}

Return_Status adv_keypad_get_value(ADV_Keypad_t *keypad,u8 *value)
{
    Return_Status ret = R_NOK;
    if(keypad!=NULL)
    {
        for(int row_counter=0;row_counter<ADV_KEYPAD_ROWS;row_counter++)
        {
            for(int j=0;j<ADV_KEYPAD_ROWS;++j)
            {
                gpio_write_pin_logic(&(keypad->keypad_row[j]),gpio_logic_low);
            }
            gpio_write_pin_logic(&(keypad->keypad_row[row_counter]),gpio_logic_high);
            __delay_ms(24);
            for(int col_counter=0;col_counter<ADV_KEYPAD_COLUMNS;++col_counter)
            {
            logic_t column_value;
            gpio_read_pin_logic(&(keypad->keypad_column[col_counter]),&column_value);
            if(gpio_logic_high==column_value)
            {
                *value=adv_keypad_values[row_counter][col_counter]; 
                break;
            }
            }
        }
    }
    return ret;
}


