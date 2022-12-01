#include <unordered_map>
#include <memory>

#include "system.h"

class SystemManager {
    std::unordered_map<const char*, Signature> system_signatures_map;
    std::unordered_map<const char*, std::shared_ptr<System>> systems_map;

public:
    template <typename T>
    void register_system();
    template <typename T>
    void set_signature(Signature);
    void entity_signature_changed(Entity, Signature);
    void entity_destroyed(Entity);
    void run_systems();
};
