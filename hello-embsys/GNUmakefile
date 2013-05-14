-include config.mk

objs :=
extns := c s cpp
$(foreach extn,$(extns),\
  $(eval $(extn)-srcs := $$(wildcard src/*.$(extn)))\
  $(eval $(extn)-objs := $$(patsubst %.$(extn),%.o,$$($(extn)-srcs)))\
  $(eval $(extn)-objs := $$(patsubst src/%,build/%,$$($(extn)-objs)))\
  $(eval objs += $($(extn)-objs))\
 )
#$(info objs="$(objs)")
deps := $(patsubst %.o,%.d,$(objs))

.PHONY:\
all\
clean\
flash

all\
:build/app.bin build/app.lst

clean\
:\
;rm -Rf build

hide =\
$(strip\
  $(if $(strip $(show)),\
    $(comment do nothing),\
    @echo $1 $(notdir $2) $(notdir $3);\
   )\
 )

flash\
:all\
;$(call hide,flsh,app)\
./flash.py build/app.bin

make-list-name =\
$(strip\
  $(dir $(1))$(patsubst %.o,%.lst,$(notdir $(1)))\
 )

assemble =\
$(strip\
  $(call hide,assm,$1,$2)\
  $(toolchain)-as\
  $(debug)\
  -amhls=$(call make-list-name,$2)\
  -o $2\
  $1\
 )

compile-c =\
$(strip\
  $(call hide,comp,$1,$2)\
  $(toolchain)-gcc\
  -mthumb\
  -c\
  $(debug)\
  $($(strip $(1))-opt)\
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
  $(call postdep,$2)\
 )

compile-c++ =\
$(strip\
  $(call hide,comp,$1,$2)\
  $(toolchain)-g++\
  -std=c++11\
  -mthumb\
  -c\
  $(debug)\
  $($(strip $(1))-opt)\
  -mcpu=arm7tdmi\
  -mthumb-interwork\
  -fomit-frame-pointer\
  -Wall\
  -fverbose-asm\
  -fno-exceptions\
  -fno-rtti\
  -Wa,-amhls=$(call make-list-name,$2)\
  -I inc\
  -MMD\
  -o $2\
  $1\
  $(call postdep,$2)\
 )

postdep =\
$(strip\
  $(eval depname := $(1:.o=.d))\
  $(eval tmpname := $(1:.o=.d.in))\
  && cp -f $(depname) $(tmpname)\
  && sed\
   -e 's/\#.*//'\
   -e 's/^[^:]*: *//'\
   -e 's/ *\\$$//'\
   -e '/^$$/ d'\
   -e 's/$$/ :/'\
   < $(tmpname)\
   >> $(depname)\
  && rm -f $(tmpname)\
 )

link =\
$(strip\
  $(call hide,link,$1,$2)\
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
  $(call hide,copy,$1,$2)\
  $(toolchain)-objcopy\
  -O ihex\
  -S $1\
  $2\
 )
make-bin =\
$(strip\
  $(call hide,copy,$1,$2)\
  $(toolchain)-objcopy\
  -O binary\
  -S $1\
  $2\
 )

make-lst =\
$(strip\
  $(call hide,copy,$1,$2)\
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

build\
:\
;mkdir -p $@

-include $(deps)
