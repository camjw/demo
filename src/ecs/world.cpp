#include <ecs/world.h>
#include <ecs/signature_builder.h>

SignatureBuilder World::get_signature_builder()
{
    return SignatureBuilder(self);
}
