-include config.mk

objs :=
extns := c s cpp
$(foreach extn,$(extns),\
  $(eval $(extn)-srcs := $$(wildcard src/*.$(extn)))\
  $(eval $(extn)-objs := $$(patsubst %.$(extn),%.o,$$($(extn)-srcs)))\
  $(eval $(extn)-objs := $$(patsubst src/%,build/%,$$($(extn)-objs)))\
  $(eval objs += $($(extn)-objs))\
 )
deps := $(patsubst %.o,%.d,$(objs))

.PHONY:\
all

all\
:build/app.bin build/app.lst

make-list-name =\
$(strip\
  $(dir $(1))$(patsubst %.o,%.lst,$(notdir $(1)))\
 )

assemble =\
$(strip\
  $(toolchain)-as\
  $(debug)\
  -amhls=$(call make-list-name,$2)\
  -o $2\
  $1\
 )

compile-c =\
$(strip\
  $(toolchain)-gcc\
  -c\
  $(debug)\
  $(opt)\
  -mcpu=arm7tdmi\
  -mthumb-interwork\
  -fomit-frame-pointer\
  -Wall\
  -Wstrict-prototypes\
  -fverbose-asm\
  -Wa,-amhls=$(call make-list-name,$2)\
  -I inc\
  -MMD\
  -o $2\
  $1\
  ;\
  $(call postdep,$2)\
 )

compile-c++ =\
$(strip\
  $(toolchain)-g++\
  -c\
  $(debug)\
  $(opt)\
  -mcpu=arm7tdmi\
  -mthumb-interwork\
  -fomit-frame-pointer\
  -Wall\
  -Wstrict-prototypes\
  -fverbose-asm\
  -Wa,-amhls=$(call make-list-name,$2)\
  -I inc\
  -MMD\
  -o $2\
  $1\
  ;\
  $(call postdep,$2)\
 )

postdep =\
$(strip\
  $(eval depname := $(1:.o=.d))\
  sed\
   -e 's/\#.*//'\
   -e 's/^[^:]*: *//'\
   -e 's/ *\\$$//'\
   -e '/^$$/ d'\
   -e 's/$$/ :/'\
   < $(depname)\
   >> $(depname)\
 )

link =\
$(strip\
  $(toolchain)-g++\
  -mcpu=arm7tdmi\
  -nostartfiles\
  -T prj/lpc2378_flash.ld\
  -Wl,-Map=build/app.map,--cref,--no-warn-mismatch\
  -o $2\
  $1\
 )

make-hex =\
$(strip\
  $(toolchain)-objcopy\
  -O ihex\
  -S $1\
  $2\
 )
make-bin =\
$(strip\
  $(toolchain)-objcopy\
  -O binary\
  -S $1\
  $2\
 )

make-lst =\
$(strip\
  $(toolchain)-objdump\
  -dSst $1\
  > $2\
 )

build/%.o\
:src/%.s\
 $(MAKEFILE_LIST)\
|build\
;$(call assemble,$<,$@)

build/%.o\
:src/%.c\
 $(MAKEFILE_LIST)\
|build\
;$(call compile-c,$<,$@)

build/%.o\
:src/%.cpp\
 $(MAKEFILE_LIST)\
|build\
;$(call compile-c++,$<,$@)

build/app.elf\
:$(objs)\
;$(call link,$^,$@)

build/app.hex\
:build/app.elf\
;$(call make-hex,$<,$@)

build/app.bin\
:build/app.elf\
;$(call make-bin,$<,$@)

build/app.lst\
:build/app.elf\
;$(call make-lst,$<,$@)

build/postdep.sh\
:$(MAKEFILE_LIST)\
;

build\
:\
;mkdir -p $@

-include $(deps)
