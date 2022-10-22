root := $(shell git rev-parse --show-toplevel)
all: walls_test

walls_test: level.o level_renderer.o walls_test.o
	g++ -lncursesw walls_test.o level.o level_renderer.o -o walls_test

level.o:
	g++ -c $(root)/src/level.cpp -o level.o

level_renderer.o:
	g++ -c $(root)/src/level_renderer.cpp -o level_renderer.o

walls_test.o:
	g++ -c walls_test.cpp -o walls_test.o

clean:
	rm walls_test walls_test.o level.o level_renderer.o
