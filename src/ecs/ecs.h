#ifndef DEMO_ECS_ECS_HPP
#define DEMO_ECS_ECS_HPP

#include <bitset>
#include <cstdint>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;
const Entity INVALID_ENTITY = UINT32_MAX;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif
