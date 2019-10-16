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
 *  File Name : system_config.c
 *  Project   : Kit-1 8-bit Computer
 *  Device    : PIC18F47K40
 *  Author    : Ryan Clarke
 *  E-mail    : kj6msg@icloud.com
 *  ----------------------------------------------------------------------------
 *  Purpose : System configuration for the Kit-1 KitROM virtual ROM.
 ******************************************************************************/


/* CONFIG1 */
#pragma config FEXTOSC  = OFF,
#pragma config RSTOSC   = HFINTOSC_64MHZ
#pragma config CLKOUTEN = OFF
#pragma config CSWEN    = ON
#pragma config FCMEN    = OFF

/* CONFIG2 */
#pragma config MCLRE   = EXTMCLR
#pragma config PWRTE   = OFF
#pragma config LPBOREN = OFF
#pragma config BOREN   = OFF
#pragma config ZCD     = OFF
#pragma config PPS1WAY = OFF
#pragma config STVREN  = OFF
#pragma config DEBUG   = OFF
#pragma config XINST   = OFF

/* CONFIG3 */
#pragma config WDTCPS = WDTCPS_31           /* default */
#pragma config WDTE   = OFF
#pragma config WDTCCS = SC                  /* default */
#pragma config WDTCWS = WDTCWS_7            /* default */

/* CONFIG4 */
#pragma config WRT0  = OFF
#pragma config WRT1  = OFF
#pragma config WRT2  = OFF
#pragma config WRT3  = OFF
#pragma config WRT4  = OFF
#pragma config WRT5  = OFF
#pragma config WRT6  = OFF
#pragma config WRT7  = OFF
#pragma config WRTC  = OFF
#pragma config WRTB  = OFF
#pragma config WRTD  = OFF
#pragma config SCANE = OFF
#pragma config LVP   = ON

/* CONFIG5 */
#pragma config CP  = OFF
#pragma config CPD = OFF

/* CONFIG6 */
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTR4 = OFF
#pragma config EBTR5 = OFF
#pragma config EBTR6 = OFF
#pragma config EBTR7 = OFF
#pragma config EBTRB = OFF
