#include <pic18f4620.h>

#include"usart.h"

static void Uart_Baud_Rate_Calculation(const usart_t *_eusart);
static void Uart_ASYNC_TX_Init(const usart_t *_eusart);
static void Uart_ASYNC_RX_Init(const usart_t *_eusart);

Return_Status Uart_Init(usart_t* uart_obj)
{
    Return_Status ret=R_NOK;
    if(uart_obj!=NULL)
    {
        ret=R_OK;
        RCSTAbits.SPEN=EUSART_MODULE_DISABLE;
        TRISCbits.RC6=1;
        TRISCbits.RC7=1;
        Uart_Baud_Rate_Calculation(uart_obj);
        Uart_ASYNC_TX_Init(uart_obj);
        Uart_ASYNC_RX_Init(uart_obj);
        
        RCSTAbits.SPEN=EUSART_MODULE_ENABLE;
    }
   return ret;
}
Return_Status Uart_DeInit(usart_t* uart_obj)
{
    Return_Status ret=R_NOK;
    if(uart_obj!=NULL)
    {
        ret=R_OK;
        RCSTAbits.SPEN=EUSART_MODULE_DISABLE;
    }
   return ret;
}
Return_Status Uart_ReadByteBlocking(u8 *data)
{
    Return_Status ret=R_OK;
    while(!PIR1bits.RCIF);
    *data = RCREG;
   return ret;
}
Return_Status Uart_ReadByteNonBlocking(u8 *data)
{
    if(PIR1bits.RCIF)
    {
        *data = RCREG;
    }
    return R_OK;
}
Return_Status Uart_WriteByteBlocking(u8 data)
{
    Return_Status ret=R_OK;
        while(!(TXSTAbits.TRMT));
        TXREG=data;
   return ret;
}

Return_Status Uart_WriteStringBlocking(u8 *data)
{
    Return_Status ret = R_OK;
    while(*data)
    {
        while(!TXSTAbits.TRMT);  // Wait until TXREG is empty
        TXREG = *data++;          // Load character into TXREG and move to the next one
    }
    return ret;
}
static void Uart_Baud_Rate_Calculation(const usart_t *_eusart){
    float Baud_Rate_Temp = 0;
    switch(_eusart->baudrate_gen_gonfig){
        case BAUDRATE_ASYN_8BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 64) - 1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        default : ;
    }
    SPBRG = (u8)((u32)Baud_Rate_Temp);
    SPBRGH = (u8)(((u32)Baud_Rate_Temp) >> 8);
}
static void Uart_ASYNC_TX_Init(const usart_t *_eusart){
    if(EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
   //     EUSART_TxInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
        /* EUSART Transmit Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
            /* Interrupt Configurations */ 
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            EUSART_TX_InterruptEnable();
            /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_TX_HighPrioritySet();
            }
            else if(INTERRUPT_LOW_PRIORITY == _eusart->usart_tx_cfg.usart_tx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_TX_LowPrioritySet();
            }
            else{ /* Nothing */ }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        else{ /* Nothing */}

        /* EUSART  9-Bit Transmit Configuration */
        if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
        }
        else{ /* Nothing */}
    }
    else { /* Nothing */}
}

static void Uart_ASYNC_RX_Init(const usart_t *_eusart){
    if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
      //  EUSART_RxInterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
       // EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
        //EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
        /* EUSART Receiver Interrupt Configuration */
        if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
            /* Interrupt Configurations */ 
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            EUSART_RX_InterruptEnable();
            /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
            INTERRUPT_PriorityLevelsEnable();
            if(INTERRUPT_HIGH_PRIORITY == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all high-priority interrupts */
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_RX_HighPrioritySet();
            }
            else if(INTERRUPT_LOW_PRIORITY == _eusart->usart_rx_cfg.usart_rx_int_priority){
                /* Enables all unmasked peripheral interrupts */
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_RX_LowPrioritySet();
            }
            else{ /* Nothing */ }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        }
        else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        else{ /* Nothing */}

        /* EUSART  9-Bit Receiver Configuration */
        if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
        }
        else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
        }
        else{ /* Nothing */}
    }
    else { /* Nothing */}
}
