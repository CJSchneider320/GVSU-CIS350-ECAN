#include <set>

#include "EcsConstants.h"

class System {
public:
    std::set<const char*> components;
    std::set<Entity> entities;
    // Must be implemented by a System. This will be run whenever
    // run_systems() is called from the World.
    virtual void run() = 0;
};
