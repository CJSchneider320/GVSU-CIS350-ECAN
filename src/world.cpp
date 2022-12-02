#include "world.h"

void World::init() {
    entity_manager = std::make_unique<EntityManager>();
    component_manager = std::make_unique<ComponentManager>();
    system_manager = std::make_unique<SystemManager>();
}

// Entity related methods

Entity World::create_entity() {
    return entity_manager->create_entity();
}

void World::destroy_entity(Entity entity) {
    entity_manager->destroy_entity(entity);
    component_manager->entity_destroyed(entity);
    system_manager->entity_destroyed(entity);
}

// Component related methods

template <typename T>
void World::register_component() {
    component_manager->register_component<T>();
}

template <typename T>
void World::add_component(Entity entity, T component) {
    component_manager->add_component(entity, component);

    auto signature = entity_manager->get_signature(entity);
    signature.set(component_manager->get_component_type<T>(), true);
    entity_manager->set_signature(entity, signature);

    system_manager->entity_signature_changed(entity, signature);
}

template <typename T>
T& World::get_component(Entity entity) {
    return component_manager->get_component<T>(entity);
}

template <typename T>
ComponentType World::get_component_type() {
    return component_manager->get_component_type<T>();
}

// System related methods

template <typename T>
void World::register_system() {
    system_manager->register_system<T>();

    auto new_system = system_manager->get_system<T>();

    Signature system_signature;
    for (auto component : new_system->components) {
        system_signature.set(component_manager->get_component_type<typeid(component)>(), true);
    }
    system_manager->set_signature<T>(system_signature);
}

void World::run_systems() {
    system_manager->run_systems();
}
