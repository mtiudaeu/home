CFLAGS  = --std=c++14 -Wall -O2 -fPIC
LDLIBS  = -ldl

all : main libgame.so

main : main.c game.h
	g++ $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

libgame.so : game.c game.h
	g++ $(CFLAGS) -shared $(LDFLAGS) -o $@ $< $(LDLIBS)

test : main libgame.so
	./$<

clean :
	$(RM) *.o *.so main
