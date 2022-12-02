#include "EcsConstants.h"
#include <unordered_map>

class IComponentMap {
public:
    virtual ~IComponentMap() = default;
    virtual void entity_destroyed(Entity) = 0;
};

template<typename T>
class ComponentMap : public IComponentMap {
    std::unordered_map<Entity, T> component_map;

public:
ComponentMap() {
    component_map = std::unordered_map<Entity, T>();
}

void insert_component(Entity entity, T component) {
    assert(component_map.find(entity) == component_map.end() && "Entity already has this component.");

    component_map[entity] = component;
}

void remove_component(Entity entity) {
    assert(component_map.find(entity) != component_map.end() && "Entity does not have this component.");

    component_map.erase(entity);
}

T& get_component(Entity entity) {
    assert(component_map.find(entity) != component_map.end() && "Entity does not have this component.");

    return component_map[entity];
}

void entity_destroyed(Entity entity) {
    if (component_map.find(entity) != component_map.end())
        remove_component(entity);
}
};
