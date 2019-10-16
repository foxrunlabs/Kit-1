# Kit-1 8-bit Computer

## Description:
The Kit-1 is an 8-bit computer based on the 65C02 CPU. Specifications include:

* 5 MHz system clock
* 64 KiB SRAM
* Serial port using a 65C51 ACIA
* 8-bit GPIO port using half of a 65C22 VIA
* Virtual ROM using an 8-bit PIC18F47K40 MCU
* microSD card interface using half of a 65C22 VIA

## Boot Sequence
The Kit-1 and peripherals are initially held in reset by the Virtual ROM upon
power-up or hard reset. During this reset period, the MCU loads the upper
portion of RAM with the BIOS image. Once this is complete, the Virtual ROM
releases the bus and goes to sleep. The BIOS initializes the peripherals and
searches for a valid KitOS image on the SD card. If KitOS is not found, then the
KitBIOS will launch the ROM monitor.

## Getting Started
The firmware and software can be built by issuing the ```make``` command in the
project root directory. This will build the BIOS, the Virtual ROM image, and
KitOS. Program the PIC18F47K40 with the Virtual ROM image and copy KitOS the
root directory of a FAT16 partition on an SD card.  

To create a simulator version of the BIOS for py65mon, issue ```make sim``` and
then execute the ```./simulate.sh``` command.

### Legal:
The source code is Copyright 2019 Ryan Clarke, licensed under the Apache License
version 2.0. A copy of the license is found in the ```doc/``` directory.
