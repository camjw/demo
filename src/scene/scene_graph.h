#ifndef DEMO_SCENE_GRAPH_H
#define DEMO_SCENE_GRAPH_H

#include "scene_node.h"
#include <ecs/entity_builder.h>

class SceneGraph
{
public:
    SceneNode* root_node;

    EntityBuilder with_entity();
};

#endif //DEMO_SCENE_GRAPH_H
