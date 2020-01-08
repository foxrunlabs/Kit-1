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

papfnBIOSCallsL = $00           ; BIOS call table (LSBs) pointer
papfnBIOSCallsH = $02           ; BIOS call table (MSBs) pointer


;= BIOS ROUTINES ===============================================================

byJiffies  = $04                ; uptime counter values
bySeconds  = $05
byMinutes  = $06
byHours    = $07

pszString = $08                 ; string pointer for cputs


;= KITMON ======================================================================

dwArg1  = $0A                   ; command line arguments
dwArg2  = $0E

wPCreg  = $12                   ; CPU register storage
byAreg  = $14
byXreg  = $15
byYreg  = $16
bySreg  = $17
byPreg  = $18

pabDump = $19                   ; pointer to data for dump command


;= SPI =========================================================================

byIn        = $1B               ; received byte
byOut       = $1C               ; transmit byte
byVIAShadow = $1D               ; shadow register for SPI port


;= SD CARD =====================================================================

dwSDCommand = $1E               ; command argument

pabSector   = $22               ; pointer to sector read/write data
dwSector    = dwSDCommand       ; sector number


;= FAT16 =======================================================================

dwFATRegion  = $24              ; FAT region LBA
dwRootRegion = $28              ; root directory region LBA
dwDataRegion = $2C              ; data region LBA

pdirEntry    = $30              ; directory table entry pointer
psFilename   = $32              ; file name pointer for find function
wCluster     = $34              ; cluster for file read function


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
wMBRSig = MBR + $1FE            ; location of boot signature (16-bit)

;- partition table -------------------------------------------------------------
tblPart1   = MBR + $1BE         ; partition 1 (16 bytes)
byP1Type   = tblPart1 + 4       ; location partition type
dwP1Sector = tblPart1 + 8       ; location of first sector LBA

tblPart2   = tblPart1 + 16      ; partition 2 (16 bytes)
byP2Type   = tblPart2 + 4       ; location partition type
dwP2Sector = tblPart2 + 8       ; location of first sector LBA

tblPart3   = tblPart2 + 16      ; partition 3 (16 bytes)
byP3Type   = tblPart3 + 4       ; location partition type
dwP3Sector = tblPart3 + 8       ; location of first sector LBA

tblPart4   = tblPart3 + 16      ; partition 4 (16 bytes)
byP4Type   = tblPart4 + 4       ; location of partition type
dwP4Sector = tblPart4 + 8       ; location of first sector LBA

;- FAT16 boot sector -----------------------------------------------------------
BPB      = BOOT + $00B          ; start of BIOS Parameter Block
wBootSig = BOOT + $1FE          ; location of boot signature

;- BIOS Parameter Block --------------------------------------------------------
wBPerSec   = BPB                ; Bytes Per Logical Sector
wRsrvSec   = BPB + $03          ; Reserved Logical Sectors
byNumFAT    = BPB + $05         ; Number of FATs
wNumRoot   = BPB + $06          ; Number of Root Entries
wSecPerFAT = BPB + $0B          ; Sectors Per FAT
