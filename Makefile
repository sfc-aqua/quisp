OPP_BUILD_SPEC_FILE=./quisp/.oppbuildspec

# if INCLUDES env is not set and there's .oppbuildspec file, 
# it attempts to load INCLUDES var from .oppbuildspec file.
ifeq (,$(INCLUDES))
ifneq (,$(wildcard $(OPP_BUILD_SPEC_FILE)))
OPP_BUILD_SPEC=$(shell cat $(OPP_BUILD_SPEC_FILE))
INCLUDES=$(filter -I%,$(OPP_BUILD_SPEC))
endif
endif

ifeq (,$(INCLUDES))
$(error 'no INCLUDES specified. set up the project with OMNetIDE++ or provide INCLUDES env var')
endif

.PHONY: all tidy format ci makefile-exe makefile-lib checkmakefile

all: makefile-exe
	$(MAKE) -C quisp -j

ci: quisp/Makefile
	$(MAKE) -C quisp ci

format: quisp/Makefile
	$(MAKE) -C quisp format

tidy: quisp/Makefile
	$(MAKE) -C quisp format

makefile-exe:
	cd quisp && opp_makemake -f --deep -O out $(INCLUDES)

makefile-so: 
	cd quisp && opp_makemake -f --deep -O out $(INCLUDES) --make-so

checkmakefile:
	@if [ ! -f $(QUISP_MAKEFILE) ]; then \
	echo; \
	echo '===================================================================================================='; \
	echo 'quisp/Makefile does not exist. Please use "make makefile-exe" or "make makefile-lib" to generate it!'; \
	echo '===================================================================================================='; \
	echo; \
	exit 1; \
	fi

