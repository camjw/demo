#ifndef DEMO_DEMO_CONTEXT_H
#define DEMO_DEMO_CONTEXT_H

#include <fbx/fbx_importer.h>
#include <memory>
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
    inline std::shared_ptr<ShaderRepository> get_shader_repository()
    {
        return shader_repository;
    }
    inline std::shared_ptr<FBXImporter> get_fbx_importer()
    {
        return fbx_importer;
    }

private:
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
    std::shared_ptr<FBXImporter> fbx_importer;
};

#endif //DEMO_DEMO_CONTEXT_H
