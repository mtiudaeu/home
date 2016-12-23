LDLIBS=-lglut -lGL -lSDL2 -lSDL2_image -lGLEW

all: shader_utils.o
	g++ shader_utils.o cube.cpp  -o a.out $(LDLIBS)

shader_utils.o:
	g++ -c shader_utils.c

clean:
	rm -f *.o *.out *.js *.html *.bc *.mem *.data

.PHONY: all clean gcc emcc
