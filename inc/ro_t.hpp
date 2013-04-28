#pragma once

#include <word_t.hpp>

struct ro_t
{

   static word_t read(
      volatile word_t* reg,
      word_t mask,
      word_t offset
   )
   {
      return (*reg >> offset) & mask;
   }
};
