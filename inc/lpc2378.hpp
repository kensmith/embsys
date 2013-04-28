#pragma once

#include "reg_t.hpp"
#include "wo_t.hpp"
#include "ro_t.hpp"
#include "rw_t.hpp"

// TODO use a mask_t type to generate masks internally from
// a specified number of bits
// TODO templatized template aliases instead of template
// structs?
// TODO or using statements instead of templates?

template <int which>
struct pinsel
{
   static_assert(0 <= which && which <= 10, "pin select out of range");

   template <int name>
   struct port
   {
      static_assert(0 <= name && name <= 15, "pin name out of range");
      static_assert(which != 0 || !(12 <= name && name <= 14), "reserved pinsel0 names");

      typedef reg_t<0xe002c000 + which*4, 0x3, name*2, rw_t> function;
   };
};

struct scs
{
   typedef reg_t<0xe01fc1a0, 1, 0, rw_t> gpiom;
   typedef reg_t<0xe01fc1a0, 1, 1, rw_t> emc_reset_disable;
   typedef reg_t<0xe01fc1a0, 1, 2, rw_t> emc_burst_control;

   typedef reg_t<0xe01fc1a0, 1, 3, rw_t> mcipwr_active_level;;
   typedef reg_t<0xe01fc1a0, 1, 4, rw_t> oscrange;
   typedef reg_t<0xe01fc1a0, 1, 5, rw_t> oscen;
   typedef reg_t<0xe01fc1a0, 1, 6, ro_t> oscstat; // note ro_t
};

struct pll
{
   struct stat
   {
      typedef reg_t<0xe01fc088, 0x3fff, 0, ro_t> msel;
      typedef reg_t<0xe01fc088, 0xff, 16, ro_t> nsel;
      typedef reg_t<0xe01fc088, 1, 24, ro_t> plle;
      typedef reg_t<0xe01fc088, 1, 25, ro_t> pllc;
      typedef reg_t<0xe01fc088, 1, 26, ro_t> plock;
   };

   struct con
   {
      typedef reg_t<0xe01fc080, 1, 0, rw_t> plle;
      typedef reg_t<0xe01fc080, 1, 1, rw_t> pllc;
      typedef reg_t<0xe01fc080, 0x3, 0, rw_t> both;
   };

   struct feed
   {
      typedef reg_t<0xe01fc08c, 0xff, 0, wo_t> pllfeed;
   };

   struct cfg
   {
      typedef reg_t<0xe01fc084, 0x3fff, 0, rw_t> msel;
      typedef reg_t<0xe01fc084, 0xff, 16, rw_t> nsel;
   };
};

struct clksrcsel
{
   typedef reg_t<0xe01fc10c, 0x3, 0, rw_t> clksrc;
};

struct cclkcfg
{
   typedef reg_t<0xe01fc104, 0xff, 0, rw_t> cclksel;
};

struct mam
{
   struct cr
   {
      typedef reg_t<0xe01fc000, 0x3, 0, rw_t> mam_mode_control;
   };

   struct tim
   {
      typedef reg_t<0xe01fc004, 0x7, 0, rw_t> mam_fetch_cycle_timing;
   };
};

struct pclk
{
   struct sel0
   {
      typedef reg_t<0xe01fc1a8, 0x3, 0, rw_t> pclk_wdt;
      typedef reg_t<0xe01fc1a8, 0x3, 2, rw_t> pclk_timer0;
      typedef reg_t<0xe01fc1a8, 0x3, 4, rw_t> pclk_timer1;
      typedef reg_t<0xe01fc1a8, 0x3, 6, rw_t> pclk_uart0;
      typedef reg_t<0xe01fc1a8, 0x3, 8, rw_t> pclk_uart1;
      typedef reg_t<0xe01fc1a8, 0x3, 12, rw_t> pclk_pwm1;
      typedef reg_t<0xe01fc1a8, 0x3, 14, rw_t> pclk_i2c0;
      typedef reg_t<0xe01fc1a8, 0x3, 16, rw_t> pclk_spi;
      typedef reg_t<0xe01fc1a8, 0x3, 18, rw_t> pclk_rtc;
      typedef reg_t<0xe01fc1a8, 0x3, 20, rw_t> pclk_ssp1;
      typedef reg_t<0xe01fc1a8, 0x3, 22, rw_t> pclk_dac;
      typedef reg_t<0xe01fc1a8, 0x3, 24, rw_t> pclk_adc;
      typedef reg_t<0xe01fc1a8, 0x3, 26, rw_t> pclk_can1;
      typedef reg_t<0xe01fc1a8, 0x3, 28, rw_t> pclk_can2;
      typedef reg_t<0xe01fc1a8, 0x3, 30, rw_t> pclk_acf;
   };

   struct sel1
   {
      typedef reg_t<0xe01fc1ac, 0x3, 0, rw_t> pclk_bat_ram;
      typedef reg_t<0xe01fc1ac, 0x3, 2, rw_t> pclk_gpio;
      typedef reg_t<0xe01fc1ac, 0x3, 4, rw_t> pclk_pcb;
      typedef reg_t<0xe01fc1ac, 0x3, 6, rw_t> pclk_i2c1;
      typedef reg_t<0xe01fc1ac, 0x3, 10, rw_t> pclk_ssp0;
      typedef reg_t<0xe01fc1ac, 0x3, 12, rw_t> pclk_timer2;
      typedef reg_t<0xe01fc1ac, 0x3, 14, rw_t> pclk_timer3;
      typedef reg_t<0xe01fc1ac, 0x3, 16, rw_t> pclk_uart2;
      typedef reg_t<0xe01fc1ac, 0x3, 18, rw_t> pclk_uart3;
      typedef reg_t<0xe01fc1ac, 0x3, 20, rw_t> pclk_i2c2;
      typedef reg_t<0xe01fc1ac, 0x3, 22, rw_t> pclk_i2s;
      typedef reg_t<0xe01fc1ac, 0x3, 24, rw_t> pclk_mci;
      typedef reg_t<0xe01fc1ac, 0x3, 28, rw_t> pclk_syscon;
   };
};
