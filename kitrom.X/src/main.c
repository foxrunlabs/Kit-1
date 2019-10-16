/*******************************************************************************
 *  Copyright 2019 Ryan Clarke
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy
 *  of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  License for the specific language governing permissions and limitations
 *  under the License.
 ******************************************************************************/

/*******************************************************************************
 *  Program   : KitROM
 *  File Name : main.c
 *  Project   : Kit-1 8-bit Computer
 *  Device    : PIC18F47K40
 *  Author    : Ryan Clarke
 *  E-mail    : kj6msg@icloud.com
 *  ----------------------------------------------------------------------------
 *  Purpose : Acts as a virtual ROM for the Kit-1 8-bit computer.
 ******************************************************************************/


#include <xc.h>
#include <stdint.h>
#include <stdlib.h>

#include "system_config.h"


#define _XTAL_FREQ 64000000L        /* 64 MHz system clock */


extern const uint16_t bios_start;
extern const uint8_t  bios[];       /* BIOS image */


int main(void)
{
    uint16_t addr;
    uint16_t i;
    
    /* system configuration ***************************************************/
    
    /* disable peripherals */
    PMD0 = 0xFF;
    PMD1 = 0xFF;
    PMD2 = 0xFF;
    PMD3 = 0xFF;
    PMD4 = 0xFF;
    PMD5 = 0xFF;
    
    /* disable analog inputs */
    CTRL_ANSEL  = 0b11111000;       /* RW, BE, nRST */
    DATA_ANSEL  = 0x00;
    ADDRL_ANSEL = 0x00;
    ADDRH_ANSEL = 0x00;
    
    /* enable open drain pins */
    CTRL_ODCON = 0b00000011;        /* BE, nRST */
    
    /* control pins setup */
    nRST = 1;
    BE   = 1;
    
    nRST_TRIS = 0;
    BE_TRIS   = 0;
    RW_TRIS   = 1;
    
    /* bus setup */
    ADDRL_TRIS = 0xFF;
    ADDRH_TRIS = 0xFF;
    DATA_TRIS  = 0xFF;
    
    
    /* connect KitROM to SRAM *************************************************/
    
    /* take control of the bus */
    nRST = 0;
    BE   = 0;
    
    /* connect to SRAM */
    RW    = 1;
    ADDRL = 0x00;
    ADDRH = 0x00;
    DATA  = 0x00;
    
    RW_TRIS    = 0;
    ADDRL_TRIS = 0x00;
    ADDRH_TRIS = 0x00;
    DATA_TRIS  = 0x00;
    
    
    /* load ROM to SRAM *******************************************************/
    
    addr = bios_start;
    i    = 0;
    
    while(addr)
    {
        ADDRL = (uint8_t)(addr);
        ADDRH = (uint8_t)(addr >> 8);
        DATA  = bios[i];
        
        RW = 0;
        __delay_us(1);
        RW = 1;
        
        addr++;
        i++;
    }
    
    
    /* disconnect KitROM from SRAM ********************************************/
    
    /* disconnect from SRAM */
    DATA_TRIS  = 0xFF;
    ADDRH_TRIS = 0xFF;
    ADDRL_TRIS = 0xFF;
    RW_TRIS    = 1;
    
    /* return the bus */
    BE   = 1;
    nRST = 1;
    
    Sleep();
    
    return EXIT_SUCCESS;
}
