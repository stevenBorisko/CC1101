#include "CC1100.hpp"

void CC1100::spi_begin(void)
{
	int x = 0;
	//printf ("init SPI bus... ");
	if ((x = wiringPiSPISetup (0, 8000000)) < 0)  //4MHz SPI speed
	{
		if(debug_level > 0){
			printf ("ERROR: wiringPiSPISetup failed!\r\n");
		}
	}
	else{
		//printf ("wiringSPI is up\r\n");
	}
}

//----------------------------------------------------------------------------//
// --- Write --- //
//----------------------------------------------------------------------------//

void CC1100::spi_write_register(uint8_t spi_instr, uint8_t value)
{
	uint8_t tbuf[2] = {0};
	tbuf[0] = spi_instr | WRITE_SINGLE_BYTE;
	tbuf[1] = value;
	uint8_t len = 2;
	wiringPiSPIDataRW (0, tbuf, len) ;

	return;
}

void CC1100::spi_write_burst(uint8_t spi_instr, uint8_t *pArr, uint8_t len)
{
	uint8_t tbuf[len + 1];
	tbuf[0] = spi_instr | WRITE_BURST;
	for (uint8_t i=0; i<len ;i++ )
	{
		tbuf[i+1] = pArr[i];
		//printf("SPI_arr_write: 0x%02X\n", tbuf[i+1]);
	}
	wiringPiSPIDataRW (0, tbuf, len + 1) ;
}

void CC1100::spi_write_strobe(uint8_t spi_instr)
{
	uint8_t tbuf[1] = {0};
	tbuf[0] = spi_instr;
	//printf("SPI_data: 0x%02X\n", tbuf[0]);
	wiringPiSPIDataRW (0, tbuf, 1) ;
}

//----------------------------------------------------------------------------//
// --- Read --- //
//----------------------------------------------------------------------------//

uint8_t CC1100::spi_read_register(uint8_t spi_instr)
{
	uint8_t value;
	uint8_t rbuf[2] = {0};
	rbuf[0] = spi_instr | READ_SINGLE_BYTE;
	uint8_t len = 2;
	wiringPiSPIDataRW (0, rbuf, len) ;
	value = rbuf[1];
	//printf("SPI_arr_0: 0x%02X\n", rbuf[0]);
	//printf("SPI_arr_1: 0x%02X\n", rbuf[1]);
	return value;
}


void CC1100::spi_read_burst(uint8_t spi_instr, uint8_t *pArr, uint8_t len)
{
	uint8_t rbuf[len + 1];
	rbuf[0] = spi_instr | READ_BURST;
	wiringPiSPIDataRW (0, rbuf, len + 1) ;
	for (uint8_t i=0; i<len ;i++ )
	{
		pArr[i] = rbuf[i+1];
		//printf("SPI_arr_read: 0x%02X\n", pArr[i]);
	}
}
