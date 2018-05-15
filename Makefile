.PHONY: all clean run quisp/%

MODE?=release

all clean:
	make -C quisp MODE=${MODE} $@

quisp/quisp:
	make -C quisp MODE=release all

quisp/quisp_dbg:
	make -C quisp MODE=debug all

run: quisp/quisp
	cd quisp && \
		./quisp -m -u Qtenv -n . networks/omnetpp.ini
