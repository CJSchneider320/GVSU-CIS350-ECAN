#include "EcsConstants.h"
#include <unordered_map>

class IComponentMap {
    virtual ~IComponentMap() = default;
    virtual void entity_destroyed(Entity) = 0;
};

template<typename T>
class ComponentMap : public IComponentMap {
    std::unordered_map<Entity, T> component_map;

public:
    ComponentMap();
    void insert_component(Entity, T);
    void remove_component(Entity);
    T& get_component(Entity);
    void entity_destroyed(Entity);
};
