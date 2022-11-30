#include "entity_manager.h"
#include <cassert>

EntityManager::EntityManager() {
    living_entities = 0;
    
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        available_entity_ids.push(entity);
    }
}

Entity EntityManager::create_entity() {
    assert(living_entities < MAX_ENTITIES && "Too many entities exist to create more.");

    Entity entity = available_entity_ids.front();
    available_entity_ids.pop();
    ++living_entities;

    return entity;
}

void EntityManager::destroy_entity(Entity entity) {
    assert(entity < MAX_ENTITIES && "Entity is out of range of maximum entities.");

    signatures[entity].reset();
    available_entity_ids.push(entity);
    --living_entities;
}

void EntityManager::set_signature(Entity entity, Signature signature) {
    assert(entity < MAX_ENTITIES && "Entity is out of range of maximum entities.");

    signatures[entity] = signature;
}
