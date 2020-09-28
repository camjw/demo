#include "demo_context.h"

DemoContext::DemoContext(std::shared_ptr<World> world)
{
    mesh_repository = std::make_shared<MeshRepository>();
    texture_repository = std::make_shared<TextureRepository>();
    material_repository = std::make_shared<MaterialRepository>();
    shader_repository = std::make_shared<ShaderRepository>();
    model_importer = std::make_shared<ModelImporter>(mesh_repository, texture_repository, material_repository, shader_repository, world);
}