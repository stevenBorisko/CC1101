CC1101
======

Driver library for Ti CC1100 / CC1101 with a Raspberry Pi.<br />
Setup guide to get your RBP to where it needs to be to run this code.

General description of RF packet
================================

```
-> pkt_len [1byte] | rx_addr [1byte] | tx_addr [1byte] | payload data [1..60bytes]
```

pkt_len = count of bytes which shall transfered over air (rx_addr + tx_addr + payload data)<br />
rx_addr = address of device, which shall receive the message (0x00 = broadcast to all devices)<br />
tx_addr = transmitter or my address. the receiver should know who has sent a message.<br />
payload = 1 to 60 bytes payload data.<br />

TX Bytes example:<br />
-> 0x06 0x03 0x01 0x00 0x01 0x02 0x03<br />

Basic configuration
===================

Use **uint8_t CC1100::begin(volatile uint8_t &My_addr)** always as first configuration step.

Device address
--------------

You should set a unique device address for the transmitter and a unique device address for the receiver. 
This can be done with **void CC1100::set_myaddr(uint8_t addr)**.

i.E. -> TX = 0x01 ; RX = 0x03


Modulation modes
----------------

the following modulation modes can be set by **void CC1100::set_mode(uint8_t mode)**. Transmitter and receiver must have the same Mode setting.

```
1 = GFSK_1_2_kb
2 = GFSK_38_4_kb
3 = GFSK_100_kb
4 = MSK_250_kb
5 = MSK_500_kb
6 = OOK_4_8_kb
```

ISM frequency band
------------------

you can set a frequency operation band by **void CC1100::set_ISM(uint8_t ism_freq)** to make it compatible with your hardware.

```
1 = 315
2 = 433
3 = 868
4 = 915
```

Compiling
============

Compile both the transmitter and the receiver code: `make` or `make all`<br />
Compile receiver: `make receiver`
Compile transmitter: `make transmitter`
Compile and test receiver: `make runReceiver`
Compile and test transmitter: `make runTransmitter`

Command Line parameters
-----------------------

Receiver (RX_Demo.out):<br />
  ```
  CC1100 SW [-h] [-V] [-v] [-a My_Addr] [-c channel] [-f frequency] [-m modulation]
  -h              			print this help and exit
  -V              			print version and exit
  -v              			set verbose flag
  -a my address [1-255] 		set my address
  -c channel    [1-255] 		set transmit channel
  -f frequency  [315,434,868,915]  	set ISM band
  -m modulation [100,250,500]           set modulation
  ```
  
  Example,<br />
  ```
  sudo ./RX_Demo -v -a3 -c1 -f434 -m100
  ```

Transmitter (TX_Demo.out):<br />
```
CC1100 SW [-h] [-V] [-a My_Addr] [-r RxDemo_Addr] [-i Msg_Interval] [-t tx_retries] [-c channel] [-f frequency]
          [-m modulation]

  -h              			print this help and exit
  -V              			print version and exit
  -v              			set verbose flag
  -a my address [1-255] 		set my address
  -r rx address [1-255] 	  	set RxDemo receiver address
  -i interval ms[1-6000] 	  	sets message interval timing
  -t tx_retries [0-255] 	  	sets message send retries
  -c channel    [1-255] 		set transmit channel
  -f frequency  [315,434,868,915]  	set ISM band
  -m modulation [100,250,500]           set modulation
  ```
  
  Example,<br />
  ```
  sudo ./TX_Demo -v -a1 -r3 -i1000 -t5 -c1 -f434 -m100
  ```
