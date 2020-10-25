#include <ecs/signature_builder.h>
#include <ecs/world.h>
#include <ecs/entity_builder.h>

SignatureBuilder World::get_signature_builder()
{
    return SignatureBuilder(self);
}

EntityBuilder* World::create_entity()
{
    return new EntityBuilder(self);
}

void register_component(component_registration_function crf)
{
    components_to_register().push_back(crf);
}

std::vector<component_registration_function>& components_to_register()
{
    static std::vector<component_registration_function> v;
    return v;
}