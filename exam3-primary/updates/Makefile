# check that we are on a 64-bit OS
ifneq (64,$(shell getconf LONG_BIT))
    $(error CSTools will only run on a 64-bit Linux operating system)
endif

# look for a suitable compiler to use if CSCOMPILER is not already set
# if CSCOMPILER is set, just trust it
ifeq (x$(CSCOMPILER),x)
    Compiler=$(shell bash bin/Compiler-check.bash)
    ifeq (,$(Compiler))
        $(info Please set environment variable CSCOMPILER to the name of your C++ compiler.)
        $(error Cannot find a suitable C++ compiler.)
    else
        export CXX=$(Compiler)
    endif
else
    $(info CSCOMPILER is set to $(CXX))
    export CXX=$(CSCOMPILER)
endif

# set CS_ARCH for the OS are we running on
System:=$(shell test -f /usr/bin/uname && /usr/bin/uname -s)

# MacOS is reported as Darwin
ifeq (Darwin,$(System))
    export CS_ARCH=macos
else
	THIS_OS:=$(shell test -f /etc/os-release && (grep "^ID=" /etc/os-release | sed 's/ID="\([^"]*\).*/\1/'))
	THIS_OSV:=$(shell test -f /etc/os-release && (grep "^VERSION_ID=" /etc/os-release | sed 's/VERSION_ID="\([^\."]*\).*/\1/'))

    # CATS is currently RHEL7.7
    ifeq (rhel7,$(THIS_OS)$(THIS_OSV))
        export CS_ARCH=cats

    # CentOS7 is close enough RHEL7
    else ifeq (centos7,$(THIS_OS)$(THIS_OSV))
        export CS_ARCH=cats

    # assume everything else is equiv to CentOS 8 for now
    else
        export CS_ARCH=centos8
    endif
endif

# C++ 17 just in case
CXXFLAGS=--std=c++17 -I. -Iincludes -Wall

# must specify make target
all: test 

notest: parser

.PHONY: parser

# testing student code
test: test-parser 

test-parser: parser
	@bash bin/run-tests parser

# testing "working" code
test-working: test-working-parser

test-working-parser:
	@bash bin/run-tests working-parser

# add missing expected test outputs
test-add: test-add-Pxml

test-add-Pxml:
	@bash bin/run-tests add-Pxml quiet

# regenerate all expected test outputs
test-new: test-new-Pxml

test-new-Pxml:
	@bash bin/run-tests new-Pxml quiet

clean:
	rm -f lib/*/parser

parser: lib/$(CS_ARCH)/parser

lib/$(CS_ARCH)/parser: parser.cpp lib/$(CS_ARCH)/lib.a
	${CXX} ${CXXFLAGS} -o $@ $^
