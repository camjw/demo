#ifndef DEMO_SCENE_BUILDER_H
#define DEMO_SCENE_BUILDER_H

#include "scene.h"
#include <ecs/entity_builder.h>
#include <string>

class SceneBuilder
{
public:
    void with_name(const std::string& name);

    EntityBuilder with_entity();

    Scene build();
};

#endif //DEMO_SCENE_BUILDER_H
