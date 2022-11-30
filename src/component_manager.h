#include <unordered_map>
#include <memory>

#include "component_map.h"


class ComponentManager{
    std::unordered_map<const char*, std::shared_ptr<IComponentMap>> components;
    std::unordered_map<const char*, ComponentType> component_types;
    ComponentType next_component_type;
public:
    ComponentManager();
    template <typename T>
    void register_component();
    template <typename T>
    ComponentType get_component_type();
    template <typename T>
    void add_component(Entity, T);
    template <typename T>
    void remove_component(Entity);
    template <typename T>
    std::shared_ptr<ComponentMap<T>> get_component_map();
    template <typename T>
    T& get_component(Entity);
    void entity_destroyed(Entity);
};
