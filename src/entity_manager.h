#include <cstdint>
#include <queue>
#include <array>
#include <bitset>

// An Entity, is an ID
using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

const Entity MAX_ENTITIES = 32000;
const ComponentType MAX_COMPONENTS = 16;

using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager {
    EntityManager();
    Entity create_entity();
    // Destroying a entity should remove a signature?
    void destroy_entity(Entity entity);
    void set_signature(Entity entity, Signature signature);
    Signature get_signature(Entity entity);
private: 
    std::queue<Entity> available_entity_ids;
    std::uint32_t living_entities;
    std::array<Signature, MAX_ENTITIES> signatures;
};
