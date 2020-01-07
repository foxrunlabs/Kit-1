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

;= BIOS CALL TABLE =============================================================

BIOSTL = $00                    ; call table (LSBs) pointer (16-bit)
BIOSTH = $02                    ; call table (MSBs) pointer (16-bit)


;= BIOS ROUTINES ===============================================================

JIFFIES = $04                   ; uptime counter values
SECONDS = $05
MINUTES = $06
HOURS   = $07

STRADDR = $08                   ; string pointer for cputs (16-bit)


;= KITMON ======================================================================

ARG1 = $0A                      ; command line arguments (32-bit)
ARG2 = $0E

PCREG = $12                     ; CPU register storage
AREG  = $14
XREG  = $15
YREG  = $16
SREG  = $17
PREG  = $18

DADDR = $19                     ; saved address for dump (16-bit)


;= SPI =========================================================================

INB    = $1B                    ; received byte
OUTB   = $1C                    ; transmit byte
SHADOW = $1D                    ; shadow register for SPI port


;= SD CARD =====================================================================

CMDARG  = $1E                   ; command argument (32-bit)

SDCADDR = $22                   ; address pointer for sector read/write (16-bit)
SECTOR  = CMDARG                ; sector number (32-bit)


;= FAT16 =======================================================================

FATREG   = $24                  ; FAT region LBA (32-bit)
ROOTREG  = $28                  ; root directory region LBA (32-bit)
DATAREG  = $2C                  ; data region LBA (32-bit)

DIRENTRY = $30                  ; directory table entry pointer (16-bit)
FILENAME = $32                  ; file name pointer for find function (16-bit)
CLUSTER  = $34                  ; cluster for file read function (16-bit)


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
VIA      = IO  + $20
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

SDC_CLK  = %00000001            ; SPI clock
SDC_nCS  = %00000010            ; SPI chip select
SDC_CD   = %00000100            ; card detect
SDC_MOSI = %01000000            ; SPI serial output (host)
SDC_MISO = %10000000            ; SPI serial input (host)


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

SDCIDLE = $01                   ; SD card idle
ILLEGAL = $04                   ; illegal command
ACCEPT  = $05                   ; data accepted
DATATKN = $FE                   ; data packet token


;===============================================================================
; FAT16
;===============================================================================

;= CONSTANTS ===================================================================

SIGNATURE  = $AA55              ; boot signature
FAT16ID    = $06                ; FAT16 partition ID
CLUSTEROFF = $1A                ; location of first cluster in directory entry
BADSECTOR  = $FFF7              ; bad sector marker

;= MEMORY MAP ==================================================================

MBR   = $E800                   ; master boot record
BOOT  = MBR  + $0200            ; boot sector
FAT   = BOOT + $0200            ; FAT region
ROOT  = FAT  + $0200            ; root directory region
KITOS = $0300                   ; KitOS address

;- master boot record ----------------------------------------------------------
PARTTBL = MBR + $1BE            ; location of partition table (64 bytes)
MBRSIG  = MBR + $1FE            ; location of boot signature (16-bit)

;- partition table -------------------------------------------------------------
PART1    = PARTTBL              ; partition 1 (16 bytes)
P1TYPE   = PART1 + 4            ; location partition type (8-bit)
P1SECTOR = PART1 + 8            ; location of first sector LBA (32-bit)

PART2    = PART1 + 16           ; partition 2 (16 bytes)
P2TYPE   = PART2 + 4            ; location partition type (8-bit)
P2SECTOR = PART2 + 8            ; location of first sector LBA (32-bit)

PART3    = PART2 + 16           ; partition 3 (16 bytes)
P3TYPE   = PART3 + 4            ; location partition type (8-bit)
P3SECTOR = PART3 + 8            ; location of first sector LBA (32-bit)

PART4    = PART3 + 16           ; partition 4 (16 bytes)
P4TYPE   = PART4 + 4            ; location of partition type (8-bit)
P4SECTOR = PART4 + 8            ; location of first sector LBA (32-bit)

;- FAT16 boot sector -----------------------------------------------------------
BPB     = BOOT + $00B           ; start of BIOS Parameter Block
BOOTSIG = BOOT + $1FE           ; location of boot signature (16-bit)

;- BIOS Parameter Block --------------------------------------------------------
BPERSEC   = BPB                 ; Bytes Per Logical Sector (16-bit)
RESSEC    = BPB + $03           ; Reserved Logical Sectors (16-bit)
NUMFAT    = BPB + $05           ; Number of FATs (8-bit)
NUMROOT   = BPB + $06           ; Number of Root Entries (16-bit)
SECPERFAT = BPB + $0B           ; Sectors Per FAT (16-bit)
