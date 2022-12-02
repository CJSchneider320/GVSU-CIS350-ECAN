#ifndef ECSCONSTANTS_H_
#define ECSCONSTANTS_H_
#include <cstdint>
#include <bitset>
#include <typeinfo>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

const Entity MAX_ENTITIES = 32000;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif
