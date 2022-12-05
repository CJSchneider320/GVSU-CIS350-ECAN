#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

#include <unordered_map>
#include <memory>
#include <cassert>
#include <string>
#include <iostream>

#include "system.h"

class World;

class SystemManager {
    std::unordered_map<std::string, Signature> system_signatures_map;
    std::unordered_map<std::string, std::shared_ptr<System>> systems_map;

public:
    template <typename T>
    void register_system() {
        const char* type_name = typeid(T).name();
    
        assert(system_signatures_map.find(type_name) == system_signatures_map.end() && "Cannot register a system more than once");
    
        auto system = std::make_shared<T>();
        //systems_map.insert(std::make_pair<std::string, std::shared_ptr<ISystem>>(std::string(type_name), system));
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
    
        //return sys;
        //return systems_map.at(std::string(type_name));
    }
    
    void entity_signature_changed(Entity entity, Signature entity_signature) {
        for (auto& pair : systems_map) {
            std::string type_name = pair.first;
            auto system = pair.second;
            const Signature system_signature = system_signatures_map[type_name];

            std::cout << "System " << type_name << " entities:" << std::endl;
            for (auto const& ent : system->entities) {
                std::cout << "Entity " << ent << std::endl;
            }

            std::cout << "System: " << type_name << std::endl;
            std::cout << "System sig: " << system_signature << std::endl << "Entity sig: " << entity_signature << std::endl;
            
            if ((entity_signature & system_signature) == system_signature
                    && system->entities.find(entity) == system->entities.end()) {
                std::cout << "System: " << type_name << " adding entity " << entity << std::endl;
                system->entities.insert(entity);
            }
            else if ((entity_signature & system_signature) != system_signature) {
                std::cout << "System: " << type_name << " removing entity " << entity << std::endl;
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
    
    void run_systems(World& world) {
        for (auto const& pair : systems_map) {
            auto const& system = pair.second;
            //std::cout << "Running system: " << pair.first << std::endl;
            system->run(world);
        }
    }

    void maintain_systems() {

    }
};

#endif
