# KitBIOS

## Description:
BIOS source for the Kit-1 8-bit computer.

### BIOS Calls:
0. Reset
1. Write Character to Terminal
2. Write String to Terminal
3. Read Character from Terminal (No Echo)
4. Read from Sector of SD Card
5. Write to Sector of SD Card

### KitMon Functions:
* D  - dump
* E  - enter
* F  - fill
* J  - jump
* L  - load
* R  - registers
* S  - stack
* W  - write
* ?  - help
* ^R - reset

Terminal setup should be 19200 8-N-1, no echo, VT100 emulation, return key sends
LF, interpret standalone LF as CRLF. To view the help menu, type ```?``` and
press enter. All parameters are in hexadecimal format. Address ranges are
separated by a space.

### Legal:
The project is Copyright 2019 Ryan Clarke, licensed under the Apache License
version 2.0.
