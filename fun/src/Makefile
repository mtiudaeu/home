CFLAGS = -std=c++14 -Wall -Werror -Wextra -O2 -g

EM++ = em++ $(CFLAGS)
G++ = g++ $(CFLAGS)

CFLAGS_SHARED_LIBS = -fPIC -shared
LDLIBS = -ldl


emcc : main.html hello.js
gcc : main.out hello.so

#gcc
hello.so : hello.cpp module.h
	$(G++) $(CFLAGS) $(CFLAGS_SHARED_LIBS) $< -o $@

module.o : module.cpp module.h
	$(G++) $(CFLAGS) -c $< -o $@

main.o : main.cpp module.h
	$(G++) $(CFLAGS) -c $< -o $@

main.out : main.o module.o
	$(G++) $(CFLAGS) $^ -o $@ $(LDLIBS)

#emcc
hello.js : hello.cpp module.h
	$(EM++) $(CFLAGS) $< -o $@ -s SIDE_MODULE=1 -fPIC
	mv hello.js hello.so

module.bc : module.cpp module.h
	$(EM++) $(CFLAGS) -c $< -o $@

main.bc : main.cpp module.h
	$(EM++) $(CFLAGS) -c $< -o $@

main.html : main.bc module.bc
	$(EM++) $(CFLAGS) $^ -o $@ -s MAIN_MODULE=1
#main.html : main.bc module.bc
#	$(EM++) $(CFLAGS) $^ -o $@ -s USE_PTHREADS=1

clean:
	rm *.so *.o *.out *.html *.bc *.mem *.js

