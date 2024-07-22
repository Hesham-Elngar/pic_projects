#include"application.h"
#include"MCAL_Layer/ADC/adc.h"

Lcd_4bit lcd1={
  .en.direction=gpio_direction_output,.en.logic=gpio_logic_low,.en.port=PORTC_INDEX,.en.pin=PIN0_INDEX,
.rs.direction=gpio_direction_output,.rs.logic=gpio_logic_low,.rs.port=PORTC_INDEX,.rs.pin=PIN1_INDEX,
.data[0].direction=gpio_direction_output,.data[0].logic=gpio_logic_low,.data[0].port=PORTC_INDEX,.data[0].pin=PIN2_INDEX,  
.data[1].direction=gpio_direction_output,.data[1].logic=gpio_logic_low,.data[1].port=PORTC_INDEX,.data[1].pin=PIN3_INDEX,  
.data[2].direction=gpio_direction_output,.data[2].logic=gpio_logic_low,.data[2].port=PORTC_INDEX,.data[2].pin=PIN4_INDEX,  
.data[3].direction=gpio_direction_output,.data[3].logic=gpio_logic_low,.data[3].port=PORTC_INDEX,.data[3].pin=PIN5_INDEX,  
};

ADC_Config_t temp_obj,pot_obj;
volatile int temp_res='\0'; 
volatile int temp_prev_res='\0'; 
volatile int pot_res='\0'; 
volatile int pot_prev_res='\0'; 
char str_temp_res[12];
char str_pot_res[12];
void adc_isr() {
    // Temperature
    ADC_GetConverion(&temp_obj, ADC_AN12_CHANNEL, &temp_res); 
    if (temp_res != temp_prev_res) {
        float voltage_temp = temp_res * (5.0 / 1023.0);
        float temperatureC = voltage_temp * 100.0; // LM35 gives 10mV per degree Celsius

        memset(str_temp_res, ' ',20);
        lcd_4bit_send_string_pos(&lcd1, 1, 1, str_temp_res);
        sprintf(str_temp_res, "Temp: %.2fC", temperatureC);

        //lcd_4bit_send_command(&lcd1, _LCD_CLEAR); // Clear display
        lcd_4bit_send_string_pos(&lcd1, 1, 1, str_temp_res);
    }
    temp_prev_res = temp_res;

    // Potentiometer
    ADC_GetConverion(&pot_obj, ADC_AN1_CHANNEL, &pot_res); 
    if (pot_res != pot_prev_res) {
        float voltage_pot = pot_res * (5.0 / 1023.0);

        memset(str_pot_res, ' ',20);
        sprintf(str_pot_res, "Volt: %.2fV", voltage_pot);

        lcd_4bit_send_string_pos(&lcd1, 2, 1, str_pot_res);
    }
    pot_prev_res = pot_res;
}

ADC_Config_t temp_obj = {
    .ADC_InterruptHandler = adc_isr,
    .Channel = ADC_AN12_CHANNEL,
    .Conversion_Clock_Select = ADC_CONVERSION_FOSC_DIV_BY_16,
    .Acquisition_Time = ADC_12_TAD,
    .ADC_Voltage_Reference = ADC_DisablevoltageRefernce,
    .ADC_Result_Format = ADC_RESULT_RIGHT
};

ADC_Config_t pot_obj = {
    .ADC_InterruptHandler = adc_isr,
    .Channel = ADC_AN1_CHANNEL,
    .Conversion_Clock_Select = ADC_CONVERSION_FOSC_DIV_BY_16,
    .Acquisition_Time = ADC_12_TAD,
    .ADC_Voltage_Reference = ADC_DisablevoltageRefernce,
    .ADC_Result_Format = ADC_RESULT_RIGHT
};
LED led1={.pin=PIN0_INDEX,.port=PORTC_INDEX,.status=LED_OFF};
int main(){
    lcd_4bit_initialize(&lcd1);
    ADC_Init(&temp_obj);
    ADC_Init(&pot_obj);
    while(1)
    {
         ADC_GetConverion_Interrupt(&temp_obj,ADC_AN12_CHANNEL);
         ADC_GetConverion_Interrupt(&pot_obj,ADC_AN1_CHANNEL);
    }
    return EXIT_SUCCESS;
}
void app_initialize()
{
    ecu_layer_initialize(); 
    
}
