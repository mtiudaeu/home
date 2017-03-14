BUILD_PATH = bin/

CFLAGS  = --std=c++14 -Wall -O2 -fPIC
LDLIBS  = -ldl


all : main 

module.o : module.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main.o : main.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main : main.o module.o
	$(CXX) $(CFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm main main.o

