BUILD_PATH = ../bin/

default: test_gcc main_gcc
all: test main

include test/Makefile
include main/Makefile

EMCC = emcc -O2 -I. $(OPTIONS) -Werror -std=c11 -s USE_SDL=2
GCC = gcc -I. $(OPTIONS) -g  -Werror -std=c11

main : main_gcc main_emcc
main_gcc : $(MAIN_OUT)
main_emcc : $(MAIN_OUT:.out=.html)

test : test_gcc test_emcc
test_gcc : $(COMMON_TEST_OUT) 
test_emcc : $(COMMON_TEST_OUT:.out=.html) 

clean : 
	rm -f $(addprefix $(BUILD_PATH), *.o *.out *.js *.html *.bc *.mem *.data *.c *.h *.wasm)

include Makefile_generated


