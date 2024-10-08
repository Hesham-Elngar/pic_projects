#include"ssd_private.h"
#include "ssd_interface.h"


u8 seg_common_anode_values[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
u8 seg_common_cathode_values[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

Return_Status ssd_init(SSD *ssd){
	Return_Status ret=R_NOK;
	if(ssd){
		ret=R_OK;
		for(int i=0;i<4;i++){
			gpio_pin_initialize(&(ssd->SSD_Pins[i]));
		}
	}
	return ret;
}
Return_Status ssd_WriteNumber(SSD *ssd,u8 value)
{
	Return_Status ret=R_NOK;
	if(ssd&&value<=9){
		ret=R_OK;
		for (int i=0;i<4;++i)
		{
			gpio_write_pin_logic(&(ssd->SSD_Pins[i]),((value>>i)&0X01));
		}
	}
	return ret;
}