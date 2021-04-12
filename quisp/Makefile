#
# OMNeT++/OMNEST Makefile for $(LIB_PREFIX)quisp
#
# This file was generated with the command:
#  opp_makemake -f --mode debug --deep -O out -I/usr/local/share/eigen3 -I/usr/local/include/eigen3 -I/usr/include/eigen3 -I. --make-so
#

# Name of target to be created (-o option)
TARGET = $(LIB_PREFIX)quisp$(D)$(SHARED_LIB_SUFFIX)
TARGET_DIR = .

# C++ include paths (with -I)
INCLUDE_PATH = -I/usr/local/share/eigen3 -I/usr/local/include/eigen3 -I/usr/include/eigen3 -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/channels/QuantumChannel.o \
    $O/modules/dummyModule.o \
    $O/modules/Application/Application.o \
    $O/modules/Common/Queue.o \
    $O/modules/Common/Router.o \
    $O/modules/PhysicalConnection/BSA/BellStateAnalyzer.o \
    $O/modules/PhysicalConnection/BSA/HoMController.o \
    $O/modules/PhysicalConnection/EPPS/EntangledPhotonPairSource.o \
    $O/modules/PhysicalConnection/EPPS/SPDC_Controller.o \
    $O/modules/QNIC/PhotonicSwitch/PhotonicSwitch.o \
    $O/modules/QNIC/StationaryQubit/StationaryQubit.o \
    $O/modules/QRSA/ConnectionManager/ConnectionManager.o \
    $O/modules/QRSA/HardwareMonitor/HardwareMonitor.o \
    $O/modules/QRSA/RealTimeController/RealTimeController.o \
    $O/modules/QRSA/RoutingDaemon/RoutingDaemon.o \
    $O/modules/QRSA/RuleEngine/RuleEngine.o \
    $O/rules/Action.o \
    $O/rules/Clause.o \
    $O/rules/Condition.o \
    $O/rules/example.o \
    $O/rules/Rule.o \
    $O/rules/RuleSet.o \
    $O/tests/modules/work/Application/test.o \
    $O/classical_messages_m.o \
    $O/PhotonicQubit_m.o

# Message files
MSGFILES = \
    classical_messages.msg \
    PhotonicQubit.msg

# SM files
SMFILES =

# Default mode (-M option); can be overridden with make MODE=debug (or =release)
ifndef MODE
MODE = debug
endif

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIBS = -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) $(IMPORT_DEFINES)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# inserted from file 'makefrag':
CXXFLAGS = -std=c++14

# you can pass the file path you want to check as SRCS environment variable. see the example below.
# $ SRCS=./quisp/modules/Application.cc make tidy # checks only Application.cc
# $ make tidy # checks all sources
SRCS?=./modules/*.cc ./rules/*.cc
HEADERS=./modules/*.h ./rules/*.h

default: all

format:
	clang-format -i $(SRCS) $(HEADERS)

tidy:
	clang-tidy -header-filter="./quisp/(rules|modules)/.*.h" $(SRCS) -- $(COPTS:-I.=-I./quisp)

ci: msgheaders
	@clang-format $(SRCS) $(HEADERS) -output-replacements-xml | grep -c "<replacement " -q ; if [ $$? -ne 1 ]; then echo "error: run make format and then push it again"; exit 1; fi
	@clang-tidy -warnings-as-errors="*" -header-filter="./(rules|modules)/.*.h" $(SRCS) -- $(COPTS:-I.=-I./quisp)

# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/% :: $O/%
	@mkdir -p $(TARGET_DIR)
	$(Q)$(LN) $< $@
ifeq ($(TOOLCHAIN_NAME),clangc2)
	$(Q)-$(LN) $(<:%.dll=%.lib) $(@:%.dll=%.lib)
endif

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile $(CONFIGFILE)
	@$(MKPATH) $O
	@echo Creating shared library: $@
	$(Q)$(SHLIB_LD) -o $O/$(TARGET) $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS)
	$(Q)$(SHLIB_POSTPROCESS) $O/$(TARGET)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE) | msgheaders smheaders
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc -MD -MP -MF $O/$(basename $<)_m.h.d $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning $(TARGET)
	$(Q)-rm -rf $O
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET)
	$(Q)-rm -f $(TARGET_DIR)/$(TARGET:%.dll=%.lib)
	$(Q)-rm -f $(call opp_rwildcard, . , *_m.cc *_m.h *_sm.cc *_sm.h)

cleanall:
	$(Q)$(MAKE) -s clean MODE=release
	$(Q)$(MAKE) -s clean MODE=debug
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

# include all dependencies
-include $(OBJS:%=%.d) $(MSGFILES:%.msg=$O/%_m.h.d)
