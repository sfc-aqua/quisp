SRCS=./quisp/modules/*.cc ./quisp/modules/*.h ./quisp/rules/*.cc ./quisp/rules/*.h

format:
	clang-format -i $(SRCS)

ci:
	@clang-format $(SRCS) -output-replacements-xml | grep -c "<replacement " -q ; if [ $$? -ne 1 ]; then echo "error: run make format and then push it again"; exit 1; fi
