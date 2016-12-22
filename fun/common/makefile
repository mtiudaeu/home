CFLAGS = -g -DINCLUDE_RUN_TEST
CXX = gcc $(CFLAGS)

all: test_array

# ---- array ----
test_array : test_array.o array.o test.o
	$(CXX) test_array.o array.o test.o -o test_array

test_array.o : test_array.c array.o
	$(CXX) -c test_array.c

array.o : array.h array.c test.o
	$(CXX) -c array.c 

# ---- test ----
test.o : test.h test.c
	$(CXX) -c test.c

# ---- clean ----
clean : 
	rm *.o test_array
