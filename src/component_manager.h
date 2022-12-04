#include <unordered_map>
#include <memory>
#include <cassert>
#include <iostream>

#include "component_map.h"


class ComponentManager{
    std::unordered_map<const char*, std::shared_ptr<IComponentMap>> components;
    std::unordered_map<const char*, ComponentType> component_types;
    ComponentType next_component_type;
public:
    ComponentManager() {
        components = std::unordered_map<const char*, std::shared_ptr<IComponentMap>>();
        component_types = std::unordered_map<const char*, ComponentType>();
        next_component_type = 0;
    }
    
    template <typename T>
    void register_component() {
        const char* type_name = typeid(T).name();
    
        assert(component_types.find(type_name) == component_types.end() && "Cannot register a component more than once.");
    
        components[type_name] = std::make_shared<ComponentMap<T>>();
        component_types[type_name] = next_component_type;
        ++next_component_type;
    }
    
    template <typename T>
    ComponentType get_component_type() {
        const char* type_name = typeid(T).name();
    
        assert(component_types.find(type_name) != component_types.end() && "Cannot get a component type for an unregistered component");
    
        return component_types[type_name];
    }
    
    template <typename T>
    void add_component(Entity entity, T component) {
        get_component_map<T>()->insert_component(entity, component);
    }
    
    template <typename T>
    void remove_component(Entity entity) {
        get_component_map<T>()->remove_component(entity);
    }
    
    template <typename T>
    T& get_component(Entity entity) {
        return get_component_map<T>()->get_component(entity);
    }
    
    template <typename T>
    std::shared_ptr<ComponentMap<T>> get_component_map() {
        const char* type_name = typeid(T).name();
    
        assert(component_types.find(type_name) != component_types.end() && "Cannot get a component map for an unregistered component.");
    
        return std::static_pointer_cast<ComponentMap<T>>(components[type_name]);
    }
    
    void entity_destroyed(Entity entity) {
        for (auto const& pair : components) {
            auto const& component = pair.second;
            component->entity_destroyed(entity);
        }
    }
};
