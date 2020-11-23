#include "demo_context.h"
#include <resources/cube_map_factory.h>

DemoContext::DemoContext(std::shared_ptr<World> world)
{
    resource_manager = std::make_shared<ResourceManager>();
    resource_manager->add_factory(new TextureFactory());
    resource_manager->add_factory(new ShaderFactory());
    resource_manager->add_factory(new MeshFactory());
    resource_manager->add_factory(new MaterialFactory(resource_manager));
    resource_manager->add_factory(new CubeMapFactory());

    model_importer = std::make_shared<ModelImporter>(resource_manager, world);
}