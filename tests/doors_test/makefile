root := $(shell git rev-parse --show-toplevel)
all: doors_test

doors_test: level.o level_renderer.o doors_test.o
	g++ -lncursesw doors_test.o level.o level_renderer.o -o doors_test

level.o:
	g++ -c $(root)/src/level.cpp -o level.o

level_renderer.o:
	g++ -c $(root)/src/level_renderer.cpp -o level_renderer.o

doors_test.o:
	g++ -c doors_test.cpp -o doors_test.o

clean:
	rm doors_test doors_test.o level.o level_renderer.o
