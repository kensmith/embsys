#pragma once

#include <word_t.hpp>

template
<
   word_t address,
   word_t mask,
   word_t offset,
   class mutability_policy
>
struct reg_t
{
   static void write(word_t value)
   {
      mutability_policy::write(
         reinterpret_cast<volatile word_t*>(address),
         mask,
         offset,
         value
      );
   }

   static word_t read()
   {
      return mutability_policy::read(
         reinterpret_cast<volatile word_t*>(address),
         mask,
         offset
      );
   }
};
