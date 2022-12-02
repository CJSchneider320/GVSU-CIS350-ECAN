#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"

class World {
    std::unique_ptr<EntityManager> entity_manager;
    std::unique_ptr<ComponentManager> component_manager;
    std::unique_ptr<SystemManager> system_manager;

public:
    void init();
    Entity create_entity();
    void destroy_entity(Entity);
    template <typename T>
    void register_component();
    template <typename T>
    void add_component(Entity, T);
    template <typename T>
    T& get_component(Entity);
    template <typename T>
    ComponentType get_component_type();
    template <typename T>
    void register_system();
    template <typename T>
    void set_system_signature(Signature);
    void run_systems();
};
