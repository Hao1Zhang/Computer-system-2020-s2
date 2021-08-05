# must specify make target
all: test
	@true

notest:
	@true

.PHONY: all test notest clean

clean:
	rm -f *.out ALU/*.out

test:
	-@bash bin/run-tests

