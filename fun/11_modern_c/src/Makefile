BUILD_PATH = ../bin/

default: test_gcc
all: test

include test/Makefile

EMCC = emcc -O2 -I. $(OPTIONS) -Werror -std=c11 
GCC = gcc -I. $(OPTIONS) -g  -Werror -std=c11


test : test_gcc test_emcc
test_gcc : $(COMMON_TEST_OUT) 
test_emcc : $(COMMON_TEST_OUT:.out=.html) 

clean : 
	rm -f $(addprefix $(BUILD_PATH), *.o *.out *.js *.html *.bc *.mem *.data *.c *.h *.wasm)

include Makefile_generated


