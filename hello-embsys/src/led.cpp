#include "led.hpp"
#include "lpc2378.hpp"
#include "lpc2378.h"

void new_led_on()
{
   fioset::led1::write(1);
}

void classic_led_on()
{
   VOLATILE32(FIO0SET) |= 1<<21;
}

void new_led_off()
{
   fioclr::led1::write(1);
}

void classic_led_off()
{
   VOLATILE32(FIO0CLR) |= 1<<21;
}
