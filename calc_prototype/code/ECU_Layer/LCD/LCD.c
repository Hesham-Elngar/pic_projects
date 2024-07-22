/* 
 * File:   LCD.c
 * Author: hesham
 *
 * Created on October 31, 2023, 12:46 AM
 */
#include"LCD.h"

static void lcd_4bit_send_4_bit(Lcd_4bit* lcd,u8 command);
static void lcd_4bit_send_enable_signal(Lcd_4bit* lcd);
static void lcd_8bit_send_enable_signal(Lcd_8bit* lcd);
static void lcd_8bit_set_cursor(Lcd_8bit* lcd,u8 row,u8 column);
static void lcd_4bit_set_cursor(Lcd_4bit* lcd,u8 row,u8 column);

Return_Status lcd_4bit_initialize(Lcd_4bit* lcd){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        gpio_pin_initialize(&(lcd->rs));
        gpio_pin_initialize(&(lcd->en));
        for(int i=0;i<4;i++){
            gpio_pin_initialize(&lcd->data[i]);
        }
        __delay_ms(20);
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5); 
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150); 
        lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        lcd_4bit_send_command(lcd,_LCD_CLEAR);
        lcd_4bit_send_command(lcd,_LCD_RETURN_HOME);
        lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        lcd_4bit_send_command(lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINE);
        lcd_4bit_send_command(lcd,0x80);
   }
    return ret;
}

Return_Status lcd_4bit_send_command(Lcd_4bit* lcd,u8 command){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        gpio_write_pin_logic(&lcd->rs,gpio_logic_low);
        lcd_4bit_send_4_bit(lcd,command>>4);
        lcd_4bit_send_enable_signal(lcd);
        lcd_4bit_send_4_bit(lcd,command);
        lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
} 

Return_Status lcd_4bit_send_char_data(Lcd_4bit *lcd,u8 data){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        gpio_write_pin_logic(&lcd->rs,gpio_logic_high);
        lcd_4bit_send_4_bit(lcd,data>>4);
        lcd_4bit_send_enable_signal(lcd);
        lcd_4bit_send_4_bit(lcd,data);
        lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Return_Status lcd_4bit_send_char_data_pos(Lcd_4bit* lcd,u8 row,u8 column,u8 data)
{
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        lcd_4bit_set_cursor(lcd,row,column);
        lcd_4bit_send_char_data(lcd,data);
        
    }
    return ret;
}

Return_Status lcd_4bit_send_custom_chr(Lcd_4bit* lcd,u8 row,u8 column,u8 custom_chr[],u8 mem_pos){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        lcd_4bit_send_command(lcd,_LCD_CGRAM_START+(8*mem_pos));
        for(int i=0;i<8;i++){
            lcd_4bit_send_char_data(lcd,custom_chr[i]);
        }
        lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return ret;
}

Return_Status lcd_4bit_send_string(Lcd_4bit* lcd,u8* str)
{
   Return_Status ret=R_NOK;
    if(lcd!=NULL){
       ret=R_OK;
       while(*str!='\0'){
           lcd_4bit_send_char_data(lcd,*str++);
       }
    }
    return ret; 
}
Return_Status lcd_4bit_send_string_pos(Lcd_4bit* lcd,u8 row,u8 column,u8* str)
{
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
       ret=R_OK;
       lcd_4bit_set_cursor(lcd,row,column);
       while(*str!='\0'){
           lcd_4bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
}
/************************************************************************************************************/
Return_Status lcd_8bit_initialize(Lcd_8bit* lcd){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        gpio_pin_initialize(&(lcd->rs));
        gpio_pin_initialize(&(lcd->en));
        for(int i=0;i<8;i++){
            gpio_pin_initialize(&lcd->data[i]);
        }
        __delay_ms(20);
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5); 
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150); 
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        lcd_8bit_send_command(lcd,_LCD_CLEAR);
        lcd_8bit_send_command(lcd,_LCD_RETURN_HOME);
        lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        lcd_8bit_send_command(lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        lcd_8bit_send_command(lcd,0x80);        
   }
    return ret;
}
Return_Status lcd_8bit_send_command(Lcd_8bit* lcd,u8 command){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        gpio_write_pin_logic(&lcd->rs,gpio_logic_low);
        for(int i=0;i<8;i++){
            gpio_write_pin_logic(&(lcd->data[i]),(command>>i)&0x01);
        }
        lcd_8bit_send_enable_signal(lcd);   
    }
    return ret;
}
Return_Status lcd_8bit_send_char_data(Lcd_8bit* lcd,u8 data){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        gpio_write_pin_logic(&lcd->rs,gpio_logic_high);
        for(int i=0;i<8;i++){
            gpio_write_pin_logic(&(lcd->data[i]),(data>>i)&0x01);
        }
        lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}
Return_Status lcd_8bit_send_char_data_pos(Lcd_8bit* lcd,u8 row,u8 column,u8 data){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        lcd_8bit_set_cursor(lcd,row,column);
        lcd_8bit_send_char_data(lcd,data);
    }
    return ret;
}
Return_Status lcd_8bit_send_custom_chr(Lcd_8bit* lcd,u8 row,u8 column,u8 custom_chr[],u8 mem_pos){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
        ret=R_OK;
        lcd_8bit_send_command(lcd,_LCD_CGRAM_START+(8*mem_pos));
        for(int i=0;i<8;i++){
            lcd_8bit_send_char_data(lcd,custom_chr[i]);
        }
        lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    return ret;
}

Return_Status lcd_8bit_send_string(Lcd_8bit* lcd,u8* str){
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
       ret=R_OK;
       while(*str!='\0'){
           lcd_8bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
}

Return_Status lcd_8bit_send_string_pos(Lcd_8bit* lcd,u8 row,u8 column,u8* str)
{
    Return_Status ret=R_NOK;
    if(lcd!=NULL){
       ret=R_OK;
       lcd_8bit_set_cursor(lcd,row,column);
       while(*str!='\0'){
           lcd_8bit_send_char_data(lcd,*str++);
       }
    }
    return ret;
    
}


void convert_byte_to_string(u8 value,u8* str){
    if(str){
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    }
}
void convert_short_to_string(u16 value,u8* str){
     if(str){
        memset(str,'\0',6);
        sprintf(str,"%i",value);
    }
}
void convert_int_to_string(u32 value,u8* str){
     if(str){
        memset(str,'\0',11);
        sprintf(str,"%i",value);
    }
}


static void lcd_4bit_send_4_bit(Lcd_4bit* lcd,u8 command){
    for(int i=0;i<4;i++){
        gpio_write_pin_logic(&lcd->data[i],(command>>i)&0x01);
    }
}
static void lcd_4bit_send_enable_signal(Lcd_4bit* lcd){
    gpio_write_pin_logic(&(lcd->en),gpio_logic_high);
    __delay_us(2);
    gpio_write_pin_logic(&(lcd->en),gpio_logic_low);
}
static void lcd_8bit_send_enable_signal(Lcd_8bit* lcd){
    gpio_write_pin_logic(&(lcd->en),gpio_logic_high);
    __delay_us(2);
    gpio_write_pin_logic(&(lcd->en),gpio_logic_low);
}
static void lcd_8bit_set_cursor(Lcd_8bit* lcd,u8 row,u8 column){
    column--;
    switch(row){
        case 1:  lcd_8bit_send_command(lcd,(0x80+column)); break;
        case 2:  lcd_8bit_send_command(lcd,(0xc0+column)); break;
        case 3:  lcd_8bit_send_command(lcd,(0x94+column)); break;
        case 4 : lcd_8bit_send_command(lcd,(0xd4+column)); break;
        default:;
    }   
}
static void lcd_4bit_set_cursor(Lcd_4bit* lcd,u8 row,u8 column){
    column--;
    switch(row){
        case 1:  lcd_4bit_send_command(lcd,(0x80+column)); break;
        case 2:  lcd_4bit_send_command(lcd,(0xc0+column)); break;
        case 3:  lcd_4bit_send_command(lcd,(0x94+column)); break;
        case 4 : lcd_4bit_send_command(lcd,(0xd4+column)); break;
        default:;
    }   
}