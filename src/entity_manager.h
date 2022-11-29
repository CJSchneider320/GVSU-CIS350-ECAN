#include <cstdint>
#include <queue>
#include <array>

// An Entity, is an ID
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 32000;

using Signature = std::uint8_t;

class EntityManager {
    void create_entity();
    // Destroying a entity should remove a signature?
    void destroy_entity();
    void set_signature();
    void get_signature();
private: 
    std::queue<Entity> available_entity_ids;
    std::uint32_t living_entities;
    std::array<Signature, MAX_ENTITIES> signatures;
};
