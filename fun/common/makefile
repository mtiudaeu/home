GCC = gcc -I. -g -DINCLUDE_RUN_TEST -Werror

# USE_SDL=2       : SDL2 Libraries
# USE_SDL_IMAGE=2 :
# --use-preload-plugins : Prevent format error with IMG_load from SDL_Image
EMCC = emcc -O2 -I. -DINCLUDE_RUN_TEST -Werror -s USE_SDL=2 -s USE_SDL_IMAGE=2 --use-preload-plugins

#MDTMP
all: test_graphics.out emcc_test_graphics

# ---- graphics test all ----
test_graphics.out : test_graphics.o context.o text.o shader.o test.o
	$(GCC) test_graphics.o context.o text.o shader.o test.o -o test_graphics.out -lGL -lGLEW -lSDL2 -lSDL2_image
emcc_test_graphics: emcc_test_graphics.bc emcc_context.bc emcc_text.bc emcc_shader.bc emcc_test.bc
	$(EMCC) emcc_test_graphics.bc emcc_context.bc emcc_text.bc emcc_shader.bc emcc_test.bc -o test_graphics.html --preload-file test/assets/text.v.glsl --preload-file test/assets/text.f.glsl --preload-file test/assets/ASCII_tileset.png

test_graphics.o : graphics/test_graphics.c test.o
	$(GCC) -c graphics/test_graphics.c -o test_graphics.o
emcc_test_graphics.bc : graphics/test_graphics.c emcc_test.bc
	$(EMCC) -c graphics/test_graphics.c -o emcc_test_graphics.bc

# ---- graphics text ----
text.o : graphics/text.h graphics/text.c shader.o test.o
	$(GCC) -c graphics/text.c -o text.o
emcc_text.bc : graphics/text.h graphics/text.c emcc_shader.bc emcc_test.bc
	$(EMCC) -c graphics/text.c -o emcc_text.bc

# ---- graphics shader ----
shader.o : graphics/shader.h graphics/shader.c
	$(GCC) -c graphics/shader.c -o shader.o
emcc_shader.bc : graphics/shader.h graphics/shader.c
	$(EMCC) -c graphics/shader.c -o emcc_shader.bc

# ---- graphics context ----
context.o : graphics/context.h graphics/context.c
	$(GCC) -c graphics/context.c -o context.o
emcc_context.bc : graphics/context.h graphics/context.c
	$(EMCC) -c graphics/context.c -o emcc_context.bc

# ---- test ----
test.o : test/test.h test/test.c
	$(GCC) -c test/test.c -o test.o
emcc_test.bc : test/test.h test/test.c
	$(EMCC) -c test/test.c -o emcc_test.bc

# ---- clean ----
clean : 
	rm -f *.o *.out *.js *.html *.bc *.mem *.data





# ---- array ----
#test_array.out : array.o test.o
#	$(GCC) array.o test.o -o test_array.out
#
#array.o : array.h array.c test.o
#	$(GCC) -c array.c -o array.o

