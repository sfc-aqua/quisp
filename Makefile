.PHONY: all clean run quisp/% doc quisp/.oppbuildspec .lvimrc

ifneq (${VIRTUAL_ENV},quisp)
$(error Get inside the QUISP virtual environment with `source setenv`)
endif

MODE?=release

all: quisp/Makefile
	make -C quisp MODE=${MODE} $@

clean: quisp/Makefile
	make -C quisp MODE=${MODE} $@
	rm $<

quisp/quisp: quisp/Makefile
	make -C quisp MODE=release all

quisp/quisp_dbg: quisp/Makefile
	make -C quisp MODE=debug all

quisp/Makefile: quisp/makemakefiles quisp/.oppbuildspec
	make -C quisp -f makemakefiles all MMOPT="$$(get_oppbuildspec quisp/.oppbuildspec)"

run: quisp/quisp
	cd quisp && \
		./quisp -m -u Qtenv -n . networks/omnetpp.ini

doc: Doxyfile
	doxygen $<

quisp/.oppbuildspec: quisp/.oppbuildspec.template
	test -f $@ || cp $< $@

.lvimrc: quisp/.oppbuildspec
	test -f $@ || make_lvimrc $$(get_oppbuildspec $<) > $@
