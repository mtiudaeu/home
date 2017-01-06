CFLAGS = -g -DINCLUDE_RUN_TEST -Werror
#CFLAGS = -g 
GCC = gcc -I. $(CFLAGS)
EMCC = emcc -O2 -I.

#MDTMP
all: test_graphics emcc_test.bc emcc_context.bc

# ---- graphics test all ----
test_graphics : test_graphics.o context.o text.o shader.o test.o
	$(GCC) test_graphics.o context.o text.o shader.o test.o -o test_graphics -lGL -lGLEW -lSDL2 -lSDL2_image

test_graphics.o : graphics/test_graphics.c test.o
	$(GCC) -c graphics/test_graphics.c -o test_graphics.o

# ---- graphics text ----
text.o : graphics/text.h graphics/text.c shader.o test.o
	$(GCC) -c graphics/text.c -o text.o

# ---- graphics shader ----
shader.o : graphics/shader.h graphics/shader.c
	$(GCC) -c graphics/shader.c -o shader.o

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
	rm *.o test_array test_graphics




# ---- array ----
#test_array : array.o test.o
#	$(GCC) array.o test.o -o test_array
#
#array.o : array.h array.c test.o
#	$(GCC) -c array.c -o array.o

