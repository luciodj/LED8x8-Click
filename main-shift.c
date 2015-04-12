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

void LED8x8_Write( uint8_t reg, uint8_t b)
// send register / value pair
{
    CS_SetLow();
      SPI_Exchange8bit( reg);
      SPI_Exchange8bit( b);
    CS_SetHigh();
}


void LED8x8_Init( uint8_t intensity)
{
    // exit disaply shut down mode
    LED8x8_Write( 0x0C, 0x01);
    // configure driver for scanning columns 0..7
    LED8x8_Write( 0x0B, 0x07);
    // limit current drive to 1/32
    LED8x8_Write( 0x0A, intensity);  
}


void Delay()
{
    while( !TMR0_HasOverflowOccured());
    TMR0IF = 0;
}


uint8_t matrix[8];
const uint8_t font_first = 'A';
const uint8_t font_table[] = { 
    //1, 2, 4, 8, 16, 32, 64, 128,   // '/'
    0b00000000,     // A
    0b11111000,
    0b00100100,
    0b00100010,
    0b00100010,
    0b00100100,
    0b11111000,
    0b00000000,
    1, 2, 4, 8, 16, 32, 64, 128,   // 'B'
    0b00000000,     // C
    0b00111000,
    0b01000100,
    0b10000010,
    0b10000010,
    0b10000010,
    0b01000100,
    0b00000000,
    1, 2, 4, 8, 16, 32, 64, 128,   // 'D'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'E'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'F'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'G'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'H'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'I'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'J'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'K'
    0b00000000,     // L
    0b11111110,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b00000000,
    1, 2, 4, 8, 16, 32, 64, 128,   // 'M'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'N'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'O'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'P'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'Q'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'R'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'S'
    1, 2, 4, 8, 16, 32, 64, 128,   // 'T'
    0b00000000,     // U
    0b01111110,
    0b10000000,
    0b10000000,
    0b10000000,
    0b10000000,
    0b01111110,
    0b00000000,

};

void LED8x8_Display( uint8_t *m)
{
    uint8_t i;
    for( i=1; i<=8; i++)
        LED8x8_Write( i, *m++);
}


void LED8x8_Putch( uint8_t *m, char c)
{
    uint8_t i;
    const uint8_t *p = &font_table[( c-font_first) << 3];
    for( i=0; i<8; i++)
        m[i] = *p++;
}


void LED8x8_ShiftLeft( uint8_t *m, char c, uint8_t n)
{
    uint8_t i;
    for( i=0; i<7; i++)
        m[i] = m[i+1];
    m[7] = font_table[(( c-font_first) << 3) + n];
}


void LED8x8_ShiftUp( uint8_t *m, char c, uint8_t n)
{
    uint8_t i, k;
    const uint8_t *p;
    p = &font_table[ (c-font_first) << 3];
    for( i=0; i<8; i++)
    {
        m[i] >>= 1;
        k = *p++;
        m[i] += ((k << (7-n)) & 0x80);
    }
}


void LED8x8_RotateUp( uint8_t *m)
{
    uint8_t i, b;
    for( i=0; i<8; i++)
    {
        b = m[i] & 1;
        m[i] >>= 1;
        if ( b)
            m[i] = m[i] + 0x80;
    }
}

void LED8x8_RotateLeft( uint8_t *m)
{
    uint8_t i, b;
    b = m[0];
    for( i=0; i<7; i++)
        m[i] = m[i+1];
    m[7] = b;
}


void LED8x8_HorMessage( uint8_t *m, char *s)
{
    char c;
    uint8_t i;
    for( i=0; i<8; i++)
        m[i] = 0;
    while ( c = *s++)
    {
        for( i=0; i<8; i++)
        {
            LED8x8_Display( m);
            LED8x8_ShiftLeft( m, c, i);
            Delay();
        }
    }
}


void LED8x8_VerMessage( uint8_t *m, char *s)
{
    char c;
    uint8_t i;
    for( i=0; i<8; i++)
        m[i] = 0;
    while ( c = *s++)
    {
        for( i=0; i<8; i++)
        {
            LED8x8_ShiftUp( m, c, i);
            LED8x8_Display( m);
            Delay();
        }
    }

}

/*
     Main application
 */
void main(void)
{
    uint8_t i;
    // initialize the device
    SYSTEM_Initialize();
    LED8x8_Init( 0);        // turn on LED matrix at lowest intensity

    while (1)
    {
        LED8x8_Putch( &matrix, 'B');
        for( i=0; i<8; i++)
        {
            LED8x8_Display( &matrix);
            LED8x8_RotateUp( &matrix);
        Delay();
        }
        for( i=0; i<8; i++)
        {
            LED8x8_Display( &matrix);
            LED8x8_RotateLeft( &matrix);
        Delay();
        }

        LED8x8_HorMessage( &matrix, "LUCA");
        LED8x8_VerMessage( &matrix, "LUCA");
    }
}
/**
 End of File
*/