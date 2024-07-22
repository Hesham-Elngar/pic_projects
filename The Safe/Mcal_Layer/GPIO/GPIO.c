#include"GPIO.h"
#include"../Device_config.h"
#include "gpio_private.h"

volatile u8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile u8 *LAT_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};
volatile u8 *PORT_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

#if PIN_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_set_pin_direction( pin_config_info *pin_config){
    Return_Status ret=R_NOK;
    if(pin_config!=NULL&&pin_config->pin<=PIN7_INDEX&&pin_config->port<=PORTE_INDEX){
        ret=R_OK;
        switch(pin_config->direction){
            case gpio_direction_output:
                CLR_BIT(*tris_registers[pin_config->port],pin_config->pin);
                break;
            case gpio_direction_input:
                SET_BIT(*tris_registers[pin_config->port],pin_config->pin);
                break;
            default : ret=R_NOK; break;    
        }
    }
    return ret;
}
#endif

#if PIN_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_get_pin_direction(pin_config_info *pin_config,direction_t *direction)
{
    Return_Status ret=R_NOK;
    if(pin_config!=NULL&&pin_config->pin<=PIN7_INDEX&&pin_config->port<=PORTE_INDEX){
        ret=R_OK;
        *direction=READ_BIT(*tris_registers[pin_config->port],pin_config->pin);
        
    }
    return ret;
}
#endif

#if PIN_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_write_pin_logic(pin_config_info* pin_config,logic_t logic){
    Return_Status ret=R_NOK;
    if(pin_config!=NULL&&pin_config->pin<=PIN7_INDEX&&pin_config->port<=PORTE_INDEX){
        ret=R_OK;
        switch(logic){
            case gpio_logic_low:
                CLR_BIT(*LAT_registers[pin_config->port],pin_config->pin);
                break;
            case gpio_logic_high:
                SET_BIT(*LAT_registers[pin_config->port],pin_config->pin);
                break;    
        }
    }
    return ret;
}
#endif


#if PIN_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_read_pin_logic(pin_config_info* pin_config,logic_t *logic){
    Return_Status ret=R_NOK;
    if(pin_config!=NULL&&NULL!=logic&&pin_config->pin<=PIN7_INDEX&&pin_config->port<=PORTE_INDEX){
        ret=R_OK;
        *logic=GET_BIT(*PORT_registers[pin_config->port],pin_config->pin);
    }
    return ret;
}
#endif


#if PIN_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_toggle_pin_value(pin_config_info *pin_config){
    Return_Status ret=R_NOK;
    if(pin_config!=NULL&&pin_config->pin<=PIN7_INDEX&&pin_config->port<=PORTE_INDEX){
        ret=R_OK;
        TOG_BIT(*LAT_registers[pin_config->port],pin_config->pin);
    }
    return ret;
}
#endif

#if PIN_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_pin_initialize(pin_config_info *pin_config)
{
    Return_Status ret=R_NOK;
    if(pin_config!=NULL&&pin_config->pin<=PIN7_INDEX&&pin_config->port<=PORTE_INDEX){
        ret=R_OK;
        gpio_set_pin_direction(pin_config);
        gpio_write_pin_logic(pin_config,pin_config->logic);
    }
    return ret;
}
#endif

#if PORT_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_set_port_direction(port_index_t port,direction_t direction)
{
    Return_Status ret=R_NOK;
    if(port<=PORTE_INDEX){
        ret=R_OK;
        *tris_registers[port]=direction;  
    }
    return ret;
}
#endif

#if PORT_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_get_port_direction(port_index_t port,u8 *direction)
{
    Return_Status ret=R_NOK;
    if(port<=PORTE_INDEX&&direction!=NULL)
    {
        ret=R_OK;
        *direction=*tris_registers[port];
    }
    return ret;
}
#endif

#if PORT_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_write_port_logic(port_index_t port,u8 logic){
    Return_Status ret=R_NOK;
    if(port<=PORTE_INDEX)
    {
        ret=R_OK;
        *LAT_registers[port]=logic ;
    }
    return ret;
}
#endif

#if PORT_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_read_port_logic(port_index_t port,u8 *logic){
     Return_Status ret=R_NOK;
    if(port<=PORTE_INDEX)
    {
        ret=R_OK;
        *logic=*LAT_registers[port];
    }
    return ret;
}
#endif

#if PORT_CONFIGURATIONS==CONFIG_ENABLE
Return_Status gpio_toggle_port_value(port_index_t port)
{
     Return_Status ret=R_NOK;
    if(port<=PORTE_INDEX)
    {
        ret=R_OK;
        *LAT_registers[port]^=0xFF;
    }
    return ret;
}
#endif

