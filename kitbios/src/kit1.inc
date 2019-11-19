;===============================================================================
; Copyright 2019 Ryan Clarke
;
; Licensed under the Apache License, Version 2.0 (the "License"); you may not
; use this file except in compliance with the License. You may obtain a copy of
; the License at
; 
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
; WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
; License for the specific language governing permissions and limitations under
; the License.
;===============================================================================

;===============================================================================
; Program   : KitBIOS
; File Name : kit1.inc
; Project   : Kit-1 8-bit Computer
; Author    : Ryan Clarke
; E-mail    : kj6msg@icloud.com
;-------------------------------------------------------------------------------
; Purpose   : Include file for KitBIOS and KitMon.
;===============================================================================


;===============================================================================
; ASCII CHARACTER CONSTANTS
;===============================================================================

NUL  = $00
SOH  = $01
_STX = $02
ETX  = $03
EOT  = $04
ENQ  = $05
ACK  = $06
BEL  = $07
BS   = $08
HT   = $09
LF   = $0A
VT   = $0B
FF   = $0C
CR   = $0D
SO   = $0E
SI   = $0F
DLE  = $10
DC1  = $11
DC2  = $12
DC3  = $13
DC4  = $14
NAK  = $15
SYN  = $16
ETB  = $17
CAN  = $18
EM   = $19
SUB  = $1A
ESC  = $1B
FS   = $1C
GS   = $1D
RS   = $1E
US   = $1F
DEL  = $7F


;===============================================================================
; ZERO PAGE MEMORY MAP
;===============================================================================

;= GENERAL REGISTERS ===========================================================

R0 = $00
R1 = $01
R2 = $02
R3 = $03
R4 = $04
R5 = $05
R6 = $06
R7 = $07
R8 = $08
R9 = $09
RA = $0A
RB = $0B
RC = $0C
RD = $0D
RE = $0E
RF = $0F


;= BIOS CALL TABLE =============================================================

BIOSTL = $10                    ; 16-bit call table (LSBs) pointer
BIOSTH = $12                    ; 16-bit call table (MSBs) pointer


;= BIOS ROUTINES ===============================================================

JIFFIES = $14                   ; uptime counter values
SECONDS = $15
MINUTES = $16
HOURS   = $17

STRADDR = $18                   ; 16-bit string pointer for cputs


;= KITMON ======================================================================

ARG1 = $1A                      ; 32-bit command line arguments
ARG2 = $1E

PCREG = $22                     ; CPU register storage
AREG  = $24
XREG  = $25
YREG  = $26
SREG  = $27
PREG  = $28

DADDR = $29                     ; saved 16-bit address for memory dump function


;= SPI =========================================================================

INB    = $2B                    ; received byte
OUTB   = $2C                    ; transmit byte
SHADOW = $2D                    ; shadow register for SPI port


;= SD CARD =====================================================================

CMDARG  = $2E                   ; 32-bit command argument

SDCADDR = $32                   ; 16-bit address for sector read/write
SECTOR  = CMDARG                ; 32-bit sector number


;= FAT16 =======================================================================

ROOTSEC = $34                   ; 32-bit root directory region sector


;===============================================================================
; HARDWARE DEVICES
;===============================================================================

;= IO MEMORY MAP ===============================================================

IO = $0200

;- device 0 --------------------------------------------------------------------
ACIA         = IO + $10
ACIA_DATA    = ACIA + $0
ACIA_STATUS  = ACIA + $1
ACIA_COMMAND = ACIA + $2
ACIA_CONTROL = ACIA + $3

;- device 1 --------------------------------------------------------------------
VIA      = IO + $20
VIA_ORB  = VIA + $0
VIA_IRB  = VIA_ORB
VIA_ORA  = VIA + $1
VIA_IRA  = VIA_ORA
VIA_DDRB = VIA + $2
VIA_DDRA = VIA + $3
VIA_T1CL = VIA + $4
VIA_T1CH = VIA + $5
VIA_T1LL = VIA + $6
VIA_T1LH = VIA + $7
VIA_T2CL = VIA + $8
VIA_T2CH = VIA + $9
VIA_SR   = VIA + $A
VIA_ACR  = VIA + $B
VIA_PCR  = VIA + $C
VIA_IFR  = VIA + $D
VIA_IER  = VIA + $E
VIA_ORAH = VIA + $F
VIA_IRAH = VIA_ORAH

;- device 2 --------------------------------------------------------------------
DEV2 = IO + $40

;- device 3 --------------------------------------------------------------------
DEV3 = IO + $80


;===============================================================================
; SD CARD
;===============================================================================

;= PINS ========================================================================

SDC_CLK  = %00000001
SDC_nCS  = %00000010
SDC_CD   = %00000100
SDC_MOSI = %01000000
SDC_MISO = %10000000


;= COMMANDS ====================================================================

CMD0   = $40                    ; GO_IDLE_STATE
CMD1   = $41                    ; SEND_OP_COND
CMD8   = $48                    ; SEND_IF_COND
CMD16  = $50                    ; SET_BLOCKLEN
CMD17  = $51                    ; READ_SINGLE_BLOCK
CMD24  = $58                    ; WRITE_BLOCK
ACMD41 = $69                    ; APP_SEND_OP_COND
CMD55  = $77                    ; APP_CMD
CMD58  = $7A                    ; READ_OCR


;= RESPONSES ===================================================================

SDCIDLE = $01
ILLEGAL = $04
ACCEPT  = $05
DATATKN = $FE


;===============================================================================
; MASTER BOOT RECORD
;===============================================================================

;= CONSTANTS ===================================================================

BOOTSIG = $AA55
FAT16ID = $06

;= MEMORY MAP ==================================================================

MBR      = $0300
PART1    = MBR + $1BE
P1TYPE   = PART1 + $4
P1SECTOR = PART1 + $8
PART2    = MBR + $01CE
P2TYPE   = PART2 + $4
P2SECTOR = PART2 + $8
PART3    = MBR + $01DE
P3TYPE   = PART3 + $4
P3SECTOR = PART3 + $8
PART4    = MBR + $01EE
P4TYPE   = PART4 + $4
P4SECTOR = PART4 + $8


;===============================================================================
; FAT16
;===============================================================================

;= MEMORY MAP ==================================================================

;- FAT16 boot sector -----------------------------------------------------------
BOOT      = $0500
BPB       = BOOT + $00B
RESERVE   = BPB + $03
NUMFAT    = BPB + $05
SECPERFAT = BPB + $0B
VOLUME    = BOOT + $02B

;- FAT16 root directory sector -------------------------------------------------
ROOT = $0700
