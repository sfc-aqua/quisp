include ./quisp/Makefile


# you can pass the file path you want to check as SRCS environment variable. see the example below.
# $ SRCS=./quisp/modules/Application.cc make tidy # checks only Application.cc
# $ make tidy # checks all sources
SRCS?=./quisp/modules/*.cc ./quisp/rules/*.cc 
HEADERS=./quisp/modules/*.h ./quisp/rules/*.h

tidy:
	clang-tidy -header-filter="./quisp/(rules|modules)/.*.h" $(SRCS) -- $(COPTS:-I.=-I./quisp)

format:
	clang-format -i $(SRCS) $(HEADERS)

ci: 
	@make -C ./quisp msgheaders
	@clang-format $(SRCS) $(HEADERS) -output-replacements-xml | grep -c "<replacement " -q ; if [ $$? -ne 1 ]; then echo "error: run make format and then push it again"; exit 1; fi
	@clang-tidy -warnings-as-errors="*" -header-filter="./quisp/(rules|modules)/.*.h" $(SRCS) -- $(COPTS:-I.=-I./quisp)
