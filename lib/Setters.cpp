#include "CC1100.hpp"

void CC1100::set_myaddr(uint8_t addr)
{
	spi_write_register(ADDR,addr);          //stores MyAddr in the CC1100
}

void CC1100::set_channel(uint8_t channel)
{
	spi_write_register(CHANNR,channel);   //stores the new channel # in the CC1100

	return;
}

void CC1100::set_ISM(uint8_t ism_freq)
{
	uint8_t freq2, freq1, freq0;

	switch (ism_freq)                                                       //loads the RF freq which is defined in cc1100_freq_select
	{
		case 0x01:                                                          //315MHz
			freq2=0x0C;
			freq1=0x1D;
			freq0=0x89;
			spi_write_burst(PATABLE_BURST,patable_power_315,8);
			break;
		case 0x02:                                                          //433.92MHz
			freq2=0x10;
			freq1=0xB0;
			freq0=0x71;
			spi_write_burst(PATABLE_BURST,patable_power_433,8);
			break;
		case 0x03:                                                          //868.3MHz
			freq2=0x21;
			freq1=0x65;
			freq0=0x6A;
			spi_write_burst(PATABLE_BURST,patable_power_868,8);
			break;
		case 0x04:                                                          //915MHz
			freq2=0x23;
			freq1=0x31;
			freq0=0x3B;
			spi_write_burst(PATABLE_BURST,patable_power_915,8);
			break;
			/*
			   case 0x05:                                                          //2430MHz
			   freq2=0x5D;
			   freq1=0x76;
			   freq0=0x27;
			   spi_write_burst(PATABLE_BURST,patable_power_2430,8);
			   break;
			 */
		default:                                                             //default is 868.3MHz
			freq2=0x21;
			freq1=0x65;
			freq0=0x6A;
			spi_write_burst(PATABLE_BURST,patable_power_868,8);    //sets up output power ramp register
			break;
	}

	spi_write_register(FREQ2,freq2);                                         //stores the new freq setting for defined ISM band
	spi_write_register(FREQ1,freq1);
	spi_write_register(FREQ0,freq0);

	return;
}

void CC1100::set_mode(uint8_t mode)
{

	switch (mode)
	{
		case 0x01:
			spi_write_burst(WRITE_BURST,cc1100_GFSK_1_2_kb,CFG_REGISTER);
			break;
		case 0x02:
			spi_write_burst(WRITE_BURST,cc1100_GFSK_38_4_kb,CFG_REGISTER);
			break;
		case 0x03:
			spi_write_burst(WRITE_BURST,cc1100_GFSK_100_kb,CFG_REGISTER);
			break;
		case 0x04:
			spi_write_burst(WRITE_BURST,cc1100_MSK_250_kb,CFG_REGISTER);
			break;
		case 0x05:
			spi_write_burst(WRITE_BURST,cc1100_MSK_500_kb,CFG_REGISTER);
			break;
		case 0x06:
			spi_write_burst(WRITE_BURST,cc1100_OOK_4_8_kb,CFG_REGISTER);
			break;
		default:
			spi_write_burst(WRITE_BURST,cc1100_GFSK_100_kb,CFG_REGISTER);
			break;
	}
	return;
}

void CC1100::set_output_power_level(int8_t dBm)
{
	uint8_t pa = 0xC0;

	if      (dBm <= -30) pa = 0x00;
	else if (dBm <= -20) pa = 0x01;
	else if (dBm <= -15) pa = 0x02;
	else if (dBm <= -10) pa = 0x03;
	else if (dBm <= 0)   pa = 0x04;
	else if (dBm <= 5)   pa = 0x05;
	else if (dBm <= 7)   pa = 0x06;
	else if (dBm <= 10)  pa = 0x07;

	spi_write_register(FREND0,pa);
}

void CC1100::set_patable(uint8_t *patable_arr)
{
	spi_write_burst(PATABLE_BURST,patable_arr,8);   //writes output power settings to cc1100    "104us"
}

void CC1100::set_fec(uint8_t cfg)
{
	uint8_t data;
	data = spi_read_register(MDMCFG1);
	data = (data & 0x7F) | (((cfg) << 7) & 0x80);
	spi_write_register(MDMCFG1, data);
	fprintf(stderr,"MDMCFG1: 0x%02X\n", data);
}

void CC1100::set_data_whitening(uint8_t cfg)
{
	uint8_t data;
	data = spi_read_register(PKTCTRL0);
	data = (data & 0xBF) | (((cfg) << 6) & 0x40);
	spi_write_register(PKTCTRL0, data);
	//fprintf(stderr,"PKTCTRL0: 0x%02X\n", data);
}

void CC1100::set_modulation_type(uint8_t cfg)
{
	uint8_t data;
	data = spi_read_register(MDMCFG2);
	data = (data & 0x8F) | (((cfg) << 4) & 0x70);
	spi_write_register(MDMCFG2, data);
	//fprintf(stderr,"MDMCFG2: 0x%02X\n", data);
}

void CC1100::set_preamble_len(uint8_t cfg)
{
	uint8_t data;
	data = spi_read_register(MDMCFG1);
	data = (data & 0x8F) | (((cfg) << 4) & 0x70);
	spi_write_register(MDMCFG1, data);
	//fprintf(stderr,"MDMCFG2: 0x%02X\n", data);
}

void CC1100::set_manchaster_encoding(uint8_t cfg)
{
	uint8_t data;
	data = spi_read_register(MDMCFG2);
	data = (data & 0xF7) | (((cfg) << 3) & 0x08);
	spi_write_register(MDMCFG2, data);
	//fprintf(stderr,"MDMCFG2: 0x%02X\n", data);
}

void CC1100::set_sync_mode(uint8_t cfg) // 0=no sync word; 1,2 = 16bit sync word, 3= 32bit sync word
{
	uint8_t data;
	data = spi_read_register(MDMCFG2);
	data = (data & 0xF8) | (cfg & 0x07);
	spi_write_register(MDMCFG2, data);
	//fprintf(stderr,"MDMCFG2: 0x%02X\n", data);
}

void CC1100::set_datarate(uint8_t mdmcfg4, uint8_t mdmcfg3, uint8_t deviant)
{
	spi_write_register(MDMCFG4, mdmcfg4);
	spi_write_register(MDMCFG3, mdmcfg3);
	spi_write_register(DEVIATN, deviant);
}
