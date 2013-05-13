.ft MT
.bd MR 3

.de bold endbold
\\$3\f[MR]\\$1\fP\\$2
.endbold

.de HEADER
..

.de FOOTER
\l'\\n[.l]u'\h'-\\n[.l]u'
.br
.tl '''%'
..

.de new endnew
.SK
.TITLE
.BLOCKS 0i \\$2
.DS C
.VERBON 22 26 MT
.bold "\\$1"
.VERBOFF
.DE
.endnew

.de delete enddelete
.BLOCKE
.enddelete

.new "C++ Hardware Registers" 2.75i
.DS C
Using compile time techniques to provide guarantees without
sacrificing performance

Ken Smith

kgsmith@uw.edu
.DE
.delete

.new "Overview" 2.75i
.BL
.LI
State of the art in MMIO
.LI
A C++ register model
.LI
Policies
.LI
Performance and benefits
.LE
.delete

.new "The state of the art: macros" 1.5i
.VERBON 22 16 MT



#define REG_VAL_TYPE (volatile uint32_t)
#define REG_TYPE (REG_VAL_TYPE*)
#define DEV_REG ((REG_TYPE)0xffff0000)
.PAUSE

*DEV_REG |= 1;
REG_VAL_TYPE get_val = *DEV_REG;
.VERBOFF
.delete

.new "The state of the art: macros" 1.5i
.BL
.LI
Advantages
.BL
.LI
Lots of people are comfortable with the idiom
.LI
Generates efficient code
.LE
.PAUSE
.LI
Disadvantages
.BL
.LI
Easy to get it wrong
.BL
.LI
Eg., writing to a read-only register compiles and runs
.LE
.LI
Meaning can be opaque
.LE
.LE
.delete

.new "The state of the art: bitfields" 1.5i
.VERBON 22 16 MT



struct  periph_status_reg_t
{
    volatile uint32_t enabled : 1;
    volatile uint32_t flag : 1;
    volatile uint32_t bitrate : 6;
};
.PAUSE

struct periph_status_reg_t* periph_status_reg =
    (struct periph_status_reg_t*) 0xffff0000;
.PAUSE

if (periph_status_reg->enabled)
{
    // react
}
.VERBOFF
.delete

.new "The state of the art: bitfields" 1.5i
.BL
.LI
Advantages
.BL
.LI
More readable than masking / anding / oring to access values
.LI
Also generates efficient code
.LE
.PAUSE
.LI
Disadvantages
.BL
.LI
Not necessarily portable
.LI
You can still accidentally write to a read-only register,
etc.
.LE
.LE
.delete

.new "C++ to the rescue" 2.75i
.BL
.LI
Catch common errors at compile time
.LI
Preserve the readability of bitfields
.LI
Preserve the platform independence of masking / anding /
oring with macros
.LE
.delete

.new "A register model" 0.5i
.VERBON 22 16 MT
template
<
   uint32_t address,
   uint32_t mask,
   uint32_t offset,
   class mutability_policy
>
.PAUSE
struct reg_t
{
   static void write(uint32_t value)
   {
      mutability_policy::write(
         reinterpret_cast<volatile uint32_t*>(address),
         mask, offset, value
      );
   }
.PAUSE

   static uint32_t read()
   {
      return mutability_policy::read(
         reinterpret_cast<volatile uint32_t*>(address),
         mask, offset
      );
   }
};
.VERBOFF
.delete

.new "Mutability policies" 2.75i
.BL
.LI
Mutability policies implement the static read and write
methods
.LI
The way they implement those methods defines the behavior of
the register
.LE
.delete

.new "A read-only policy" 1.75i
.VERBON 22 16 MT
struct ro_t
{

   static uint32_t read(
      volatile uint32_t* reg,
      uint32_t mask,
      uint32_t offset
   )
   {
      return (*reg >> offset) & mask;
   }
};
.VERBOFF
.delete

.new "A read-only register" 2.5i
.VERBON 22 16 MT
struct scs
{
   typedef reg_t<0xe01fc1a0, 1, 6, ro_t> oscstat;
};
.PAUSE

do {} while (scs::oscstat::read() == 0);
.PAUSE

scs::ocsstat::write(1); // doesn't compile
.VERBOFF
.delete

.new "A write-only policy" 1.75i
.VERBON 22 16 MT
struct wo_t
{
   static void write(
      volatile uint32_t* reg,
      uint32_t mask,
      uint32_t offset,
      uint32_t value
   )
   {
      *reg = (value & mask) << offset;
   }
};
.VERBOFF
.delete

.new "A write-only register" 2.5i
.VERBON 22 16 MT
struct fioset
{
   typedef reg_t<0x3fffc018, 1, 21, wo_t> led1;
};
.PAUSE

fioset::led1::write(1);
.PAUSE

uint32_t result = fioset::led1::read(); // doesn't compile
.VERBOFF
.delete

.new "Read-write policy" 1.5i
.VERBON 22 16 MT
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
.VERBOFF
.delete

.new "Exotic policy" 2.75i
.BL
.LI
Keyed Register
.BL
.LI
Every time you write to this register, you have to write a
special value to the most significant byte
.LE
.LE
.delete

.new "A keyed register policy" 1i
.VERBON 22 16 MT
template
<
    uint32_t key_mask,
    uint32_t key_offset,
    uint32_t key_value
>
struct keyed_wo_t
{
    static void write(
        volatile uint32_t* reg,
        uint32_t mask,
        uint32_t offset,
        uint32_t value
    )
    {
        volatile uint32_t tmp = (value & mask) << offset;
.PAUSE
        tmp &= ~(key_mask << key_offset);
.PAUSE
        tmp |= (key_value & key_mask) << key_offset;
.PAUSE
        *reg = tmp;
    }
};
.VERBOFF
.delete

.new "A keyed register" 1.75i
struct sys
{
    typedef reg_t
    <
        0xfffe0080,
        1,
        0,
        keyed_wo_t<0xff, 24, 0xa5>
    > reset;
};

sys::reset::write(1); // writes 0xa5000001
.delete

.new "More uses for policies" 2.75i
.BL
.LI
Log all register accesses
.LI
Gather metrics about register accesses
.LI
Add delay or timing code
.LI
Perform mutual exclusion
.LI
Anything else that makes use of compile-time information
.LE
.delete

.new "Other possibilities" 2i
.BL
.LI
remote_reg_t
.BL
.LI
Access registers of off-chip (SPI, I2C, RS232) devices using
the same idiom
.LE
.LI
Collect and flush several writes at once
.BL
.LI
Use expression templates to collapse a series of
writes into a single write to allow maximum performance
while preserving readability
.LI
Useful in conjunction with off-chip register access to
minimize bus transactions
.LE
.LI
Mock registers for unit testing or desktop simulator
.LE
.delete

.new "Performance" 2.5i
.BL
.LI
Much of the masking / anding / oring is computed at compile
time
.LI
The generated assembly is as fast as using C macros for the
test platform (arm-none-eabi-gcc) when compiling with -Os
.BL
.LI
The compiler collapses and inlines the static function calls
(no impact on the runtime stack)
.LE
.LE
.delete

.new "Limitations" 2.5i
.BL
.LI
Pushback from collaboraters unused to the technique
.LI
You may have to write a lot of register definitions
.LI
Naive use may introduce a performance penalty, esp. with
read-write registers
.BL
.LI
One read-modify-write per field
rather than per register unless you develop the idea
mentioned in "Other possibilities"
.LE
.LE
.delete

.new "Benefits" 1.75i
.BL
.LI
Namespaces or nested structs make it easy to guess register
names.
.BL
.LI
Namespace or template aliases can lessen the typing burden
.LE
.LI
Register access statements look like actions
.LI
It's clear when you're reading or writing
.LI
Compile time safety
.LI
Speed
.LI
Once you get the masking / shifting / anding / oring right
in the policy classes, you don't have to do it again
.LE
.delete

.new "Questions?" 0.75i
.VERBON 22 14 MT
Original paper at
.bold http://yogiken.wordpress.com/2010/02/10/on-publishing/

Code and Slides at
.bold https://github.com/kensmith/embsys

.bold References:
Alexandrescu, 2001. Andrei Alexandrescu, Modern C++ Design,
Addison-Wesley

Goodliffe, 2005. Pete Goodliffe, Register Access in C++:
Exploiting C++'s features for efficient and safe hardware
register access,
.bold http://www.ddj.com/cpp/184401954
.bold http://accu.org/index.php/journals/281

Meyers, 2010. Scott Meyers, Effective C++ in Embedded
Systems,
.bold http://www.aristeia.com/c++-in-embedded.html

Moen, 2010. Martin Moene, One Approach to Using Hardware
Registers in C++,
.bold http://accu.org/index.php/journals/1606

Saks, 1998. Dan Saks, Representing and Manipulating Hardware
in Standard C and C++,
.bold http://www.open-std.org/jtc1/sc22/wg21/docs/ESC_SF_02_465_paper.pdf
.VERBOFF
.delete

.\" vim:tw=60:
