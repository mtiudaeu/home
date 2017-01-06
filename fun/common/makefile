CFLAGS = -g -DINCLUDE_RUN_TEST -Werror
#CFLAGS = -g 
GCC = gcc -I. $(CFLAGS)
EMCC = emcc -O2 -I.

#MDTMP
all: test_graphics.out emcc_test.bc emcc_context.bc emcc_shader.bc

# ---- graphics test all ----
test_graphics.out : test_graphics.o context.o text.o shader.o test.o
	$(GCC) test_graphics.o context.o text.o shader.o test.o -o test_graphics.out -lGL -lGLEW -lSDL2 -lSDL2_image

test_graphics.o : graphics/test_graphics.c test.o
	$(GCC) -c graphics/test_graphics.c -o test_graphics.o
emcc_test_graphics.bc : graphics/test_graphics.c test.o
	$(EMCC) -O2 -s USE_SDL=2 -c graphics/test_graphics.c -o emcc_test_graphics.bc

# ---- graphics text ----
text.o : graphics/text.h graphics/text.c shader.o test.o
	$(GCC) -c graphics/text.c -o text.o
emcc_text.bc : graphics/text.h graphics/text.c shader.o test.o
	$(EMCC) -O2 -s USE_SDL=2 -c graphics/text.c -o emcc_text.bc

# ---- graphics shader ----
shader.o : graphics/shader.h graphics/shader.c
	$(GCC) -c graphics/shader.c -o shader.o
emcc_shader.bc : graphics/shader.h graphics/shader.c
	$(EMCC) -O2 -s USE_SDL=2 -c graphics/shader.c -o emcc_shader.bc

# ---- graphics context ----
context.o : graphics/context.h graphics/context.c
	$(GCC) -c graphics/context.c -o context.o
emcc_context.bc : graphics/context.h graphics/context.c
	$(EMCC) -O2 -s USE_SDL=2 -c graphics/context.c -o emcc_context.bc

# ---- test ----
test.o : test/test.h test/test.c
	$(GCC) -c test/test.c -o test.o
emcc_test.bc : test/test.h test/test.c
	$(EMCC) -O2 -c test/test.c -o emcc_test.bc

# ---- clean ----
clean : 
	rm -f *.o *.out *.js *.html *.bc *.mem *.data





# ---- array ----
#test_array.out : array.o test.o
#	$(GCC) array.o test.o -o test_array.out
#
#array.o : array.h array.c test.o
#	$(GCC) -c array.c -o array.o

