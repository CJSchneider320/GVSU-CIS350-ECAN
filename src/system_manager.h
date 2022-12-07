#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

#include <unordered_map>
#include <memory>
#include <cassert>
#include <string>
#include <iostream>
#include <queue>

#include "system.h"
#include "entity_manager.h"

class World;

class SystemManager {
    std::unordered_map<std::string, Signature> system_signatures_map;
    std::unordered_map<std::string, std::shared_ptr<System>> systems_map;
    std::queue<Entity> changed_entities;

public:
    template <typename T>
    void register_system() {
        const char* type_name = typeid(T).name();
    
        assert(system_signatures_map.find(type_name) == system_signatures_map.end() && "Cannot register a system more than once");
    
        auto system = std::make_shared<T>();
        systems_map[std::string(type_name)] = std::make_shared<T>();
    }
    
    template <typename T>
    void set_signature(Signature system_signature) {
        const char* type_name = typeid(T).name();
    
        assert(systems_map.find(type_name) != systems_map.end() && "Cannot set the signature for an unregistered system.");
    
        system_signatures_map[type_name] = system_signature;
    }
    
    template <typename T>
    std::shared_ptr<T> get_system() {
        const char* type_name = typeid(T).name();
    
        assert(systems_map.find(type_name) != systems_map.end() && "Cannot get an unregistered system.");

        return std::static_pointer_cast<T>(systems_map.at(std::string(type_name)));
    }
    
    void entity_signature_changed(Entity entity, Signature entity_signature) {
        for (auto pair : systems_map) {
            std::string type_name = pair.first;
            auto system = pair.second;
            const Signature system_signature = system_signatures_map[type_name];
            
            if ((entity_signature & system_signature) == system_signature
                    && system->entities.find(entity) == system->entities.end()) {
                system->entities.insert(entity);
            }
            else if ((entity_signature & system_signature) != system_signature) {
                system->entities.erase(entity);
            }
        }
    }
    
    void entity_destroyed(Entity entity) {
        for (auto const& pair : systems_map) {
            auto const& system = pair.second;
            system->entities.erase(entity);
        }
    }
    
    void run_systems(World& world, std::unique_ptr<EntityManager> &entity_manager) {
        for (auto const& pair : systems_map) {
            auto const& system = pair.second;
            system->run(world);
        }
    }
};

#endif
