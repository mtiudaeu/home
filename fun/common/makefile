CFLAGS = -g -DINCLUDE_RUN_TEST
#CFLAGS = -g 
CXX = gcc -I. $(CFLAGS)

all: test_array test_text

# ---- graphics text ----
test_text : text.o test.o
	$(CXX) text.o test.o -o test_text -lGL -lSDL2 -lSDL2_image

text.o : graphics/text.h graphics/text.c test.o
	$(CXX) -c graphics/text.c 

# ---- array ----
test_array : array.o test.o
	$(CXX) array.o test.o -o test_array

array.o : array.h array.c test.o
	$(CXX) -c array.c 

# ---- test ----
test.o : test/test.h test/test.c
	$(CXX) -c test/test.c

# ---- clean ----
clean : 
	rm *.o test_array test_text
