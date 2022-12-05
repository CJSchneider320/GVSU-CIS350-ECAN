#ifndef WORLD_H_
#define WORLD_H_

#include <queue>

#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"

class World {
    std::unique_ptr<EntityManager> entity_manager;
    std::unique_ptr<ComponentManager> component_manager;
    std::unique_ptr<SystemManager> system_manager;
    std::queue<Entity> changed_entities;

public:
    void init() {
        entity_manager = std::make_unique<EntityManager>();
        component_manager = std::make_unique<ComponentManager>();
        system_manager = std::make_unique<SystemManager>();
    }
    
    // Entity related methods
    
    Entity create_entity() {
        return entity_manager->create_entity();
    }
    
    void destroy_entity(Entity entity) {
        entity_manager->destroy_entity(entity);
        component_manager->entity_destroyed(entity);
        system_manager->entity_destroyed(entity);
    }
    
    // Component related methods
    
    template <typename T>
    void register_component() {
        component_manager->register_component<T>();
    }
    
    template <typename T>
    void add_component(Entity entity, T component) {
        component_manager->add_component(entity, component);
        auto signature = entity_manager->get_signature(entity);
        signature.set(component_manager->get_component_type<T>(), true);
        entity_manager->set_signature(entity, signature);
    
        changed_entities.push(entity);
    }
    
    template <typename T>
    void remove_component(Entity entity) {
        //std::cout << "Removing component: " << typeid(T).name() << std::endl;
        component_manager->remove_component<T>(entity);
    
        auto signature = entity_manager->get_signature(entity);
        signature.set(component_manager->get_component_type<T>(), false);
        entity_manager->set_signature(entity, signature);
    
        changed_entities.push(entity);
    }
    
    template <typename T>
    T& get_component(Entity entity) {
        return component_manager->get_component<T>(entity);
    }
    
    template <typename T>
    ComponentType get_component_type() {
        return component_manager->get_component_type<T>();
    }

    template <typename T>
    std::shared_ptr<ComponentMap<T>> get_component_map() {
        return component_manager->get_component_map<T>();
    }
    
    // System related methods
    
    template <typename T>
    std::shared_ptr<T> register_system() {
        system_manager->register_system<T>();
    
        auto const& new_system = system_manager->get_system<T>();
    
        return system_manager->get_system<T>();
    }
    
    template <typename T>
    void set_system_signature() {
        auto const& new_system = system_manager->get_system<T>();
        
        Signature signature;
        for (auto component : new_system->components) {
            signature.set(component, true);
        }
    
        system_manager->set_signature<T>(signature);
    }
    
    void run_systems(World& world) {
        system_manager->run_systems(world, entity_manager);
        maintain();
    }

    void maintain() {
        while (!changed_entities.empty()) {
            Entity entity = changed_entities.front();
            system_manager->entity_signature_changed(entity, entity_manager->get_signature(entity));
            changed_entities.pop();
        }
    }

};

#endif
