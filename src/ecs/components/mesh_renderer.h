#ifndef DEMO_MESH_RENDERER_H
#define DEMO_MESH_RENDERER_H

#include "resources/resource_handle.h"

struct MeshRenderer
{
    ResourceHandle mesh;
    ResourceHandle material;
};

#endif // DEMO_MESH_RENDERER_H
