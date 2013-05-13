groff-macros := m present
groff-flags := $(addprefix -m,$(groff-macros))
groff := groff $(groff-flags)
target-suffixes := pdf
dont-generate := common.g
groff-sources := $(wildcard *.g)
groff-sources := $(filter-out $(dont-generate),$(groff-sources))
targets := $(groff-sources:g=)
targets := $(addsuffix $(target-suffixes),$(targets))
pdf-viewer := acroread

$(foreach s,$(groff-sources), \
  $(if $($(s)-flags), \
    , \
    $(info Using default flags for $(s).) \
    $(eval \
      $(s)-flags := $(default-flags) \
     ) \
   ) \
 )

.PHONY: all 
all \
  : $(targets) \
    $(if $(strip $(vp)),vp) \

%.ps \
  : %.pps \
  ; presentps < $< > $@

%.pps \
  : %.g $(wildcard common.g) \
  ; $(strip $(groff) $($(<)-flags) $< > $@)

%.pdf \
  : %.ps \
  ; ps2pdf $< $@

.PHONY: vp
vp \
  : $(targets) \
  ;$(if $(strip $(vp)), \
     ($(pdf-viewer) $(vp).pdf > /dev/null 2>&1 &), \
     $(error make vp=basename) \
    )

clean-targets := $(wildcard $(targets))
.PHONY: clean
clean \
  : \
  ; $(if $(clean-targets), \
      rm -f $(clean-targets) \
     )
