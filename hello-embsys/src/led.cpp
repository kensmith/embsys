#include "led.hpp"
#include "lpc2378.hpp"

void led_on()
{
   fio::set::led1::write(1);
}

void led_off()
{
   fio::clr::led1::write(1);
}

void classic_led_on()
{

}

void classic_led_off()
{
}
