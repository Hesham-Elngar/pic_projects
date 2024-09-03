#include "application.h"
#include "MCAL_Layer/ADC/adc.h"
#include "MCAL_Layer/Timers/Timer2.h"
#include "MCAL_Layer/CCP/hal_ccp.h"
#include "MCAL_Layer/interrupt/interrupt_manager.h"
#include "MCAL_Layer/Timers/timer0.h"

#define NOT_PRESSED '\0'
#define TEMPERATURE_THRESHOLD 100.0

void app_initialize();
void electrical_heater();

volatile u8 heater_on = 0;
volatile u8 adc_ready = 0;
volatile u8 motor_on = 1;
ADC_Config_t temp_sensor;

void int0_isr() {
    heater_on = !heater_on;
    if (heater_on) {
        lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
        lcd_4bit_send_string(&lcd1, "Boiling");
        motor_on = 1;
        ADC_GetConverion_Interrupt(&temp_sensor, ADC_AN0_CHANNEL); // Start ADC conversion when heater is turned on
    } else {
        lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
        lcd_4bit_send_string(&lcd1, "Heating Stopped");
        dc_motor_stop(&Elec_Heater_motor);
        motor_on = 0;
    }
}

void adc_isr() {
    adc_ready = 1;
    electrical_heater(); //Call the heater control function directly from the ISR
}

void ccp_isr() {
    lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
    lcd_4bit_send_string(&lcd1, "Heating Finished");
    dc_motor_stop(&Elec_Heater_motor);
    heater_on = 0;  // Automatically turn off heater
}

ccp_t ccp_obj = {
    .CCP1_InterruptHandler = ccp_isr,
    .ccp_inst = CCP1_INST,
    .ccp_mode = CCP_COMPARE_MODE_SELECTED,
    .ccp_mode_variant = CCP_COMPARE_MODE_GEN_EVENT,
};

ADC_Config_t temp_sensor = {
    .ADC_InterruptHandler = adc_isr,
    .Channel = ADC_AN0_CHANNEL,
    .Acquisition_Time = ADC_16_TAD,
    .Conversion_Clock_Select = ADC_CONVERSION_FOSC_DIV_BY_4,
    .ADC_Voltage_Reference = ADC_DisablevoltageRefernce,
    .ADC_Result_Format = ADC_RESULT_RIGHT
};

EXT_INTx_t int_obj = {
    .EXT_InterruptHandler = int0_isr,
    .edge = Interrupt_Rising_Edge,
    .mcu_pin.direction = gpio_direction_input,
    .mcu_pin.pin = PIN0_INDEX,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.logic = gpio_logic_low,
    .source = EXT_INT0
};

volatile float temperatureInCelsius;

int main() {
    app_initialize();
    while (1) ;
    return EXIT_SUCCESS;
}

void app_initialize() {
    ecu_layer_initialize();
    ADC_Init(&temp_sensor);
    INTx_Init(&int_obj);
    CCP_Init(&ccp_obj);
    CCP_Compare_Mode_Set_Value(&ccp_obj, 205); // Set CCP value corresponding to 100 C
}

void electrical_heater() {
    adc_result result;
    float voltage_temp;

    // Get ADC result
    ADC_GetConverionResult(&temp_sensor, &result);
    voltage_temp = result * (5.0 / 1023.0);
    temperatureInCelsius = voltage_temp * 100.0;  // LM35 gives 10mV per degree Celsius

    if (temperatureInCelsius < TEMPERATURE_THRESHOLD && heater_on) {
        dc_motor_move_right(&Elec_Heater_motor);
        lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
        lcd_4bit_send_string(&lcd1, "Boiling...");
    } else if(temperatureInCelsius < TEMPERATURE_THRESHOLD && heater_on==0) {
        lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
        lcd_4bit_send_string(&lcd1, "Heating Stopped");
        dc_motor_stop(&Elec_Heater_motor);
        heater_on = 0;  // Automatically turn off heater
    }
    else
    {
         lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
        lcd_4bit_send_string(&lcd1, "Heating Finished");
        dc_motor_stop(&Elec_Heater_motor);
        heater_on = 0;  // Automatically turn off heater

    }

    if (heater_on) {
        // Start a new ADC conversion if the heater is still on
        ADC_GetConverion_Interrupt(&temp_sensor, ADC_AN0_CHANNEL);
    }
}
