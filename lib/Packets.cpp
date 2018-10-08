#include "CC1100.hpp"

//----------------------------------------------------------------------------//
// --- Packets --- //
//----------------------------------------------------------------------------//

uint8_t CC1100::packet_available()
{
    if(digitalRead(GDO2) == TRUE)                           //if RF package received
    {
        if(spi_read_register(IOCFG2) == 0x06)               //if sync word detect mode is used
        {
            while(digitalRead(GDO2) == TRUE){               //wait till sync word is fully received
                printf("!\r\n");
            }                                                  //for sync word receive
        }

        if(debug_level > 0){
             //printf("Pkt->:\r\n");
        }

        return TRUE;
    }
    return FALSE;
}

uint8_t CC1100::wait_for_packet(uint8_t milliseconds)
{
    for(uint8_t i = 0; i < milliseconds; i++)
        {
            delay(1);                 //delay till system has data available
            if (packet_available())
            {
                return TRUE;
            }
        }
    return FALSE;
}

uint8_t CC1100::sent_packet(uint8_t my_addr, uint8_t rx_addr, uint8_t *txbuffer,
                            uint8_t pktlen,  uint8_t tx_retries)
{
    uint8_t pktlen_ack, rssi, lqi;                              //default package len for ACK
    uint8_t rxbuffer[FIFOBUFFER];
    uint8_t tx_retries_count = 0;
    uint8_t from_sender;
    uint16_t ackWaitCounter = 0;

    if(pktlen > (FIFOBUFFER - 1))
    {
        printf("ERROR: package size overflow\r\n");
        return FALSE;
    }

    do                                                          //sent package out with retries
    {
        tx_payload_burst(my_addr, rx_addr, txbuffer, pktlen);   //loads the data in cc1100 buffer
        transmit();                                             //sents data over air
        receive();                                              //receive mode

        if(rx_addr == BROADCAST_ADDRESS){                       //no wait acknowledge if sent to broadcast address or tx_retries = 0
            return TRUE;                                        //successful sent to BROADCAST_ADDRESS
        }

        while (ackWaitCounter < ACK_TIMEOUT )                   //wait for an acknowledge
        {
            if (packet_available() == TRUE)                     //if RF package received check package acknowge
            {
                from_sender = rx_addr;                          //the original message sender address
                rx_fifo_erase(rxbuffer);                        //erase RX software buffer
                rx_payload_burst(rxbuffer, pktlen_ack);         //reads package in buffer
                check_acknolage(rxbuffer, pktlen_ack, from_sender, my_addr); //check if received message is an acknowledge from client
                return TRUE;                                    //package successfully sent
            }
            else{
                ackWaitCounter++;                               //increment ACK wait counter
                delay(1);                                       //delay to give receiver time
            }
        }

        ackWaitCounter = 0;                                     //resets the ACK_Timeout
        tx_retries_count++;                                     //increase tx retry counter

        if(debug_level > 0){                                    //debug output messages
            printf(" #:");
            printf("0x%02X \r\n", tx_retries_count);
        }
    }while(tx_retries_count <= tx_retries);                     //while count of retries is reaches

    return FALSE;                                               //sent failed. too many retries
}

void CC1100::sent_acknolage(uint8_t my_addr, uint8_t tx_addr)
{
    uint8_t pktlen = 0x06;                                      //complete Pktlen for ACK packet
    uint8_t tx_buffer[0x06];                                    //tx buffer array init

    tx_buffer[3] = 'A'; tx_buffer[4] = 'c'; tx_buffer[5] = 'k'; //fill buffer with ACK Payload

    tx_payload_burst(my_addr, tx_addr, tx_buffer, pktlen);      //load payload to CC1100
    transmit();                                                 //sent package over the air
    receive();                                                  //set CC1100 in receive mode

    if(debug_level > 0){                                        //debut output
        printf("Ack_sent!\r\n");
    }
}

uint8_t CC1100::check_acknolage(uint8_t *rxbuffer, uint8_t pktlen, uint8_t sender, uint8_t my_addr)
{
    int8_t rssi_dbm;
    uint8_t crc, lqi;

    if((pktlen == 0x05 && \
        rxbuffer[1] == my_addr || rxbuffer[1] == BROADCAST_ADDRESS) && \
        rxbuffer[2] == sender && \
        rxbuffer[3] == 'A' && rxbuffer[4] == 'c' && rxbuffer[5] == 'k')   //acknolage received!
        {
            if(rxbuffer[1] == BROADCAST_ADDRESS){                           //if receiver address BROADCAST_ADDRESS skip acknolage
                if(debug_level > 0){
                    printf("BROADCAST ACK\r\n");
                }
                return FALSE;
            }
            rssi_dbm = rssi_convert(rxbuffer[pktlen + 1]);
            lqi = lqi_convert(rxbuffer[pktlen + 2]);
            crc = check_crc(lqi);

            if(debug_level > 0){
                printf("ACK! ");
                printf("RSSI:%i ",rssi_dbm);
                printf("LQI:0x%02X ",lqi);
                printf("CRC:0x%02X\r\n",crc);
            }
            return TRUE;
        }
    return FALSE;
}

//----------------------------------------------------------------------------//
// --- Payload --- //
//----------------------------------------------------------------------------//

uint8_t CC1100::get_payload(uint8_t rxbuffer[], uint8_t &pktlen, uint8_t &my_addr,
                            uint8_t &sender, int8_t &rssi_dbm, uint8_t &lqi)
{
    uint8_t crc;

    rx_fifo_erase(rxbuffer);                               //delete rx_fifo bufffer

    if(rx_payload_burst(rxbuffer, pktlen) == FALSE)        //read package in buffer
    {
        rx_fifo_erase(rxbuffer);                           //delete rx_fifo bufffer
        return FALSE;                                    //exit
    }
    else
    {
        my_addr = rxbuffer[1];                             //set receiver address to my_addr
        sender = rxbuffer[2];

        if(check_acknolage(rxbuffer, pktlen, sender, my_addr) == TRUE) //acknowlage received?
        {
            rx_fifo_erase(rxbuffer);                       //delete rx_fifo bufffer
            return FALSE;                                //Ack received -> finished
        }
        else                                               //real data, and sent acknowladge
        {
            rssi_dbm = rssi_convert(rxbuffer[pktlen + 1]); //converts receiver strength to dBm
            lqi = lqi_convert(rxbuffer[pktlen + 2]);       //get rf quialtiy indicator
            crc = check_crc(lqi);                          //get packet CRC

            if(debug_level > 0){                           //debug output messages
                if(rxbuffer[1] == BROADCAST_ADDRESS)       //if my receiver address is BROADCAST_ADDRESS
                {
                    printf("BROADCAST message\r\n");
                }

                printf("RX_FIFO:");
                for(uint8_t i = 0 ; i < pktlen + 1; i++)   //showes rx_buffer for debug
                {
                    printf("0x%02X ", rxbuffer[i]);
                }
                printf("| 0x%02X 0x%02X |", rxbuffer[pktlen+1], rxbuffer[pktlen+2]);
                printf("\r\n");

                printf("RSSI:%d ", rssi_dbm);
                printf("LQI:");printf("0x%02X ", lqi);
                printf("CRC:");printf("0x%02X ", crc);
                printf("\r\n");
            }

            my_addr = rxbuffer[1];                         //set receiver address to my_addr
            sender = rxbuffer[2];                          //set from_sender address

            if(my_addr != BROADCAST_ADDRESS)               //send only ack if no BROADCAST_ADDRESS
            {
                sent_acknolage(my_addr, sender);           //sending acknolage to sender!
            }

            return TRUE;
        }
        return FALSE;
    }
}

uint8_t CC1100::tx_payload_burst(uint8_t my_addr, uint8_t rx_addr,
                              uint8_t *txbuffer, uint8_t length)
{
    txbuffer[0] = length-1;
    txbuffer[1] = rx_addr;
    txbuffer[2] = my_addr;

    spi_write_burst(TXFIFO_BURST,txbuffer,length); //writes TX_Buffer +1 because of pktlen must be also transfered

    if(debug_level > 0){
        printf("TX_FIFO: ");
        for(uint8_t i = 0 ; i < length; i++)       //TX_fifo debug out
        {
             printf("0x%02X ", txbuffer[i]);
        }
        printf("\r\n");
  }
  return TRUE;
}

uint8_t CC1100::rx_payload_burst(uint8_t rxbuffer[], uint8_t &pktlen)
{
    uint8_t bytes_in_RXFIFO = 0;
    uint8_t res = 0;

    bytes_in_RXFIFO = spi_read_register(RXBYTES);              //reads the number of bytes in RXFIFO

    if((bytes_in_RXFIFO & 0x7F) && !(bytes_in_RXFIFO & 0x80))  //if bytes in buffer and no RX Overflow
    {
        spi_read_burst(RXFIFO_BURST, rxbuffer, bytes_in_RXFIFO);
        pktlen = rxbuffer[0];
        res = TRUE;
    }
    else
    {
        if(debug_level > 0){
            printf("no bytes in RX buffer or RX Overflow!: ");printf("0x%02X \r\n", bytes_in_RXFIFO);
        }
        sidle();                                                  //set to IDLE
        spi_write_strobe(SFRX);delayMicroseconds(100);            //flush RX Buffer
        receive();                                                //set to receive mode
        res = FALSE;
    }

    return res;
}

//----------------------------------------------------------------------------//
// --- Buffer --- //
//----------------------------------------------------------------------------//

void CC1100::tx_fifo_erase(uint8_t *txbuffer)
{
    memset(txbuffer, 0, sizeof(FIFOBUFFER));  //erased the TX_fifo array content to "0"
}

void CC1100::rx_fifo_erase(uint8_t *rxbuffer)
{
    memset(rxbuffer, 0, sizeof(FIFOBUFFER)); //erased the RX_fifo array content to "0"
}

