/*
 * MODULE
 *
 *   main.c
 *
 * DESCRIPTION
 *
 *  Sets up the Olimex LPC2378-STK board and continuously outputs a "Hello
 *  World" banner through the UART0 port.
 *
 *  Used to verify the at the Eclipse IDE, Cygwin, CDT, and GNUARM
 *  have been installed correctly.
 *
 * OS
 *
 *  n/a
 *
 * PLATFORM
 *
 *  Olimex LPC2378-STK
 *
 * HISTORY
 *
 *   2007/10/01: Mitch Ishihara
 *     split init routines from main.c
 *     changed cEntry to main
 *   2007/09/12: Andrew N. Sloss:
 *     convert the main.c to use VOLATILExx(<address>) format
 *     added 1st draft comments
 *   2007/08/21: Andrew N. Sloss:
 *     inspired from James Lynch's example code demo2106_blink_flash.
****************************************************************************/
#define __MAIN_C__

//#include <stdio.h>
#include <stdint.h>
#include "lpc2378.hpp"
#include "init.h"
#include "led.hpp"
//#include "uarts.h"

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
/***************************************************************************/
/*  main                                                                   */
/***************************************************************************/
/*
 * NAME
 *
 *  main
 *
 * DESCRIPTION
 *
 *  prints out a standard banner on serial port
 *
 *   "University of Washington - UART Test Application"
 *
 * PARAMETERS
 *
 *  none...
 *
 * EXAMPLE
 *
 * from crt.s
 *
 *  B  main
 *
 * NOTES
 *
 *  This routine never terminates...
 *
 */

namespace
{
   void wait()
   {
       volatile uint32_t p = 0x100000;
       while (p--);
   }
}

int main(void)
{
    initHardware();
    
    while (1)
    {
        led_on();
        wait();
        led_off();
        wait();
    }

    return 0;
}
/*** EOF ***/
