OPP_BUILD_SPEC_FILE=./quisp/.oppbuildspec

# if INCLUDES env is not set and there's .oppbuildspec file, 
# it attempts to load INCLUDES var from .oppbuildspec file.
ifeq (,$(INCLUDES))
ifneq (,$(wildcard $(OPP_BUILD_SPEC_FILE)))

# check GNU Make version
version_list := $(subst ., ,$(MAKE_VERSION))
major_version := $(word 1, $(version_list))
minor_version := $(word 2, $(version_list))
ifeq ($(major_version),3)
$(error 'use GNU Make 4.2 or later, your version is $(MAKE_VERSION) or pass INCLUDES env var')
else
ifneq (,$(filter $(minor_version), 0 1))
$(error '1use GNU Make 4.2 or later, your version is $(MAKE_VERSION) or pass INCLUDES env var')
endif
endif
# here need GNU Make 4.2 or later
# see also https://lists.gnu.org/archive/html/info-gnu/2016-05/msg00013.html
OPP_BUILD_SPEC=$(file < $(OPP_BUILD_SPEC_FILE))
INCLUDES=$(filter -I%,$(OPP_BUILD_SPEC))
endif
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

