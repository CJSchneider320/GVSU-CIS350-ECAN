#include <cstdint>
#include <bitset>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

const Entity MAX_ENTITIES = 32000;
const ComponentType MAX_COMPONENTS = 16;

using Signature = std::bitset<MAX_COMPONENTS>;
