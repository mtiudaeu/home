CFLAGS = -g -DINCLUDE_RUN_TEST
CXX = gcc $(CFLAGS)

all: test_translator test_array

# ---- translator ----
test_translator : test_translator.o translator.o
	$(CXX) test_translator.o translator.o test.o -o test_translator

test_translator.o : test_translator.c translator.o
	$(CXX) -c test_translator.c

translator.o : translator.h translator.c test.o
	$(CXX) -c translator.c 

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
	rm *.o test_translator test_array
