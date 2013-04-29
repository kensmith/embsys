/*
 * MODULE
 *
 *   init.c
 *
 * DESCRIPTION
 *
 *  Hardware Initialization Routines
 *
 * PLATFORM
 *
 *  Olimex LPC-2378-STK
 *
 * HISTORY
 *
 *   2007/10/31: Mitch Ishihara:
 *     changed PINSEL10 setting to just write the value instead
 *       of read-modify-write.
 *   2007/10/01: Mitch Ishihara:
 *     split init routines from main.c
 *     changed MEMMAP to USERRAMMODE to run completely from RAM
 *   2007/09/12: Andrew N. Sloss:
 *     convert the main.c to use VOLATILExx(<address>) format
 *     added 1st draft comments
 *   2007/08/21: Andrew N. Sloss:
 *     inspired from James Lynch's example code demo2106_blink_flash.
 *
 * NOTES
 *
 *  Taken from the LPC2378 User Manual:
 *
 *   5.14 PLL setup sequence
 *
 *   The following sequence must be followed step by step in order to
 *   have the PLL initialized an running:
 *
 *   1. Disconnect the PLL with one feed sequence if PLL is already
 *      connected.
 *   2. Disable the PLL with one feed sequence.
 *   3. Change the CPU Clock Divider setting to speed up operation without
 *      the PLL, if desired.
 *   4. Write to the Clock Source Selection Control register to change the
 *      clock source.
 *   5. Write to the PLLCFG and make it effective with one feed sequence.
 *      The PLLCFG can only be updated when the PLL is disabled.
 *   6. Enable the PLL with one feed sequence.
 *   7. Change the CPU Clock Divider setting for the operation with the
 *      PLL. It's critical to do this before connecting the PLL.
 *   8. Wait for the PLL to achieve lock by monitoring the PLOCK bit in the
 *      PLLSTAT register, or using the PLOCK interrupt, or wait for a fixed
 *      time when the input clock to PLL is slow (i.e. 32 kHz). The value of
 *      PLOCK may not be stable when the PLL reference frequency (FREF, the
 *      frequency of REFCLK, which is equal to the PLL input frequency divided
 *      by the pre-divider value) is less than 100 kHz or greater than 20
 *      MHz. In these cases, the PLL may be assumed to be stable after a
 *      start-up time has passed. This time is 500 us when FREF is
 *      greater than 400 kHz and 200 / FREF seconds when FREF is less than
 *      400kHz.
 *   9. Connect the PLL with one feed sequence.
 *
 *   It's very important not to merge any steps above. For example, don't
 *   update the PLLCFG and enable the PLL simultaneously with the same feed
 *   sequence.
 *
 */

/*
 * IMPORTS
 */

#include <stdint.h>
#include "lpc2378.hpp"
#include "init.h"

/*
 * ROUTINES
 */

/*
 * NAME
 *
 *  initPLL
 *
 * DESCRIPTION
 *
 *  This init is specific to the 2300 family of devices.
 *
 *  Initialize PLL (Configured for a 12.000 MHz crystal) to
 *  boost processor clock to 72.000 MHz
 *
 * PARAMETER
 *
 *  none...
 *
 * EXAMPLE
 *
 *  initPLL();
 *
 * NOTES
 *
 *  none...
 *
 */

static void initPLL(void)
{
   /* [1] Check if PLL connected, disconnect if yes. */

   if (pllstat::pllc::read())
   {
      pllcon::plle::write(1);
      pllfeed::write(0xaa);
      pllfeed::write(0x55);
   }

   /* [2] Disable the PLL once it has been disconnected. */

   pllcon::both::write(0);
   pllfeed::write(0xaa);
   pllfeed::write(0x55);


   /* Enable the main oscillator */

   scs::oscen::write(1);

   /* Wait until main OSC is usable */

   do {} while (scs::oscstat::read() == 0);

   /* Select the main osc as the PLL clk source. */
   clksrcsel::clksrc::write(1);

   /*
    * NOTES:
    *
    * Set multiplier and divider values.
    *
    *  PLLCFG = ((N - 1) << 16) + (M - 1)
    *
    *  F_cco = (2 * M *F_in)/N
    *      M = 12, N = 1, F_in = 12.000 MHz -> F_cco = 288.000 MHz
    *
    */
   static const int M = 12;
   static const int N = 1;
   pllcfg::msel::write(M - 1);
   pllcfg::nsel::write(N - 1);
   pllfeed::write(0xaa);
   pllfeed::write(0x55);
    
   /* Enable the PLL. */
   pllcon::plle::write(1);
   pllfeed::write(0xaa);
   pllfeed::write(0x55);
    
   /* Divide F_cco down to get the CCLK output. (288 / 6 = 48) */
   cclkcfg::cclksel::write(6-1);
    
   /* Wait for the PLL to lock to set frequency */
    
   do {} while (pllstat::plock::read() == 0);
   do {} while (
      pllstat::msel::read() != M - 1
         &&
      pllstat::nsel::read() != N - 1
   );
    
   /* Enable and connect the PLL as the clock source */
   pllcon::plle::write(1);
   pllcon::pllc::write(1);
   pllfeed::write(0xaa);
   pllfeed::write(0x55);
    
   /* Check connect bit status and wait for connection. */
   do {} while (pllstat::pllc::read() == 0);
}

/*
 * NAME
 *
 * initMAM
 *
 * DESCRIPTION
 *
 * enable the MAM accelerator and sets number of clocks used for
 * flash memory fetch.
 *
 * PARAMETER
 *
 * none...
 *
 * EXAMPLE
 *
 *   initMAM();
 *
 * NOTES
 *
 *  none...
 *
 */

static void initMAM(void)
{
   mamcr::mam_mode_control::write(0);
   mamtim::mam_fetch_cycle_timing::write(3);
   mamcr::mam_mode_control::write(1);
}

/*
 * NAME
 *
 * initPCLK
 *
 * DESCRIPTION
 *
 * Set the pclk for each peripheral. The default PDIV_4, but we do that
 * explicitly here to make it easier to change them later.
 *
 * PARAMETER
 *
 * none...
 *
 * EXAMPLE
 *
 *   initPCLK();
 *
 * NOTES
 *
 *  none...
 *
 */

static void initPCLK(void)
{
   pclksel0::pclk_uart0::write(1);
   pclksel0::pclk_uart1::write(1);
   pclksel1::pclk_uart2::write(1);
   pclksel1::pclk_uart3::write(1);
}

/*
 * NAME:
 *
 *  initGPIO
 *
 * DESCRIPTION:
 *
 *  sets up the GPIO pins
 *
 * PARAMETERS:
 *
 *  none...
 *
 * RETURN:
 *
 *  none...
 *
 * EXAMPLE:
 *
 *   initGPIO();
 *
 * NOTES:
 *
 *  none...
 *
 */

static void initGPIO(void)
{
    pinsel<0>::port<2>::function::write(1);
    pinsel<0>::port<3>::function::write(1);
    pinsel<10>::port<1>::function::write(0);
    scs::gpiom::write(1);
}

/*
 * NAME:
 *
 *  initHardware
 *
 * DESCRIPTION:
 *
 *  initializes all the hardware components for the UART0 to function.
 *
 * PARAMETERS:
 *
 *  none...
 *
 * RETURN:
 *
 *  none...
 *
 * EXAMPLE:
 *
 *   initHardware();
 *
 * NOTES:
 *
 *  experimental
 *
 */

void initHardware(void)
{
    /*
     * intialize main hardware components
     */
    
    initPLL();
    initMAM();
    initPCLK ();
    initGPIO();
    
    /* intialize specific hardware components for UART0 */
    uart0::bps<115200>();
    uart0::fcr::fifo_enable::write(0);
    
    /* Turn off MCIPWR SD LED (near bottom left corner of LCD) */
    fiodir::led1::write(1);
    fioclr::led1::write(1);
    
    /* MEMMAP Choices are:
    BOOTLOADERMODE      0x00
    USERFLASHMODE       0x01
    USERRAMMODE         0x02
    EXTERNALMEMORYMODE  0x03
    */
    memmap::map::write(1);
}

/*
 * NAME:
 *
 *  handlerDummy
 *
 * DESCRIPTION:
 *
 *  dummy function for the exception vectors
 *
 * PARAMETERS:
 *
 *  none...
 *
 * RETURN:
 *
 *  never returns
 *
 * EXAMPLE:
 *
 *   n/a
 *
 * NOTES:
 *
 *  none..
 *
 */

void handlerDummy(void)
{
    /* forever */
    while(1) continue;
}

