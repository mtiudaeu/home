LDLIBS=-lglut -lGLEW -lGL -lSDL2 -lm

all: gcc emcc test

gcc: gcc_shader_utils.o
	gcc shader_utils.o triangle.c $(LDLIBS) -o triangle.out
gcc_shader_utils.o :
	gcc -c shader_utils.c

emcc: emcc_shader_utils.bc
	emcc -O2 emcc_shader_utils.bc triangle.c -s USE_SDL=2 -o triangle.html --preload-file triangle.f.glsl --preload-file triangle.v.glsl
emcc_shader_utils.bc :
	emcc -O2 -s USE_SDL=2 -c shader_utils.c -o emcc_shader_utils.bc

test: test_include.bc
	emcc -O2 test_include.bc test_main.c -o test.html --preload-file triangle.f.glsl --preload-file triangle.v.glsl

test_include.bc:
	emcc -O2 -c test_include.c -o test_include.bc

clean:
	rm -f *.o *.out *.js *.html *.bc *.mem *.data

.PHONY: all clean gcc emcc
