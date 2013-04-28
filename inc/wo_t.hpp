#pragma once

#include <word_t.hpp>

struct wo_t
{
   static void write(
      volatile word_t* reg,
      word_t mask,
      word_t offset,
      word_t value
   )
   {
      *reg = (value & mask) << offset;
   }
};
