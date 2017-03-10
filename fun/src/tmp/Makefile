BUILD_PATH = bin/

CFLAGS  = --std=c++14 -Wall -O2 -fPIC
LDLIBS  = -ldl


all : main 

main.o : main.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main : main.o
	$(CXX) $(CFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm main main.o

