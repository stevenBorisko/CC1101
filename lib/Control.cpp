#include "CC1100.hpp"

//----------------------------------------------------------------------------//
// --- Init --- //
//----------------------------------------------------------------------------//

uint8_t CC1100::begin(volatile uint8_t &My_addr)
{
    uint8_t partnum, version;
    extern int cc1100_freq_select, cc1100_mode_select, cc1100_channel_select;

    pinMode(GDO0, INPUT);                 //setup AVR GPIO ports
    pinMode(GDO2, INPUT);

    set_debug_level(1);   //set debug level of CC1101 outputs

    if(debug_level > 0){
          printf("Init CC1100...\r\n");
    }

    spi_begin();                          //inits SPI Interface
    reset();                              //CC1100 init reset

    spi_write_strobe(SFTX);delayMicroseconds(100);//flush the TX_fifo content
    spi_write_strobe(SFRX);delayMicroseconds(100);//flush the RX_fifo content

    partnum = spi_read_register(PARTNUM); //reads CC1100 partnumber
    version = spi_read_register(VERSION); //reads CC1100 version number

    //checks if valid Chip ID is found. Usualy 0x03 or 0x14. if not -> abort
    if(version == 0x00 || version == 0xFF){
        if(debug_level > 0){
            printf("no CC11xx found!\r\n");
        }
        end();                        //CC1100 Powerdown and disable SPI bus
        return FALSE;
    }

    if(debug_level > 0){
          printf("Partnumber: 0x%02X\r\n", partnum);
          printf("Version   : 0x%02X\r\n", version);
    }




    //set modulation mode
    set_mode(cc1100_mode_select);

    //set ISM band
    set_ISM(cc1100_freq_select);

    //set channel
    set_channel(cc1100_channel_select);

    //set output power amplifier
    set_output_power_level(0);            //set PA to 0dBm as default

    //set my receiver address
    set_myaddr(My_addr);                  //My_Addr from EEPROM to global variable

    if(debug_level > 0){
          printf("...done!\r\n");
    }

    receive();                                  //set CC1100 in receive mode

    return TRUE;
}

//----------------------------------------------------------------------------//
// --- Operation --- //
//----------------------------------------------------------------------------//

void CC1100::end(void)
{
    powerdown();                          //power down CC1100
}

void CC1100::reset(void)                  // reset defined in cc1100 datasheet
{
    digitalWrite(SS_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(SS_PIN, HIGH);
    delayMicroseconds(40);

    spi_write_strobe(SRES);
    delay(1);
}

void CC1100::powerdown(void)
{
    sidle();
    spi_write_strobe(SPWD);               // CC1100 Power Down
}

void CC1100::wakeup(void)
{
    digitalWrite(SS_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(SS_PIN, HIGH);
    delayMicroseconds(10);
    receive();                            // go to RX Mode
}


//----------------------------------------------------------------------------//
// --- Modes --- //
//----------------------------------------------------------------------------//

uint8_t CC1100::sidle(void)
{
    uint8_t marcstate;

    spi_write_strobe(SIDLE);              //sets to idle first. must be in

    marcstate = 0xFF;                     //set unknown/dummy state value

    while(marcstate != 0x01)              //0x01 = sidle
    {
        marcstate = (spi_read_register(MARCSTATE) & 0x1F); //read out state of cc1100 to be sure in RX
        //printf("marcstate_rx: 0x%02X\r", marcstate);
    }
    //Serial.println();
    delayMicroseconds(100);
    return TRUE;
}

uint8_t CC1100::transmit(void)
{
    uint8_t marcstate;

    sidle();                              //sets to idle first.
    spi_write_strobe(STX);                //sends the data over air

    marcstate = 0xFF;                     //set unknown/dummy state value

    while(marcstate != 0x01)              //0x01 = ILDE after sending data
    {
        marcstate = (spi_read_register(MARCSTATE) & 0x1F); //read out state of cc1100 to be sure in IDLE and TX is finished
        //printf("marcstate_tx: 0x%02X ",marcstate);
    }
    //printf("\r\n");
    delayMicroseconds(100);
    return TRUE;
}

uint8_t CC1100::receive(void)
{
    uint8_t marcstate;

    sidle();                              //sets to idle first.
    spi_write_strobe(SRX);                //writes receive strobe (receive mode)

    marcstate = 0xFF;                     //set unknown/dummy state value

    while(marcstate != 0x0D)              //0x0D = RX
    {
        marcstate = (spi_read_register(MARCSTATE) & 0x1F); //read out state of cc1100 to be sure in RX
        //printf("marcstate_rx: 0x%02X\r", marcstate);
    }
    //printf("\r\n");
    delayMicroseconds(100);
    return TRUE;
}
