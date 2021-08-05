# check that we are on a 64-bit OS
ifneq (64,$(shell getconf LONG_BIT))
    $(error CSTools will only run on a 64-bit Linux operating system)
endif

# must specify make target
all: test
	@true

notest:
	@true

.PHONY: all test notest clean

clean:
	@true

test:
	-@bash bin/run-tests

