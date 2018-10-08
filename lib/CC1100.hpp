#ifndef CC1100_HPP
#define CC1100_HPP

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

//----------------------------------------------------------------------------//
// --- Macro Definitions --- //
//----------------------------------------------------------------------------//

#include "Macros.hpp"

//----------------------------------------------------------------------------//
// --- Class Declarations --- //
//----------------------------------------------------------------------------//

extern uint8_t cc1100_debug;

class CC1100
{
	private:

		//--------------------------------------//
		// --- SPI --- //
		//--------------------------------------//

		void spi_begin(void);

	public:

		// --- Write --- //

		void spi_write_register(uint8_t spi_instr, uint8_t value);
		// Write several registers at once
		void spi_write_burst(uint8_t spi_instr, uint8_t *pArr, uint8_t length);
		void spi_write_strobe(uint8_t spi_instr);

		// --- Read --- //

		uint8_t spi_read_register(uint8_t spi_instr);
		// Read several registers at once
		void spi_read_burst(uint8_t spi_instr, uint8_t *pArr, uint8_t length);

		//--------------------------------------//
		// --- Debug --- //
		//--------------------------------------//
		uint8_t debug_level;
		uint8_t set_debug_level(uint8_t set_debug_level);
		uint8_t get_debug_level(void);

		//--------------------------------------//
		// --- Control --- //
		//--------------------------------------//

		// --- Init --- //

		uint8_t begin(volatile uint8_t &My_addr);

		// --- Operation --- //
		void end(void);
		void reset(void);
		void wakeup(void);
		void powerdown(void);

		//  --- Modes --- //
		uint8_t sidle(void);
		uint8_t transmit(void);
		uint8_t receive(void);

		//--------------------------------------//
		// --- WOR --- //
		//--------------------------------------//

		// enables WOR Mode  EVENT0 ~1890ms; rx_timeout ~235ms
		void wor_enable(void);
		// disable WOR Mode
		void wor_disable(void);
		// reset WOR timer
		void wor_reset(void);

		//--------------------------------------//
		// --- Settings --- //
		//--------------------------------------//

		// Show all CC1100 registers
		void show_register_settings(void);
		// Show settings
		void show_main_settings(void);

		//--------------------------------------//
		// --- Packets --- //
		//--------------------------------------//

		// --- Packets --- //

		// Check if packet is received
		uint8_t packet_available();
		// Check if Packet is received within defined time in ms
		uint8_t wait_for_packet(uint8_t milliseconds);
		uint8_t sent_packet(uint8_t my_addr, uint8_t rx_addr, uint8_t *txbuffer, uint8_t pktlen, uint8_t tx_retries);
		void sent_acknolage(uint8_t my_addr, uint8_t tx_addr);

		uint8_t check_acknolage(uint8_t *rxbuffer, uint8_t pktlen, uint8_t sender, uint8_t my_addr);

		// --- Payload --- //

		// check Payload for ACK or Data
		uint8_t get_payload(uint8_t rxbuffer[], uint8_t &pktlen_rx,uint8_t &my_addr,
				uint8_t &sender, int8_t &rssi_dbm, uint8_t &lqi);

		uint8_t tx_payload_burst(uint8_t my_addr, uint8_t rx_addr, uint8_t *txbuffer, uint8_t length);
		// package received
		uint8_t rx_payload_burst(uint8_t rxbuffer[], uint8_t &pktlen);

		// --- Buffers --- //

		void rx_fifo_erase(uint8_t *rxbuffer);
		void tx_fifo_erase(uint8_t *txbuffer);


		//--------------------------------------//
		// --- Miscellaneous --- //
		//--------------------------------------//

		int8_t rssi_convert(uint8_t Rssi);
		uint8_t check_crc(uint8_t lqi);
		uint8_t lqi_convert(uint8_t lqi);
		uint8_t get_temp(uint8_t *ptemp_Arr);

		//--------------------------------------//
		// --- Setters --- //
		//--------------------------------------//

		void set_myaddr(uint8_t addr);
		void set_channel(uint8_t channel);
		// [set ISM Band 1=315MHz; 2=433MHz; 3=868MHz; 4=915MHz]
		void set_ISM(uint8_t ism_freq);
		// set modulation mode 1 = GFSK_1_2_kb; 2 = GFSK_38_4_kb; 3 = GFSK_100_kb; 4 = MSK_250_kb; 5 = MSK_500_kb; 6 = OOK_4_8_kb
		void set_mode(uint8_t mode);
		void set_output_power_level(int8_t dbm);
		// set frequency
		void set_patable(uint8_t *patable_arr);
		// ON-TRUE OFF-FALSE
		void set_fec(uint8_t cfg);
		// ON-TRUE OFF-FALSE
		void set_data_whitening(uint8_t cfg);
		// set Modulation type 2-FSK=0; GFSK=1; ASK/OOK=3; 4-FSK=4; MSK=7
		void set_modulation_type(uint8_t cfg);
		void set_preamble_len(uint8_t cfg);
		// ON-TRUE OFF-FALSE
		void set_manchaster_encoding(uint8_t cfg);
		// no sync-0
		void set_sync_mode(uint8_t cfg);
		// set modem datarate and deviant
		void set_datarate(uint8_t mdmcfg4, uint8_t mdmcfg3, uint8_t deviant);
};

//----------------------------------------------------------------------------//
// --- Static Array Initializations --- //
//----------------------------------------------------------------------------//

//-------------------[global default settings 868 Mhz]--------------------------
static uint8_t cc1100_GFSK_1_2_kb[CFG_REGISTER] = {
	0x07,  // IOCFG2        GDO2 Output Pin Configuration
	0x2E,  // IOCFG1        GDO1 Output Pin Configuration
	0x80,  // IOCFG0        GDO0 Output Pin Configuration
	0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	0x57,  // SYNC1         Sync Word, High Byte
	0x43,  // SYNC0         Sync Word, Low Byte
	0x3E,  // PKTLEN        Packet Length
	0x0E,  // PKTCTRL1      Packet Automation Control
	0x45,  // PKTCTRL0      Packet Automation Control
	0xFF,  // ADDR          Device Address
	0x00,  // CHANNR        Channel Number
	0x08,  // FSCTRL1       Frequency Synthesizer Control
	0x00,  // FSCTRL0       Frequency Synthesizer Control
	0x21,  // FREQ2         Frequency Control Word, High Byte
	0x65,  // FREQ1         Frequency Control Word, Middle Byte
	0x6A,  // FREQ0         Frequency Control Word, Low Byte
	0xF5,  // MDMCFG4       Modem Configuration
	0x83,  // MDMCFG3       Modem Configuration
	0x13,  // MDMCFG2       Modem Configuration
	0xA0,  // MDMCFG1       Modem Configuration
	0xF8,  // MDMCFG0       Modem Configuration
	0x15,  // DEVIATN       Modem Deviation Setting
	0x07,  // MCSM2         Main Radio Control State Machine Configuration
	0x0C,  // MCSM1         Main Radio Control State Machine Configuration
	0x18,  // MCSM0         Main Radio Control State Machine Configuration
	0x16,  // FOCCFG        Frequency Offset Compensation Configuration
	0x6C,  // BSCFG         Bit Synchronization Configuration
	0x03,  // AGCCTRL2      AGC Control
	0x40,  // AGCCTRL1      AGC Control
	0x91,  // AGCCTRL0      AGC Control
	0x02,  // WOREVT1       High Byte Event0 Timeout
	0x26,  // WOREVT0       Low Byte Event0 Timeout
	0x09,  // WORCTRL       Wake On Radio Control
	0x56,  // FREND1        Front End RX Configuration
	0x17,  // FREND0        Front End TX Configuration
	0xA9,  // FSCAL3        Frequency Synthesizer Calibration
	0x0A,  // FSCAL2        Frequency Synthesizer Calibration
	0x00,  // FSCAL1        Frequency Synthesizer Calibration
	0x11,  // FSCAL0        Frequency Synthesizer Calibration
	0x41,  // RCCTRL1       RC Oscillator Configuration
	0x00,  // RCCTRL0       RC Oscillator Configuration
	0x59,  // FSTEST        Frequency Synthesizer Calibration Control,
	0x7F,  // PTEST         Production Test
	0x3F,  // AGCTEST       AGC Test
	0x81,  // TEST2         Various Test Settings
	0x3F,  // TEST1         Various Test Settings
	0x0B   // TEST0         Various Test Settings
};

static uint8_t cc1100_GFSK_38_4_kb[CFG_REGISTER] = {
	0x07,  // IOCFG2        GDO2 Output Pin Configuration
	0x2E,  // IOCFG1        GDO1 Output Pin Configuration
	0x80,  // IOCFG0        GDO0 Output Pin Configuration
	0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	0x57,  // SYNC1         Sync Word, High Byte
	0x43,  // SYNC0         Sync Word, Low Byte
	0x3E,  // PKTLEN        Packet Length
	0x0E,  // PKTCTRL1      Packet Automation Control
	0x45,  // PKTCTRL0      Packet Automation Control
	0xFF,  // ADDR          Device Address
	0x00,  // CHANNR        Channel Number
	0x06,  // FSCTRL1       Frequency Synthesizer Control
	0x00,  // FSCTRL0       Frequency Synthesizer Control
	0x21,  // FREQ2         Frequency Control Word, High Byte
	0x65,  // FREQ1         Frequency Control Word, Middle Byte
	0x6A,  // FREQ0         Frequency Control Word, Low Byte
	0xCA,  // MDMCFG4       Modem Configuration
	0x83,  // MDMCFG3       Modem Configuration
	0x13,  // MDMCFG2       Modem Configuration
	0xA0,  // MDMCFG1       Modem Configuration
	0xF8,  // MDMCFG0       Modem Configuration
	0x34,  // DEVIATN       Modem Deviation Setting
	0x07,  // MCSM2         Main Radio Control State Machine Configuration
	0x0C,  // MCSM1         Main Radio Control State Machine Configuration
	0x18,  // MCSM0         Main Radio Control State Machine Configuration
	0x16,  // FOCCFG        Frequency Offset Compensation Configuration
	0x6C,  // BSCFG         Bit Synchronization Configuration
	0x43,  // AGCCTRL2      AGC Control
	0x40,  // AGCCTRL1      AGC Control
	0x91,  // AGCCTRL0      AGC Control
	0x02,  // WOREVT1       High Byte Event0 Timeout
	0x26,  // WOREVT0       Low Byte Event0 Timeout
	0x09,  // WORCTRL       Wake On Radio Control
	0x56,  // FREND1        Front End RX Configuration
	0x17,  // FREND0        Front End TX Configuration
	0xA9,  // FSCAL3        Frequency Synthesizer Calibration
	0x0A,  // FSCAL2        Frequency Synthesizer Calibration
	0x00,  // FSCAL1        Frequency Synthesizer Calibration
	0x11,  // FSCAL0        Frequency Synthesizer Calibration
	0x41,  // RCCTRL1       RC Oscillator Configuration
	0x00,  // RCCTRL0       RC Oscillator Configuration
	0x59,  // FSTEST        Frequency Synthesizer Calibration Control,
	0x7F,  // PTEST         Production Test
	0x3F,  // AGCTEST       AGC Test
	0x81,  // TEST2         Various Test Settings
	0x3F,  // TEST1         Various Test Settings
	0x0B   // TEST0         Various Test Settings
};

static uint8_t cc1100_GFSK_100_kb[CFG_REGISTER] = {
	0x07,  // IOCFG2        GDO2 Output Pin Configuration
	0x2E,  // IOCFG1        GDO1 Output Pin Configuration
	0x80,  // IOCFG0        GDO0 Output Pin Configuration
	0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	0x57,  // SYNC1         Sync Word, High Byte
	0x43,  // SYNC0         Sync Word, Low Byte
	0x3E,  // PKTLEN        Packet Length
	0x0E,  // PKTCTRL1      Packet Automation Control
	0x45,  // PKTCTRL0      Packet Automation Control
	0xFF,  // ADDR          Device Address
	0x00,  // CHANNR        Channel Number
	0x08,  // FSCTRL1       Frequency Synthesizer Control
	0x00,  // FSCTRL0       Frequency Synthesizer Control
	0x21,  // FREQ2         Frequency Control Word, High Byte
	0x65,  // FREQ1         Frequency Control Word, Middle Byte
	0x6A,  // FREQ0         Frequency Control Word, Low Byte
	0x5B,  // MDMCFG4       Modem Configuration
	0xF8,  // MDMCFG3       Modem Configuration
	0x13,  // MDMCFG2       Modem Configuration
	0xA0,  // MDMCFG1       Modem Configuration
	0xF8,  // MDMCFG0       Modem Configuration
	0x47,  // DEVIATN       Modem Deviation Setting
	0x07,  // MCSM2         Main Radio Control State Machine Configuration
	0x0C,  // MCSM1         Main Radio Control State Machine Configuration
	0x18,  // MCSM0         Main Radio Control State Machine Configuration
	0x1D,  // FOCCFG        Frequency Offset Compensation Configuration
	0x1C,  // BSCFG         Bit Synchronization Configuration
	0xC7,  // AGCCTRL2      AGC Control
	0x00,  // AGCCTRL1      AGC Control
	0xB2,  // AGCCTRL0      AGC Control
	0x02,  // WOREVT1       High Byte Event0 Timeout
	0x26,  // WOREVT0       Low Byte Event0 Timeout
	0x09,  // WORCTRL       Wake On Radio Control
	0xB6,  // FREND1        Front End RX Configuration
	0x17,  // FREND0        Front End TX Configuration
	0xEA,  // FSCAL3        Frequency Synthesizer Calibration
	0x0A,  // FSCAL2        Frequency Synthesizer Calibration
	0x00,  // FSCAL1        Frequency Synthesizer Calibration
	0x11,  // FSCAL0        Frequency Synthesizer Calibration
	0x41,  // RCCTRL1       RC Oscillator Configuration
	0x00,  // RCCTRL0       RC Oscillator Configuration
	0x59,  // FSTEST        Frequency Synthesizer Calibration Control,
	0x7F,  // PTEST         Production Test
	0x3F,  // AGCTEST       AGC Test
	0x81,  // TEST2         Various Test Settings
	0x3F,  // TEST1         Various Test Settings
	0x0B   // TEST0         Various Test Settings
};

static uint8_t cc1100_MSK_250_kb[CFG_REGISTER] = {
	0x07,  // IOCFG2        GDO2 Output Pin Configuration
	0x2E,  // IOCFG1        GDO1 Output Pin Configuration
	0x80,  // IOCFG0        GDO0 Output Pin Configuration
	0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	0x57,  // SYNC1         Sync Word, High Byte
	0x43,  // SYNC0         Sync Word, Low Byte
	0x3E,  // PKTLEN        Packet Length
	0x0E,  // PKTCTRL1      Packet Automation Control
	0x45,  // PKTCTRL0      Packet Automation Control
	0xFF,  // ADDR          Device Address
	0x00,  // CHANNR        Channel Number
	0x0B,  // FSCTRL1       Frequency Synthesizer Control
	0x00,  // FSCTRL0       Frequency Synthesizer Control
	0x21,  // FREQ2         Frequency Control Word, High Byte
	0x65,  // FREQ1         Frequency Control Word, Middle Byte
	0x6A,  // FREQ0         Frequency Control Word, Low Byte
	0x2D,  // MDMCFG4       Modem Configuration
	0x3B,  // MDMCFG3       Modem Configuration
	0x73,  // MDMCFG2       Modem Configuration
	0xA0,  // MDMCFG1       Modem Configuration
	0xF8,  // MDMCFG0       Modem Configuration
	0x00,  // DEVIATN       Modem Deviation Setting
	0x07,  // MCSM2         Main Radio Control State Machine Configuration
	0x0C,  // MCSM1         Main Radio Control State Machine Configuration
	0x18,  // MCSM0         Main Radio Control State Machine Configuration
	0x1D,  // FOCCFG        Frequency Offset Compensation Configuration
	0x1C,  // BSCFG         Bit Synchronization Configuration
	0xC7,  // AGCCTRL2      AGC Control
	0x00,  // AGCCTRL1      AGC Control
	0xB2,  // AGCCTRL0      AGC Control
	0x02,  // WOREVT1       High Byte Event0 Timeout
	0x26,  // WOREVT0       Low Byte Event0 Timeout
	0x09,  // WORCTRL       Wake On Radio Control
	0xB6,  // FREND1        Front End RX Configuration
	0x17,  // FREND0        Front End TX Configuration
	0xEA,  // FSCAL3        Frequency Synthesizer Calibration
	0x0A,  // FSCAL2        Frequency Synthesizer Calibration
	0x00,  // FSCAL1        Frequency Synthesizer Calibration
	0x11,  // FSCAL0        Frequency Synthesizer Calibration
	0x41,  // RCCTRL1       RC Oscillator Configuration
	0x00,  // RCCTRL0       RC Oscillator Configuration
	0x59,  // FSTEST        Frequency Synthesizer Calibration Control,
	0x7F,  // PTEST         Production Test
	0x3F,  // AGCTEST       AGC Test
	0x81,  // TEST2         Various Test Settings
	0x3F,  // TEST1         Various Test Settings
	0x0B   // TEST0         Various Test Settings
};

static uint8_t cc1100_MSK_500_kb[CFG_REGISTER] = {
	0x07,  // IOCFG2        GDO2 Output Pin Configuration
	0x2E,  // IOCFG1        GDO1 Output Pin Configuration
	0x80,  // IOCFG0        GDO0 Output Pin Configuration
	0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	0x57,  // SYNC1         Sync Word, High Byte
	0x43,  // SYNC0         Sync Word, Low Byte
	0x3E,  // PKTLEN        Packet Length
	0x0E,  // PKTCTRL1      Packet Automation Control
	0x45,  // PKTCTRL0      Packet Automation Control
	0xFF,  // ADDR          Device Address
	0x00,  // CHANNR        Channel Number
	0x0C,  // FSCTRL1       Frequency Synthesizer Control
	0x00,  // FSCTRL0       Frequency Synthesizer Control
	0x21,  // FREQ2         Frequency Control Word, High Byte
	0x65,  // FREQ1         Frequency Control Word, Middle Byte
	0x6A,  // FREQ0         Frequency Control Word, Low Byte
	0x0E,  // MDMCFG4       Modem Configuration
	0x3B,  // MDMCFG3       Modem Configuration
	0x73,  // MDMCFG2       Modem Configuration
	0xA0,  // MDMCFG1       Modem Configuration
	0xF8,  // MDMCFG0       Modem Configuration
	0x00,  // DEVIATN       Modem Deviation Setting
	0x07,  // MCSM2         Main Radio Control State Machine Configuration
	0x0C,  // MCSM1         Main Radio Control State Machine Configuration
	0x18,  // MCSM0         Main Radio Control State Machine Configuration
	0x1D,  // FOCCFG        Frequency Offset Compensation Configuration
	0x1C,  // BSCFG         Bit Synchronization Configuration
	0xC7,  // AGCCTRL2      AGC Control
	0x40,  // AGCCTRL1      AGC Control
	0xB2,  // AGCCTRL0      AGC Control
	0x02,  // WOREVT1       High Byte Event0 Timeout
	0x26,  // WOREVT0       Low Byte Event0 Timeout
	0x09,  // WORCTRL       Wake On Radio Control
	0xB6,  // FREND1        Front End RX Configuration
	0x17,  // FREND0        Front End TX Configuration
	0xEA,  // FSCAL3        Frequency Synthesizer Calibration
	0x0A,  // FSCAL2        Frequency Synthesizer Calibration
	0x00,  // FSCAL1        Frequency Synthesizer Calibration
	0x19,  // FSCAL0        Frequency Synthesizer Calibration
	0x41,  // RCCTRL1       RC Oscillator Configuration
	0x00,  // RCCTRL0       RC Oscillator Configuration
	0x59,  // FSTEST        Frequency Synthesizer Calibration Control,
	0x7F,  // PTEST         Production Test
	0x3F,  // AGCTEST       AGC Test
	0x81,  // TEST2         Various Test Settings
	0x3F,  // TEST1         Various Test Settings
	0x0B   // TEST0         Various Test Settings
};

static uint8_t cc1100_OOK_4_8_kb[CFG_REGISTER] = {
	0x06,  // IOCFG2        GDO2 Output Pin Configuration
	0x2E,  // IOCFG1        GDO1 Output Pin Configuration
	0x06,  // IOCFG0        GDO0 Output Pin Configuration
	0x47,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	0x57,  // SYNC1         Sync Word, High Byte
	0x43,  // SYNC0         Sync Word, Low Byte
	0xFF,  // PKTLEN        Packet Length
	0x04,  // PKTCTRL1      Packet Automation Control
	0x05,  // PKTCTRL0      Packet Automation Control
	0x00,  // ADDR          Device Address
	0x00,  // CHANNR        Channel Number
	0x06,  // FSCTRL1       Frequency Synthesizer Control
	0x00,  // FSCTRL0       Frequency Synthesizer Control
	0x21,  // FREQ2         Frequency Control Word, High Byte
	0x65,  // FREQ1         Frequency Control Word, Middle Byte
	0x6A,  // FREQ0         Frequency Control Word, Low Byte
	0x87,  // MDMCFG4       Modem Configuration
	0x83,  // MDMCFG3       Modem Configuration
	0x3B,  // MDMCFG2       Modem Configuration
	0x22,  // MDMCFG1       Modem Configuration
	0xF8,  // MDMCFG0       Modem Configuration
	0x15,  // DEVIATN       Modem Deviation Setting
	0x07,  // MCSM2         Main Radio Control State Machine Configuration
	0x30,  // MCSM1         Main Radio Control State Machine Configuration
	0x18,  // MCSM0         Main Radio Control State Machine Configuration
	0x14,  // FOCCFG        Frequency Offset Compensation Configuration
	0x6C,  // BSCFG         Bit Synchronization Configuration
	0x07,  // AGCCTRL2      AGC Control
	0x00,  // AGCCTRL1      AGC Control
	0x92,  // AGCCTRL0      AGC Control
	0x87,  // WOREVT1       High Byte Event0 Timeout
	0x6B,  // WOREVT0       Low Byte Event0 Timeout
	0xFB,  // WORCTRL       Wake On Radio Control
	0x56,  // FREND1        Front End RX Configuration
	0x17,  // FREND0        Front End TX Configuration
	0xE9,  // FSCAL3        Frequency Synthesizer Calibration
	0x2A,  // FSCAL2        Frequency Synthesizer Calibration
	0x00,  // FSCAL1        Frequency Synthesizer Calibration
	0x1F,  // FSCAL0        Frequency Synthesizer Calibration
	0x41,  // RCCTRL1       RC Oscillator Configuration
	0x00,  // RCCTRL0       RC Oscillator Configuration
	0x59,  // FSTEST        Frequency Synthesizer Calibration Control
	0x7F,  // PTEST         Production Test
	0x3F,  // AGCTEST       AGC Test
	0x81,  // TEST2         Various Test Settings
	0x35,  // TEST1         Various Test Settings
	0x09,  // TEST0         Various Test Settings
};

//Patable index: -30  -20- -15  -10   0    5    7    10 dBm
static uint8_t patable_power_315[8] = {0x17,0x1D,0x26,0x69,0x51,0x86,0xCC,0xC3};
static uint8_t patable_power_433[8] = {0x6C,0x1C,0x06,0x3A,0x51,0x85,0xC8,0xC0};
static uint8_t patable_power_868[8] = {0x03,0x17,0x1D,0x26,0x50,0x86,0xCD,0xC0};
static uint8_t patable_power_915[8] = {0x0B,0x1B,0x6D,0x67,0x50,0x85,0xC9,0xC1};
//static uint8_t patable_power_2430[8] = {0x44,0x84,0x46,0x55,0xC6,0x6E,0x9A,0xFE};

#endif
