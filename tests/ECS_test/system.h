#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <set>

#include "EcsConstants.h"

class World;

//class ISystem {
//public:
//    std::set<Entity> entities;
//    virtual void run(World&) = 0;
//};

class System {
public:
    std::set<Entity> entities;
    std::set<ComponentType> components;
    // Must be implemented by a System. This will be run whenever
    // run_systems() is called from the World.
    virtual void run(World&) = 0;
};

#endif
