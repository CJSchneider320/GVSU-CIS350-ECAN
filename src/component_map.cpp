#include "component_map.h"

template <typename T>
ComponentMap<T>::ComponentMap() {
    component_map = std::unordered_map<Entity, T>();
}

template <typename T>
void ComponentMap<T>::insert_component(Entity entity, T component) {
    assert(component_map.find(entity) == component_map.end() && "Entity already has this component.");

    component_map[entity] = component;
}

template <typename T>
void ComponentMap<T>::remove_component(Entity entity) {
    assert(component_map.find(entity) != component_map.end() && "Entity does not have this component.");

    component_map.erase(entity);
}

template <typename T>
T& ComponentMap<T>::get_component(Entity entity) {
    assert(component_map.find(entity) != component_map.end() && "Entity does not have this component.");

    return component_map[entity];
}

template <typename T>
void ComponentMap<T>::entity_destroyed(Entity entity) {
    if (component_map.find(entity) != component_map.end())
        remove_component(entity);
}

