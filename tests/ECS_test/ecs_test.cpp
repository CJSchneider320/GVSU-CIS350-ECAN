// TODO Determine what causes segfault in removing a component from an entity
#include <iostream>
#include <string>
#include "world.h"

// In files specifically dedicated to a system, you must use this include:
// #include "system.h"
// Also, any externally defined components and systems must included
// before you use them.

struct Position {
    int x;
    int y;
};

struct Greeting {
    std::string greeting;
};

struct Farewell {
    std::string farewell;
};

class Move : public System {
public:
    void run(World& world) override {
        //std::cout << "Start Move" << std::endl;
        for (Entity entity : entities) {
            //std::cout << "My entity: " << entity << std::endl;
            auto& position = world.get_component<Position>(entity);
            if (position.x == 80) {
                position.y += 1;
                position.x = 0;
            } else {
                position.x += 1;
            }
            //std::cout << "x, y: " << position.x << ", " << position.y << std::endl;
        }
        //std::cout << "Done in Move" << std::endl;
    }
};

class SayGreeting : public System {
public:
    void run(World& world) {
        //std::cout << "Start SayGreeting" << std::endl;
        for (Entity entity : entities) {
            //std::cout << "My entity: " << entity << std::endl;
            auto position = world.get_component<Position>(entity);
            auto greeting = world.get_component<Greeting>(entity);

            
            if (position.x % 40 == 0) {
                std::cout << greeting.greeting << std::endl;
            }
            if (position.y == 50) {
                world.remove_component<Greeting>(entity);
                std::cout << "Removed greeting from Entity " << entity << std::endl;
            }
        }
        //std::cout << "Done in SayGreeting" << std::endl;
    }
};

class SayFarewell : public System {
public:
    void run(World& world) {
        //std::cout << "Start SayFarewell" << std::endl;
        for (Entity entity : entities) {
            //std::cout << "My entity: " << entity << std::endl;
            auto position = world.get_component<Position>(entity);
            auto farewell = world.get_component<Farewell>(entity);

            if (position.y > 0 && position.x == 79) {
                std::cout << farewell.farewell <<std::endl;
            }
            if (position.y == 50) {
                world.remove_component<Farewell>(entity);
            }
        }
        //std::cout << "Done in SayFarewell" << std::endl;
    }
};


int main() {
    std::cout << "Initializing World..." << std::endl;
    World world;
    world.init();

    // Register Components first
    std::cout << "Registering Components..." << std::endl;
    world.register_component<Position>();
    world.register_component<Greeting>();
    world.register_component<Farewell>();

    // Register Systems next, and add their necessary components to them.
    std::cout << "Registering Systems..." << std::endl;
    auto move_system = world.register_system<Move>();
    move_system->components.insert(world.get_component_type<Position>());
    world.set_system_signature<Move>();

    auto say_greeting_system = world.register_system<SayGreeting>();
    say_greeting_system->components.insert(world.get_component_type<Position>());
    say_greeting_system->components.insert(world.get_component_type<Greeting>());
    world.set_system_signature<SayGreeting>();

    auto farewell_system = world.register_system<SayFarewell>();
    farewell_system->components.insert(world.get_component_type<Position>());
    farewell_system->components.insert(world.get_component_type<Farewell>());
    world.set_system_signature<SayFarewell>();

    // Create entities and add their components
    std::cout <<"Creating Entities..." << std::endl;
    std::cout << "Entity 0..." << std::endl;
    Entity e1 = world.create_entity();
    world.add_component(e1, Position {10, 10});
    world.add_component(e1, Greeting {"Hello there!"});
    
    std::cout << "Entity 1..." << std::endl;
    Entity e2 = world.create_entity();
    world.add_component(e2, Position {0, 0});
    world.add_component(e2, Farewell { "Take it easy!" });

    std::cout << "Running systems..." << std::endl;
    int i = 0;
    while (i < 32000) {
        world.run_systems(world);
        i++;
    }
    std::cout << "Finished" << std::endl;
}
