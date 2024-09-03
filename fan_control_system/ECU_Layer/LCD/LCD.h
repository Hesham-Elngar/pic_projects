/* 
 * File:   LCD.h
 * Author: hesham
 *
 * Created on October 31, 2023, 12:46 AM
 */

#ifndef LCD_H
#define	LCD_H
#include"../../MCAL_Layer/GPIO/GPIO.h"
#include"string.h"

#define _LCD_CLEAR                      0X01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28

#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80


typedef struct{
    pin_config_info rs;
    pin_config_info en;
    pin_config_info data[4];
}Lcd_4bit;

typedef struct{
    pin_config_info rs;
    pin_config_info en;
    pin_config_info data[8];           
}Lcd_8bit;

Return_Status lcd_4bit_initialize(Lcd_4bit* lcd);
Return_Status lcd_4bit_send_command(Lcd_4bit* lcd,u8 command); 
Return_Status lcd_4bit_send_char_data(Lcd_4bit *lcd,u8 data);
Return_Status lcd_4bit_send_char_data_pos(Lcd_4bit* lcd,u8 row,u8 column,u8 data);
Return_Status lcd_4bit_send_custom_chr(Lcd_4bit* lcd,u8 row,u8 column,u8 custom_chr[],u8 mem_pos);
Return_Status lcd_4bit_send_string(Lcd_4bit* lcd,u8* str);
Return_Status lcd_4bit_send_string_pos(Lcd_4bit* lcd,u8 row,u8 column,u8* str);

Return_Status lcd_8bit_initialize(Lcd_8bit* lcd);
Return_Status lcd_8bit_send_command(Lcd_8bit* lcd,u8 command);
Return_Status lcd_8bit_send_char_data(Lcd_8bit* lcd,u8 data);
Return_Status lcd_8bit_send_char_data_pos(Lcd_8bit* lcd,u8 row,u8 column,u8 data);
Return_Status lcd_8bit_send_custom_chr(Lcd_8bit* lcd,u8 row,u8 column,u8 custom_chr[],u8 mem_pos);
Return_Status lcd_8bit_send_string(Lcd_8bit* lcd,u8* str);
Return_Status lcd_8bit_send_string_pos(Lcd_8bit* lcd,u8 row,u8 column,u8* str);

void convert_byte_to_string(u8 value,u8* str);
void convert_short_to_string(u16 value,u8* str);
void convert_int_to_string(u32 value,u8* str);


#endif	/* LCD_H */

