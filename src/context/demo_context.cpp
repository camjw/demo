#include <demo/context/demo_context.h>

DemoContext::DemoContext()
{
    mesh_repository = std::make_shared<MeshRepository>();
    texture_repository = std::make_shared<TextureRepository>();
    shader_repository = std::make_shared<ShaderRepository>();
}

std::shared_ptr<MeshRepository> DemoContext::get_mesh_repository()
{
    printf("Getting mesh repository");
    return mesh_repository;
}

std::shared_ptr<TextureRepository> DemoContext::get_texture_repository()
{
    printf("Getting texture repository");
    return texture_repository;
}

std::shared_ptr<ShaderRepository> DemoContext::get_shader_repository()
{
    printf("Getting shader repository");
    return shader_repository;
}