#include "CC1100.hpp"

void CC1100::wor_enable()
{
/*
    EVENT1 = WORCTRL[6:4] -> Datasheet page 88
    EVENT0 = (750/Xtal)*(WOREVT1<<8+WOREVT0)*2^(5*WOR_RES) = (750/26Meg)*65407*2^(5*0) = 1.89s

                        (WOR_RES=0;RX_TIME=0)               -> Datasheet page 80
i.E RX_TIMEOUT = EVENT0*       (3.6038)      *26/26Meg = 235.8ms
                        (WOR_RES=0;RX_TIME=1)               -> Datasheet page 80
i.E.RX_TIMEOUT = EVENT0*       (1.8029)      *26/26Meg = 117.9ms
*/
    sidle();

    spi_write_register(MCSM0, 0x18);    //FS Autocalibration
    spi_write_register(MCSM2, 0x01);    //MCSM2.RX_TIME = 1b

    // configure EVENT0 time
    spi_write_register(WOREVT1, 0xFF);  //High byte Event0 timeout
    spi_write_register(WOREVT0, 0x7F);  //Low byte Event0 timeout

    // configure EVENT1 time
    spi_write_register(WORCTRL, 0x78);  //WOR_RES=0b; tEVENT1=0111b=48d -> 48*(750/26MHz)= 1.385ms

    spi_write_strobe(SFRX);             //flush RX buffer
    spi_write_strobe(SWORRST);          //resets the WOR timer to the programmed Event 1
    spi_write_strobe(SWOR);             //put the radio in WOR mode when CSn is released

    delayMicroseconds(100);
}

void CC1100::wor_disable()
{
    sidle();                            //exit WOR Mode
    spi_write_register(MCSM2, 0x07);    //stay in RX. No RX timeout
}

void CC1100::wor_reset()
{
    sidle();                            //go to IDLE
    spi_write_register(MCSM2, 0x01);    //MCSM2.RX_TIME = 1b
    spi_write_strobe(SFRX);             //flush RX buffer
    spi_write_strobe(SWORRST);          //resets the WOR timer to the programmed Event 1
    spi_write_strobe(SWOR);             //put the radio in WOR mode when CSn is released

    delayMicroseconds(100);
}
