#ifndef DEMO_FBX_IMPORTER_H
#define DEMO_FBX_IMPORTER_H

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <ecs/world.h>
#include <memory>
#include <resources/mesh_repository.h>
#include <resources/shader_repository.h>
#include <resources/texture_repository.h>
#include <scene/scene.h>
#include <scene/scene_node.h>
#include <string>
#include <unordered_set>
#include <utility>

struct FBXImportOptions
{
    bool import_camera;

    static FBXImportOptions Default()
    {
        return FBXImportOptions {
            .import_camera = false,
        };
    }
};

class FBXImporter
{
public:
    FBXImporter(std::shared_ptr<MeshRepository> mesh_repository, std::shared_ptr<TextureRepository> texture_repository,
        std::shared_ptr<ShaderRepository> shader_repository, std::shared_ptr<World> world)
        : mesh_repository(std::move(mesh_repository))
        , texture_repository(std::move(texture_repository))
        , shader_repository(std::move(shader_repository))
        , world(std::move(world))
    {
    }

    void load_fbx(const std::string& filename, SceneNode* scene_node, FBXImportOptions import_options);
    inline void load_fbx(const std::string& filename, SceneNode* scene_node)
    {
        load_fbx(filename, scene_node, FBXImportOptions::Default());
    };

private:
    void attach_assimp_node_to_scene(const aiNode* assimp_node, SceneNode* scene_node, std::vector<MeshID>& mesh_ids,
        std::vector<TextureID>& texture_ids, std::unordered_set<MeshID>& used_meshes);
    void update_scene_camera(const aiScene* assimp_scene, SceneNode* scene_node);
    std::vector<MeshID> build_meshes(const aiScene* assimp_scene);
    std::vector<TextureID> build_textures(const aiScene* assimp_scene);

    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
    std::shared_ptr<World> world;

    Assimp::Importer assimp_importer;
    void populate_node(const aiNode* assimp_node, SceneNode* scene_node, std::vector<MeshID> mesh_ids, std::unordered_set<MeshID>& used_meshes);
};

#endif //DEMO_FBX_IMPORTER_H
