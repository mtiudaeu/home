BUILD_PATH = ../bin/

all: slim test

include test/Makefile
include tetris/Makefile

EMCC = emcc -O2 -I. $(OPTIONS) -Werror -std=c11 -s USE_SDL=2 -s USE_SDL_IMAGE=2
GCC = gcc -I. $(OPTIONS) -g  -Werror -std=c11


slim: gcc_targets emcc_targets
gcc_targets : $(TETRIS_OUT)
emcc_targets : $(TETRIS_OUT:.out=.html)

test : test_gcc test_emcc
test_gcc : $(COMMON_TEST_OUT) 
test_emcc : $(COMMON_TEST_OUT:.out=.html) 

clean : 
	rm -f $(addprefix $(BUILD_PATH), *.o *.out *.js *.html *.bc *.mem *.data *.c *.h *.wasm)

include Makefile_generated


