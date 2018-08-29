.PHONY: all clean run dbg tags tags quisp/% doc quisp/.oppbuildspec .lvimrc

ifneq (${VIRTUAL_ENV},quisp)
$(error Get inside the QUISP virtual environment with `source setenv`)
endif

MODE?=release

MSGFILES:=$(wildcard quisp/*.msg)
CMSGFILES:=${MSGFILES:%.msg=%_m.cc}
HMSGFILES:=${MSGFILES:%.msg=%_m.h}

ifeq (${BATCH},)
QENV:=Qtenv
else
QENV:=Cmdenv
QCONFIG?=Simple_constant_quantum_cost
QCFG:=-c $(QCONFIG)
endif

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
		./quisp -m -u ${QENV} -n . networks/omnetpp.ini ${QCFG}

dbg: quisp/quisp_dbg
	cd quisp && \
		gdb quisp_dbg -ex 'run -m -u ${QENV} -n . networks/omnetpp.ini ${QCFG}'

quisp/%_m.cc quisp/%_m.h: quisp/Makefile
	make -C quisp MODE=${MODE} ${@F}

msg:
	make -C quisp MODE=${MODE} ${CMSGFILES:quisp/%=%} ${HMSGFILES:quisp/%=%}

tags: msg
	find "$$(cd quisp && pwd)" -type f -name '*.cc' -o -name '*.h' -exec 'ctags' '-o' 'tags' '--language-force=c++' '{}' '+'
	test ! -d .git || mv tags .git/.

doc: Doxyfile
	doxygen $<

quisp/.oppbuildspec: quisp/.oppbuildspec.template
	test -f $@ || cp $< $@

.lvimrc: quisp/.oppbuildspec
	test -f $@ || make_lvimrc $$(get_oppbuildspec $<) > $@
