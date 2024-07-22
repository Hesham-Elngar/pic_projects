/* 
 * File:   app.c
 * Author: hesham
 *
 * Created on February 19, 2024, 11:34 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include"app.h"
#include "Mcal_Layer/EEPROM/eeprom.h"
#include "Hal_Layer/LED/LED.h"
int main() {
    app_initialize();
    if(is_pass_pressed()==NOT_PRESSESD)
    {
        set_password();   
        EEPROM_WriteByte(EEPROM_STATUS_LOCATION,PRESSESD);
        exit(0);
    }
    else if(is_pass_pressed()==PRESSESD)
    {
        LED_on(&red_led);
        LED_off(&yellow_led);
        u8 check_values[PASSWORD_MAX_NUMBER]={NOT_PRESSESD};
        u8 tries=TRIES_MAX_NUMBER;
        u8 flag;
        
       do
       {
         lcd_4bit_send_command(&lcd_obj,_LCD_CLEAR);
         enter_password(check_values);
         lcd_4bit_send_command(&lcd_obj,_LCD_CLEAR);
          flag=check_password(check_values);
        if(flag==1)
        {
            lcd_4bit_send_string_pos(&lcd_obj,1,5,"CORRECT PASSWORD");
            lcd_4bit_send_string_pos(&lcd_obj,2,5,"SYSTEM OPENED");
            LED_on(&yellow_led);
            LED_off(&red_led);
            __delay_ms(4000);
            exit(0);
        }
        else
        {
            tries--;
            lcd_4bit_send_string_pos(&lcd_obj,1,3,"WRONG PASSWORD");
            lcd_4bit_send_string_pos(&lcd_obj,2,3,"TRIES LEFT : ");
            lcd_4bit_send_char_data(&lcd_obj,tries+48);
            __delay_ms(1000);
        }
       }while(tries>0);      
       lcd_4bit_send_command(&lcd_obj,_LCD_CLEAR);
       lcd_4bit_send_string_pos(&lcd_obj,1,3,"WRONG PASSWORD");
       lcd_4bit_send_string_pos(&lcd_obj,2,3,"SYSTEM CLOSED");
        exit(0);
    }
    return (EXIT_SUCCESS);
}

void app_initialize()
{
    hal_init();
}
u8 is_pass_pressed()
{ 
    u8 ret='\0';
    EEPROM_ReadByte(EEPROM_STATUS_LOCATION,&ret);
    return (ret==PRESSESD);
}
void set_password()
{
    u8 pass_values[PASSWORD_MAX_NUMBER]={NOT_PRESSESD};
    lcd_4bit_send_string_pos(&lcd_obj,1,5,"WELCOME");
        for(int i=0;i<4;++i){
           lcd_4bit_send_char_data(&lcd_obj,'.');
            __delay_ms(400);
        }
        __delay_ms(400);
        lcd_4bit_send_command(&lcd_obj,_LCD_CLEAR);
        lcd_4bit_send_string_pos(&lcd_obj,1,1,"SELECT PASS : ");
        lcd_4bit_send_command(&lcd_obj,_LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF);
        for(int i=0;i<PASSWORD_MAX_NUMBER;++i){
            while(pass_values[i]==NOT_PRESSESD){
                 keypad_get_value(&keypad_obj,&pass_values[i]);
            }
            EEPROM_WriteByte(EEPROM_PASS_START_LOCATION+i,(pass_values[i]-48));
            lcd_4bit_send_char_data(&lcd_obj,pass_values[i]);
            __delay_ms(300);
           lcd_4bit_send_command(&lcd_obj,_LCD_CURSOR_MOVE_SHIFT_LEFT);
            lcd_4bit_send_char_data(&lcd_obj,'*');
        }   
        lcd_4bit_send_command(&lcd_obj,_LCD_CLEAR);
        lcd_4bit_send_string_pos(&lcd_obj,1,1,"PASS SAVED");
        __delay_ms(500);
}

void enter_password(u8 check_values[])
{
        memset(check_values,NOT_PRESSESD,PASSWORD_MAX_NUMBER);
        lcd_4bit_send_string_pos(&lcd_obj,1,1,"ENTER PASS : ");
        lcd_4bit_send_command(&lcd_obj,_LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF);
        u8 pass_counter=0;
        u8 saved_value;
        for(int i=0;i<PASSWORD_MAX_NUMBER;++i){
            while(check_values[i]==NOT_PRESSESD){
                 keypad_get_value(&keypad_obj,&check_values[i]);
            }
            lcd_4bit_send_char_data(&lcd_obj,check_values[i]);
            __delay_ms(300);
           lcd_4bit_send_command(&lcd_obj,_LCD_CURSOR_MOVE_SHIFT_LEFT);
            lcd_4bit_send_char_data(&lcd_obj,'*');
        }
}
u8 check_password(u8 check_values[])
{
   u8 saved_value,flag=1; 
    for(int i=0;i<PASSWORD_MAX_NUMBER;++i){
            EEPROM_ReadByte(EEPROM_PASS_START_LOCATION+i,&saved_value);
            if(check_values[i]!=(saved_value+48))
            {
                flag=0;
                break;
            }
    }
   return flag;
}

    