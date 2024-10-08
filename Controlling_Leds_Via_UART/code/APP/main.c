#include <builtins.h>

#include "application.h"
#include "MCAL_Layer/interrupt/external_interrupt.h"
#include"MCAL_Layer/USART/usart.h"
#include"pic18f4620.h"
#include"ECU_Layer/LED/LED.h"
void app_initialize();

void uart_init()
{
    usart_t obj;
    obj.baudrate=9600;
    obj.baudrate_gen_gonfig=BAUDRATE_ASYN_8BIT_lOW_SPEED;
    
    obj.usart_rx_cfg.usart_rx_enable=EUSART_ASYNCHRONOUS_RX_ENABLE;
    obj.usart_rx_cfg.usart_rx_9bit_enable=EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
    obj.usart_rx_cfg.usart_rx_interrupt_enable=EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;

    obj.usart_tx_cfg.usart_tx_9bit_enable=EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    obj.usart_tx_cfg.usart_tx_enable=EUSART_ASYNCHRONOUS_TX_ENABLE;
    obj.usart_tx_cfg.usart_tx_interrupt_enable=EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;

    obj.EUSART_FramingErrorHandler=NULL;
    obj.EUSART_OverrunErrorHandler=NULL;
    obj.EUSART_RxDefaultInterruptHandler=NULL;
    obj.EUSART_TxDefaultInterruptHandler=NULL;
    Uart_Init(&obj);
}
u8 data ;
LED led1={.pin=PIN0_INDEX,.port=PORTD_INDEX,.status=LED_OFF};
LED led2={.pin=PIN1_INDEX,.port=PORTD_INDEX,.status=LED_OFF};
int main() {
    uart_init();
    LED_init(&led1);
    LED_init(&led2);
    while (1) {
//        Uart_WriteByteBlocking('a'); 
//        __delay_ms(250);
//        Uart_WriteByteBlocking('b');
//        __delay_ms(250);
//        Uart_WriteByteBlocking('c');
//        __delay_ms(250);

    Uart_ReadByteNonBlocking(&data);
     if(data=='a')
     {
         LED_on(&led1);
         Uart_WriteStringBlocking("Green LED ON\r");
      __delay_ms(250);
     }
     else if(data=='b')
     {
        LED_on(&led2); 
        Uart_WriteStringBlocking("RED LED ON\r");
       __delay_ms(250);
     }
     else 
     {
         LED_off(&led1);
         LED_off(&led2);
         Uart_WriteStringBlocking("ALL LEDs OFF\r");
       __delay_ms(250);
     }
    }
    return EXIT_SUCCESS;
}

void app_initialize() {
    ecu_layer_initialize();
    
}

