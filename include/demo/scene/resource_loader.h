#ifndef DEMO_RESOURCE_LOADER_H
#define DEMO_RESOURCE_LOADER_H

#include <demo/context/mesh_repository.h>
#include <demo/context/shader_repository.h>
#include <demo/context/texture_repository.h>
#include <memory>

class ResourceLoader
{
public:
    ResourceLoader(
        std::shared_ptr<MeshRepository> mesh_repository,
        std::shared_ptr<TextureRepository> texture_repository,
        std::shared_ptr<ShaderRepository> shader_repository)
        : mesh_repository(mesh_repository)
        , texture_repository(texture_repository)
        , shader_repository(shader_repository)
    {
    }

    MeshID get_or_create_mesh(const std::string& filename);
    TextureID get_or_create_texture(const std::string& filename);
    ShaderID get_or_create_shader(const std::string& vertex_filename, const std::string& fragment_filename);

private:
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
};

#endif // DEMO_RESOURCE_LOADER_H
