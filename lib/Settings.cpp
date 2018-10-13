#include "CC1100.hpp"

void CC1100::show_register_settings(void)
{
	if(debug_level > 0){
		uint8_t config_reg_verify[CFG_REGISTER],Patable_verify[CFG_REGISTER];

		spi_read_burst(READ_BURST,config_reg_verify,CFG_REGISTER);  //reads all 47 config register from cc1100
		spi_read_burst(PATABLE_BURST,Patable_verify,8);             //reads output power settings from cc1100

		//show_main_settings();
		fprintf(stderr,"Config Register:\r\n");

		for(uint8_t i = 0 ; i < CFG_REGISTER; i++)  //showes rx_buffer for debug
		{
			fprintf(stderr,"0x%02X ", config_reg_verify[i]);
			if(i==9 || i==19 || i==29 || i==39) //just for beautiful output style
			{
				fprintf(stderr,"\r\n");
			}
		}
		fprintf(stderr,"\r\n");
		fprintf(stderr,"PaTable:\r\n");

		for(uint8_t i = 0 ; i < 8; i++)         //showes rx_buffer for debug
		{
			fprintf(stderr,"0x%02X ", Patable_verify[i]);
		}
		fprintf(stderr,"\r\n");
	}
}

void CC1100::show_main_settings(void)
{
	extern volatile uint8_t My_addr;
	extern int cc1100_mode_select, cc1100_freq_select, cc1100_channel_select;

	fprintf(stderr,"Mode: %d\r\n", cc1100_mode_select);
	fprintf(stderr,"Frequency: %d\r\n", cc1100_freq_select);
	fprintf(stderr,"Channel: %d\r\n", cc1100_channel_select);
	fprintf(stderr,"My_Addr: %d\r\n", My_addr);
}
