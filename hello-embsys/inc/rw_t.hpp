#pragma once

#include <word_t.hpp>
#include <ro_t.hpp>

struct rw_t : ro_t
{
   static void write(
      volatile word_t* reg,
      word_t mask,
      word_t offset,
      word_t value
   )
   {
      *reg =
         (*reg & ~(mask << offset))
         |
         ((value & mask) << offset);
   }
};
