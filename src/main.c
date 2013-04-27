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
#include "lpc2378.h"
#include "init.h"
#include "print.h"
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
int main(void)
{
	uint32_t p;
	
    /* initialize */
    initHardware();
    
    printString("\033[2J"); /* Clear entire screen */
    printString("Olimex LPC-2378-STK... alive!!!\n");
    
    //sprintf(string, "sprintf works!\n");
    //printString(string);

    while (1)
    {
        /* Turn MCIPWR SD LED On */
        VOLATILE32(FIO0SET) |= 1<<21;
        
        printString("University of Washington - UART Test Application \n");
        for (p = 0; p < 0x100000; p++ );        // wait

        // IMPORTANT: String formatting drags in tons of other library code
        //  sprintf(string, "\n.%u", p);
        //  printString(string);
        
        /* Turn MCIPWR SD LED Off */
        VOLATILE32(FIO0CLR) |= 1<<21;
        for (p = 0; p < 0x100000; p++ );        // wait
    }
    /* never terminates, but put this here to make compiler happy ... */
    return(0);
}
/*** EOF ***/
