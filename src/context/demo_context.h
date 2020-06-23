#ifndef DEMO_CONTEXT_H
#define DEMO_CONTEXT_H

#include <context/mesh_repository.h>
#include <context/shader_repository.h>
#include <context/texture_repository.h>
#include <memory>

class DemoContext
{
public:
    DemoContext();

    std::shared_ptr<MeshRepository> get_mesh_repository();
    std::shared_ptr<TextureRepository> get_texture_repository();
    std::shared_ptr<ShaderRepository> get_shader_repository();

private:
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
};

#endif // DEMO_CONTEXT_H
