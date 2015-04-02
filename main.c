/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.10.3
        Device            :  PIC16F1509
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X 2.26
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#include "mcc_generated_files/mcc.h"

uint8_t symbol[] = { 0, 1, 2, 4, 8, 16, 32, 64, 128};

void RED8x8_Write( uint8_t reg, uint8_t b)
{
    // activate CS
    CS_SetLow();

    // send register / value pair
    SPI_Exchange8bit( reg);
    SPI_Exchange8bit( b);

    // deactivate CS
    CS_SetHigh();
}


/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // exit disaply shut down mode
    RED8x8_Write( 0x0C, 0x01);
    // configure driver for scanning columns 0..7
    RED8x8_Write( 0x0B, 0x07);
    // limit current drive to 1/32
    RED8x8_Write( 0x0A, 0x00);

    while (1)
    {
        uint8_t i, b;
        for( i=1; i<=8; i++)
        {
            b = symbol[i];
            RED8x8_Write( i, b);
            if (b & 0x80)
                symbol[i] = (b << 1) + 1;
            else
                symbol[i] = b << 1;
        }
        // wait 131ms
        while( !TMR0_HasOverflowOccured());
        TMR0IF = 0;
    }
}
/**
 End of File
*/