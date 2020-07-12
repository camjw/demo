#ifndef DEMO_ECS_SIGNATURE_H
#define DEMO_ECS_SIGNATURE_H

#include <bitset>
#include <memory>
#include <ecs/ecs.h>
#include <ecs/world.h>

class SignatureBuilder
{
    public:
        SignatureBuilder(std::shared_ptr<World> world): world(world) {}

        template <class T>
        SignatureBuilder with()
        {
            signature.set(world->get_component_type<T>());
            return *this;
        }

        SignatureBuilder reset()
        {
            signature.reset();
            return *this;
        }

        SignatureBuilder operator&(SignatureBuilder const& other)
        {
            return SignatureBuilder(world, signature & other.signature);
        }

        bool operator==(SignatureBuilder const& other)
        {
            return signature == other.signature;
        }

        Signature build()
        {
            return signature;
        }

        Signature signature;

    private:
        SignatureBuilder(std::shared_ptr<World> world, std::bitset<MAX_COMPONENTS> signature): signature(signature), world(world)  {}

        std::shared_ptr<World> world;
};

#endif

