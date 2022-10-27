root := $(shell git rev-parse --show-toplevel)
all: render_test

render_test: level.o level_renderer.o render_test.o
	g++ render_test.o level.o level_renderer.o -o render_test -lncursesw 

level.o:
	g++ -c $(root)/src/level.cpp -o level.o

level_renderer.o:
	g++ -c $(root)/src/level_renderer.cpp -o level_renderer.o

render_test.o: render_test.cpp
	g++ -c render_test.cpp -o render_test.o

clean:
	rm render_test render_test.o level.o level_renderer.o
