#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_
#include <array>
#include <queue>
#include <unordered_map>
#include <cassert>
#include "EcsConstants.h"

class EntityManager {
    std::queue<Entity> available_entity_ids;
    std::uint32_t living_entities;
    std::unordered_map<Entity, Signature> signatures;
public:
    EntityManager() {
        living_entities = 0;
        
        for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
            available_entity_ids.push(entity);
        }
    }
    
    Entity create_entity() {
        assert(living_entities < MAX_ENTITIES && "Too many entities exist to create more.");
    
        Entity entity = available_entity_ids.front();
        available_entity_ids.pop();
        ++living_entities;
    
        return entity;
    }
    
    void destroy_entity(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity is out of range of maximum entities.");
    
        signatures.erase(entity);
        available_entity_ids.push(entity);
        --living_entities;
    }
    
    void set_signature(Entity entity, Signature signature) {
        assert(entity < MAX_ENTITIES && "Entity is out of range of maximum entities.");
    
        signatures[entity] = signature;
    }
    
    Signature get_signature(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity is out of range of maximum entities.");
    
        return signatures[entity];
    }
};

#endif
