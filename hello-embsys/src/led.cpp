#include "led.hpp"
#include "lpc2378.hpp"
#include "lpc2378.h"

void new_led_on()
{
   fio::set::led1::write(1);
}

void new_led_off()
{
   fio::clr::led1::write(1);
}

void classic_led_on()
{
   VOLATILE32(FIO0SET) |= 1<<21;
}

void classic_led_off()
{
   VOLATILE32(FIO0CLR) |= 1<<21;
}
