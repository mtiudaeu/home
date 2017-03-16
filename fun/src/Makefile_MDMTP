CFLAGS = -std=c++14 -Wall -Werror -Wextra -O2 -g

CFLAGS_SHARED_LIBS = -fPIC -shared
LDLIBS = -ldl


all : main.out hello.so

hello.so : hello.cpp module.h
	$(CXX) $(CFLAGS) $(CFLAGS_SHARED_LIBS) $< -o $@

module.o : module.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main.o : main.cpp module.h
	$(CXX) $(CFLAGS) -c $< -o $@

main.out : main.o module.o
	$(CXX) $(CFLAGS) $^ -o $@ $(LDLIBS)


clean:
	rm *.so *.o *.out *.html *.bc *.mem *.js

