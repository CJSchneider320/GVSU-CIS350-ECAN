#include <cassert>
#include "system_manager.h"

template <typename T>
void SystemManager::register_system() {
    const char* type_name = typeid(T).name();

    assert(system_signatures_map.find(type_name) == system_signatures_map.end() && "Cannot register a system more than once");

    systems_map[type_name] = std::make_shared<T>();
}

template <typename T>
void SystemManager::set_signature(Signature system_signature) {
    const char* type_name = typeid(T).name();

    assert(systems_map.find(type_name) != systems_map.end() && "Cannot set the signature for an unregistered system.");

    system_signatures_map[type_name] = system_signature;
}

void SystemManager::entity_signature_changed(Entity entity, Signature entity_signature) {
    for (auto const& pair : systems_map) {
        const char* type_name = pair.first;
        auto const& system = pair.second;
        const Signature system_signature = system_signatures_map[type_name];
        
        if ((entity_signature & system_signature) == system_signature)
            system->entities.insert(entity);
        else
            system->entities.erase(entity);
    }
}

void SystemManager::entity_destroyed(Entity entity) {
    for (auto const& pair : systems_map) {
        auto const& system = pair.second;
        system->entities.erase(entity);
    }
}

void SystemManager::run_systems() {
    for (auto const& pair : systems_map) {
        auto const& system = pair.second;
        system->run();
    }
}
