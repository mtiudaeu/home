CFLAGS = -g -DINCLUDE_RUN_TEST -Werror
#CFLAGS = -g 
CXX = gcc -I. $(CFLAGS)

all: test_array test_graphics

# ---- graphics test all ----
test_graphics : test_graphics.o context.o text.o shader.o test.o
	$(CXX) test_graphics.o context.o text.o shader.o test.o -o test_graphics -lGL -lGLEW -lSDL2 -lSDL2_image

test_graphics.o : graphics/test_run.c test.o
	$(CXX) -c graphics/test_run.c -o test_graphics.o

# ---- graphics text ----
text.o : graphics/text.h graphics/text.c shader.o test.o
	$(CXX) -c graphics/text.c -o text.o

# ---- graphics shader ----
shader.o : graphics/shader.h graphics/shader.c
	$(CXX) -c graphics/shader.c -o shader.o

# ---- graphics context ----
context.o : graphics/context.h graphics/context.c
	$(CXX) -c graphics/context.c -o context.o

# ---- array ----
test_array : array.o test.o
	$(CXX) array.o test.o -o test_array

array.o : array.h array.c test.o
	$(CXX) -c array.c -o array.o

# ---- test ----
test.o : test/test.h test/test.c
	$(CXX) -c test/test.c -o test.o

# ---- clean ----
clean : 
	rm *.o test_array test_graphics
