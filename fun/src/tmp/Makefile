BUILD_PATH = bin/

CFLAGS = -std=c++14 -Wall -Wextra -O2 -g
CFLAGS_SHARED_LIBS = -fPIC
LDLIBS = -ldl


all : main 

hello.so : hello.cpp module.h
	$(CXX) $(CFLAGS) $(CFLAGS_SHARED_LIBS) -c $< -shared -o $@

module.o : module.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main.o : main.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main : main.o module.o hello.so
	$(CXX) $(CFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm main main.o module.o hello.so

