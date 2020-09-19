#ifndef DEMO_RESOURCE_LOADER_H
#define DEMO_RESOURCE_LOADER_H

#include <memory>
#include <resources/mesh_repository.h>
#include <resources/shader_repository.h>
#include <resources/texture_repository.h>

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

    TextureID get_or_create_texture(const std::string& texture_name, const std::string& filename);
    ShaderID get_or_create_shader(const std::string& shader_name, const std::string& vertex_filename, const std::string& fragment_filename);

private:
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
};

#endif // DEMO_RESOURCE_LOADER_H
