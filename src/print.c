/*
 * MODULE
 *
 *   print.c
 *
 * DESCRIPTION
 *
 * Very lightweight print functions.
 *
 * OS
 *
 *  n/a
 *
 * PLATFORM
 *
 * HISTORY
 *   2007/10/30: Added Alan's uint32_t print
 *               Added Stephane's printHex
 *   2007/10/01: Mitch Ishihara
****************************************************************************/
#define __PRINT_C__

//#include <stdio.h>
#include <stdint.h>
#include "print.h"
#include "lpc2378.h"


/*=========================================================================*/
/*  DEFINE: All Structures and Common Constants                            */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Prototypes                                                     */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Definition of all local Data                                   */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Definition of all local Procedures                             */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: All code exported                                              */
/*=========================================================================*/
void printHex(uint32_t u32)
{
    uint32_t   u32Mask  = 0xF0000000;
    uint8_t    u32Shift = 32;
    uint32_t   u32Char;

    do {
        u32Shift -= 4;
        u32Char = (u32 & u32Mask) >> u32Shift;
        u32Mask >>= 4;
        if (u32Char >= 0xA)
        {
            PUTC('A' + (u32Char - 10));
        }
        else
        {
            PUTC('0' + u32Char);
        }
    } while (u32Shift > 0);
}

void print_uint32(uint32_t u)
{
    uint32_t    buffer_length = 20;
    char      buffer[buffer_length];
    char      *p = &buffer[buffer_length - 1];

    *p = '\0';
    do {
        p--;
        *p = (u % 10) + '0';
        u /= 10;
    } while (u > 0);

    printString(p);
}


/*
 * NAME
 *
 *  printString
 *
 * DESCRIPTION
 *
 *  Standard printString function
 *
 * PARAMETERS
 *
 *  none...
 *
 * EXAMPLE
 *
 *  printString("hello embedded world");
 *
 * NOTES
 *
 *  intercepts '\n' and adds '\r'  (LF+CR)
 *
 */

void printString(char *ptr)
{
    if (ptr==0 || *ptr==0) return;

    do
    {
      if (*ptr=='\n')
      {
      PUTC(*ptr++);
      PUTC('\r');
      }
      else
      {
      PUTC(*ptr++);
      }
    }
    while (*ptr!=0);
}
/*** EOF ***/
