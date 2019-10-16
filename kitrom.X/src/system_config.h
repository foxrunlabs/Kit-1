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
 *  File Name : system_config.h
 *  Project   : Kit-1 8-bit Computer
 *  Device    : PIC18F47K40
 *  Author    : Ryan Clarke
 *  E-mail    : kj6msg@icloud.com
 *  ----------------------------------------------------------------------------
 *  Purpose : System configuration for the Kit-1 KitROM virtual ROM.
 ******************************************************************************/


#ifndef SYSTEM_CONFIG_H
#define	SYSTEM_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <xc.h>


/* control pins */
#define nRST PORTEbits.RE0
#define BE   PORTEbits.RE1
#define RW   PORTEbits.RE2

#define nRST_TRIS TRISE0
#define BE_TRIS   TRISE1
#define RW_TRIS   TRISE2

#define CTRL_ANSEL ANSELE
#define CTRL_ODCON ODCONE

/* bus pins */
#define DATA  PORTA
#define ADDRL PORTC
#define ADDRH PORTD

#define DATA_TRIS  TRISA
#define ADDRL_TRIS TRISC
#define ADDRH_TRIS TRISD

#define DATA_ANSEL  ANSELA
#define ADDRL_ANSEL ANSELC
#define ADDRH_ANSEL ANSELD


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_CONFIG_H */
