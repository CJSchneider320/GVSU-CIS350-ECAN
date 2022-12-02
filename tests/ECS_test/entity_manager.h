#include "EcsConstants.h"
#include <array>
#include <queue>
#include <unordered_map>

class EntityManager {
    std::queue<Entity> available_entity_ids;
    std::uint32_t living_entities;
    std::unordered_map<Entity, Signature> signatures;
public:
    EntityManager();
    Entity create_entity();
    // Destroying a entity should remove a signature?
    void destroy_entity(Entity entity);
    void set_signature(Entity entity, Signature signature);
    Signature get_signature(Entity entity);
};
