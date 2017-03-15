CFLAGS = -std=c++14 -Wall -Werror -Wextra -O2 -g

EMCC = em++ $(CFLAGS)
GCC = g++ $(CFLAGS)

CFLAGS_SHARED_LIBS = -fPIC -shared
LDLIBS = -ldl


emcc : main.html hello.bc
gcc : main.out hello.so
#emcc : main.html hello.bc

#gcc
hello.so : hello.cpp module.h
	$(CXX) $(CFLAGS) $(CFLAGS_SHARED_LIBS) $< -o $@

module.o : module.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main.o : main.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main.out : main.o module.o
	$(CXX) $(CFLAGS) $^ -o $@ $(LDLIBS)

#emcc
hello.bc : hello.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

module.bc : module.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main.bc : main.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main.html : main.bc module.bc
	$(CXX) $(CFLAGS) $^ -o $@ -s USE_PTHREADS=1

clean:
	rm *.so *.o *.out *.html *.bc *.mem *.js

