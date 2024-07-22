#include"application.h"
#include"MCAL_Layer/ADC/adc.h"
#include "MCAL_Layer/Timers/timer0.h"

LED led1={.pin=PIN0_INDEX,.port=PORTC_INDEX,.status=LED_OFF};
LED led2={.pin=PIN1_INDEX,.port=PORTC_INDEX,.status=LED_OFF};
LED led3={.pin=PIN2_INDEX,.port=PORTC_INDEX,.status=LED_OFF};
volatile int flag=0;
void tmr0_handler()
{   
    if(flag==0)
    {
        LED_on(&led1);
        LED_off(&led2);
        LED_off(&led3);
        flag++;
    }
    else if(flag==1)
    {
        LED_on(&led2);
        LED_off(&led1);
        LED_off(&led3); 
        ++flag;  
    }
    else if(flag==2)
    {
        LED_on(&led3);
        LED_off(&led1);
        LED_off(&led2); 
        flag=0;  
    }
     
}

TIMER0_t tmr0_obj={
    .Timer0_InterruptHandler=tmr0_handler,
    .edge=TIMER0_SelectRisingEdge_CFG,.mode=TIMER0_TIMER_MODE_CFG,
    .register_size=TIMER0_16BIT_MODE_CFG,
    .preload_value=3036
    ,.prescaler_enable=TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value=TIMER0_PRESCALER_DIV_BY_32,
};

void delay_ms(u32 target)
{
    flag=0;
   while (flag<target);
}
int main(){
    //lcd_4bit_initialize(&lcd1);
    LED_init(&led1);
    LED_init(&led2);
    LED_init(&led3);
    timer0_Init(&tmr0_obj);
    while(1)
    {
        
    }
    return EXIT_SUCCESS;
}
void app_initialize()
{
    ecu_layer_initialize(); 
    
}
