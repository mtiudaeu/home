CFLAGS = -g -DINCLUDE_RUN_TEST -Werror
#CFLAGS = -g 
CXX = gcc -I. $(CFLAGS)

all: test_array test_graphics

# ---- graphics test all ----
test_graphics : test_graphics.o context.o text.o test.o
	$(CXX) test_graphics.o context.o text.o test.o -o test_graphics -lGL -lSDL2 -lSDL2_image

test_graphics.o : graphics/test_run.c test.o
	$(CXX) -c graphics/test_run.c -o test_graphics.o

# ---- graphics text ----
text.o : graphics/text.h graphics/text.c test.o
	$(CXX) -c graphics/text.c -o text.o

# ---- graphics text ----
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
