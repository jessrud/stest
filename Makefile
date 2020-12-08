CC=clang
CFLAGS=--std=c89 -Wall -Wextra -pedantic -ggdb3

.PHONY: test_header test_module clean

test_header:
	$(CC) example.c -o test_example -DTESTING $(CFLAGS)
	./test_example

test_module: stest.o
	$(CC) -c example.c -o test_example.o -DTESTING -DSTEST_EXTERN $(CFLAGS)
	$(CC) test_example.o stest.o -o test_example
	./test_example

# a little goofyness is required to get modern compilers to not try compiling
# this as a PCH
stest.o: stest.h
	cp stest.h stest.c
	$(CC) -c stest.c -o stest.o $(CFLAGS)
	rm -f stest.c

clean:
	rm -f test_example
	rm -f *.o
