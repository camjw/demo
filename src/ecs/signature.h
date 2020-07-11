#ifndef DEMO_ECS_SIGNATURE_H
#define DEMO_ECS_SIGNATURE_H

#include <memory>
#include <bitset>
#include <ecs/ecs.h>
#include <ecs/world.h>

class Signature
{
    public:
        Signature(std::shared_ptr<World> world, std::bitset<MAX_COMPONENTS> bitset): world(world), bitset(bitset) {}

        Signature(std::shared_ptr<World> world): world(world) {}

        template <class T>
        Signature with()
        {
            bitset.set(world->get_component_type<T>());
            return *this;
        }

        Signature reset()
        {
            bitset.reset();
            return *this;
        }

        Signature operator&(Signature const& other)
        {
            return Signature(world, bitset & other.bitset);
        }

        bool operator==(Signature const& other)
        {
            return bitset == other.bitset;
        }

        std::bitset<MAX_COMPONENTS> bitset;

    private:
        std::shared_ptr<World> world;
};

#endif

