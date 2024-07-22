#include "application.h"
#include "MCAL_Layer/ADC/adc.h"
#include "MCAL_Layer/Timers/timer0.h"
#include <time.h>
    
#define MAX_INPUT 2
#define NOT_PRESSED '\0'

u8 get_keypad_input();
LED led1 = {.pin = PIN0_INDEX, .port = PORTD_INDEX, .status = LED_OFF};
Lcd_4bit lcd1 = {
    .en.direction = gpio_direction_output, .en.logic = gpio_logic_low, .en.port = PORTC_INDEX, .en.pin = PIN0_INDEX,
    .rs.direction = gpio_direction_output, .rs.logic = gpio_logic_low, .rs.port = PORTC_INDEX, .rs.pin = PIN1_INDEX,
    .data[0].direction = gpio_direction_output, .data[0].logic = gpio_logic_low, .data[0].port = PORTC_INDEX, .data[0].pin = PIN2_INDEX,
    .data[1].direction = gpio_direction_output, .data[1].logic = gpio_logic_low, .data[1].port = PORTC_INDEX, .data[1].pin = PIN3_INDEX,
    .data[2].direction = gpio_direction_output, .data[2].logic = gpio_logic_low, .data[2].port = PORTC_INDEX, .data[2].pin = PIN4_INDEX,
    .data[3].direction = gpio_direction_output, .data[3].logic = gpio_logic_low, .data[3].port = PORTC_INDEX, .data[3].pin = PIN5_INDEX,
};

volatile uint16_t seconds, minutes, hours;
char duration[3] = "PM";
char str[50];
int flag;

void tmr0_handler() {
    ++flag;
    ++seconds;
    if (seconds == 60) {
        seconds = 0;
        ++minutes;
    }
    if (minutes == 60) {
        minutes = 0;
        ++hours;
    }
    if (hours == 13) {
        hours = 1;
        if (strcmp(duration, "PM") == 0) {
            strcpy(duration, "AM");
        } else {
            strcpy(duration, "PM");
        }
    }
    
}

TIMER0_t tmr0_obj = {
    .Timer0_InterruptHandler = tmr0_handler,
    .edge = TIMER0_SelectRisingEdge_CFG,
    .mode = TIMER0_TIMER_MODE_CFG,
    .register_size = TIMER0_16BIT_MODE_CFG,
    .preload_value = 3036,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
};
void get_time_input() {
    char input[MAX_INPUT + 1];
    int i;
    __delay_ms(1000);
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    // Input Hours
    lcd_4bit_send_string_pos(&lcd1, 1, 1, "Enter Hours:");
    for (i = 0; i < MAX_INPUT; i++) {
        input[i] = get_keypad_input();
        lcd_4bit_send_char_data(&lcd1, input[i]);
        __delay_ms(800); // Debounce delay
    }
    input[i] = '\0';
    hours = atoi(input);

    // Input Minutes
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    lcd_4bit_send_string_pos(&lcd1, 1, 1, "Enter Minutes:");
    for (i = 0; i < MAX_INPUT; i++) {
        input[i] = get_keypad_input();
        lcd_4bit_send_char_data(&lcd1, input[i]);
        __delay_ms(800); // Debounce delay
    }
    input[i] = '\0';
    minutes = atoi(input);

    // Input Seconds
    lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
    lcd_4bit_send_string_pos(&lcd1, 1, 1, "Enter Seconds:");
    for (i = 0; i < MAX_INPUT; i++) {
        input[i] = get_keypad_input();
        lcd_4bit_send_char_data(&lcd1, input[i]);
        __delay_ms(800); // Debounce delay
    }
    input[i] = '\0';
    seconds = atoi(input);

    // Determine AM/PM
    if (hours >= 12) {
        strcpy(duration, "PM");
        if (hours > 12) {
            hours -= 12;
        }
    } else {
        strcpy(duration, "AM");
        if (hours == 0) {
            hours = 12;
        }
    }
}

int main() {
    LED_init(&led1);
    app_initialize();
    timer0_Init(&tmr0_obj);
    u8 first=1;
    //get_time_input();
    while (1) {
        if(first==1)
        {
            strcpy(duration,"  ");
        }
         lcd_4bit_send_string_pos(&lcd1, 1, 1,"Time: ");
    sprintf(str, "%02u:%02u:%02u %s", hours, minutes, seconds, duration);
    lcd_4bit_send_string(&lcd1, str);
    lcd_4bit_send_string_pos(&lcd1,2,1,"Press 1 to Set Clock");
    u8 keypad_val=NOT_PRESSED;
    keypad_get_value(&keypad1,&keypad_val);
    if(keypad_val=='1')
        {
            first==0;
            get_time_input();
            __delay_ms(200);
        }
    }
    return EXIT_SUCCESS;
}

void app_initialize() {
    ecu_layer_initialize();
}

u8 get_keypad_input()
{
    u8 keypad_val=NOT_PRESSED;
    while(keypad_val==NOT_PRESSED)
    {
        keypad_get_value(&keypad1,&keypad_val); 
    }
    return keypad_val; 
}