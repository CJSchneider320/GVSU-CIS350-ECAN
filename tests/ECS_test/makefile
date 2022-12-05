root := $(shell git rev-parse --show-toplevel)
all: ecs_test

ecs_test:
	g++ $(root)/src/entity_manager.cpp ecs_test.cpp -o ecs_test

component_map.o:
	g++ -c $(root)/src/component_map.cpp -o component_map.o

component_manager.o:
	g++ -c $(root)/src/component_manager.cpp -o component_manager.o

entity_manager.o:
	g++ -c $(root)/src/entity_manager.cpp -o entity_manager.o

system_manager.o:
	g++ -c $(root)/src/system_manager.cpp -o system_manager.o

world.o:
	g++ -c $(root)/src/world.cpp -o world.o

ecs_test.o:
	g++ -c $(root)/src/component_manager.cpp $(root)/src/system_manager.cpp ecs_test.cpp -o ecs_test.o

clean:
	rm component_map.o component_manager.o entity_manager.o system_manager.o world.o ecs_test.o ecs_test
