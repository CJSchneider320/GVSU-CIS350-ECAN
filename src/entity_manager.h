#include "EcsConstants.h"
#include <queue>
#include <array>

class EntityManager {
    std::queue<Entity> available_entity_ids;
    std::uint32_t living_entities;
    std::array<Signature, MAX_ENTITIES> signatures;
public:
    EntityManager();
    Entity create_entity();
    // Destroying a entity should remove a signature?
    void destroy_entity(Entity entity);
    void set_signature(Entity entity, Signature signature);
    Signature get_signature(Entity entity);
};
