#include"eeprom.h"

Return_Status EEPROM_WriteByte(u16 address,u8 data){
    Return_Status ret=R_OK;
    EEADRH =(u8)((address>>8) & 0x03);
    EEADR = (u8) (address & 0xFF);
    EEDATA=data;
    EECON1bits.EEPGD=0;
    EECON1bits.CFGS=0;
    EECON1bits.WREN=1;
    u8 int_state=INTCONbits.GIE;
    INTERRUPT_GLOBAL_DISABLE();    
    EECON2=0x55;
    EECON2=0xAA;
    EECON1bits.WR=1;
    while(EECON1bits.WR);
    EECON1bits.WREN=0;
    INTCONbits.GIE=int_state;
    return ret;   
}
Return_Status EEPROM_ReadByte(u16 address,u8 *data){
    Return_Status ret=R_NOK;
    if(data){
    Return_Status ret=R_OK;
    EEADRH=(u8)(address>>8)&0x03;
    EEADR=(u8)(address&0xFF);
    u8 interrupt_status=INTCONbits.GIE;
    EECON1bits.EEPGD=0;
    EECON1bits.CFGS=0;
    INTERRUPT_GLOBAL_DISABLE();
    EECON2=0x55;
    EECON2=0xff;
    EECON1bits.RD=1;
    while(EECON1bits.RD);
    *data=EEDATA;
    INTCONbits.GIE=interrupt_status;
    }
    return ret;
}
