QUISP_MAKEFILE = "./quisp/Makefile"

.PHONY: all tidy format ci makefile-exe makefile-lib checkmakefile googletest clean test coverage coverage-report help

all: makefile-exe
	$(MAKE) -C quisp -j$(nproc)

run-module-test: lib
	cd module_tests && ./runtest

run-unit-test: lib googletest
	$(MAKE) -C quisp run-unit-test

test: run-module-test run-unit-test

exe: makefile-exe
	$(MAKE) -C quisp -j$(nproc)

lib: makefile-lib
	$(MAKE) -C quisp -j$(nproc)

msgheaders: checkmakefile
	$(MAKE) -C quisp msgheaders

format-ci: 
	$(MAKE) -C quisp format-ci

format: quisp/Makefile
	$(MAKE) -C quisp format

tidy: quisp/Makefile
	$(MAKE) -C quisp tidy

googletest/CMakeLists.txt:
	git submodule update --init

googletest/build: googletest/CMakeLists.txt
	mkdir -p googletest/build && cd googletest/build && cmake .. -G "Unix Makefiles"

googletest/build/lib: googletest/build
	make -C googletest/build

googletest: googletest/build/lib

eigen/CMakeLists.txt:
	git submodule update --init

eigen: eigen/CMakeLists.txt

makefile-exe: eigen
	cd quisp && opp_makemake -f --deep -O out -i ./makefrag

makefile-lib: eigen
	cd quisp && opp_makemake -f --deep -O out -i ./makefrag -M debug  --make-so

clean:
	@if [ -f "$(QUISP_MAKEFILE)" ]; then \
		$(MAKE) -C quisp clean; \
	fi
	$(RM) quisp/Makefile quisp/quisp quisp/quisp_dbg quisp/run_unit_test quisp/libquisp*
	$(RM) -r quisp/out
	$(RM) -rf quisp/coverage* quisp/default.profraw quisp/lcov.info

distclean:
	git submodule deinit --all -f
	make clean

coverage: makefile-lib
	$(MAKE) -C quisp lcov.info

coverage-report: makefile-lib
	$(MAKE) -C quisp/ coverage/index.html

checkmakefile:
	@if [ ! -f "$(QUISP_MAKEFILE)" ]; then \
	echo; \
	echo '===================================================================================================='; \
	echo 'quisp/Makefile does not exist. Please use "make makefile-exe" or "make makefile-lib" to generate it!'; \
	echo '===================================================================================================='; \
	echo; \
	exit 1; \
	else \
	echo 'quisp/Makefile exists.'; \
	fi

help:
	@echo; \
	echo '===================================================================================================='; \
	echo 'Usage: make [target]'; \
	echo '===================================================================================================='; \
	echo; \
	echo 'Available targets:'; \
	echo '  exe                 build the executable quisp/quisp'; \
	echo '  lib                 build the library quisp/libquisp{_dbg}.{dylib,so}'; \
	echo '  clean               remove objcet files, executables and libraries'; \
	echo '  distclean           remove everything includes submoduled components'; \
	echo '  run-unit-test       build unit tests and run it'; \
	echo '  run-module-test     build modele tests(opp_test) and run it'; \
	echo '  coverage            generate coverage as quisp/lcov.info'; \
	echo '  coverage-report     generate html coverage report at quisp/coverage/index.html'; \
	echo '  format              run clang-format on the source files'; \
	echo '  tidy                run clang-tidy on the source files to do static analysis'; \

