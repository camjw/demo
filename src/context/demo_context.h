#ifndef DEMO_DEMO_CONTEXT_H
#define DEMO_DEMO_CONTEXT_H

#include <import/model_importer.h>
#include <memory>
#include <resources/cube_map_repository.h>
#include <resources/material_repository.h>
#include <resources/mesh_repository.h>
#include <resources/shader_repository.h>
#include <resources/texture_repository.h>

class DemoContext
{
public:
    explicit DemoContext(std::shared_ptr<World> world);

    inline std::shared_ptr<MeshRepository> get_mesh_repository()
    {
        return mesh_repository;
    }
    inline std::shared_ptr<TextureRepository> get_texture_repository()
    {
        return texture_repository;
    }
    inline std::shared_ptr<MaterialRepository> get_material_repository()
    {
        return material_repository;
    }
    inline std::shared_ptr<ShaderRepository> get_shader_repository()
    {
        return shader_repository;
    }
    inline std::shared_ptr<CubeMapRepository> get_cube_map_repository()
    {
        return cube_map_repository;
    }
    inline std::shared_ptr<ModelImporter> get_model_importer()
    {
        return model_importer;
    }

private:
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<MaterialRepository> material_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
    std::shared_ptr<CubeMapRepository> cube_map_repository;
    std::shared_ptr<ModelImporter> model_importer;
};

#endif //DEMO_DEMO_CONTEXT_H
