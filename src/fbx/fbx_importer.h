#ifndef DEMO_FBX_IMPORTER_H
#define DEMO_FBX_IMPORTER_H

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <ecs/world.h>
#include <memory>
#include <resources/mesh_repository.h>
#include <resources/texture_repository.h>
#include <scene/scene_node.h>
#include <string>
#include <utility>

class FBXImporter
{
public:
    FBXImporter(std::shared_ptr<MeshRepository> mesh_repository, std::shared_ptr<TextureRepository> texture_repository, std::shared_ptr<World> world)
        : mesh_repository(std::move(mesh_repository))
        , texture_repository(std::move(texture_repository))
        , world(std::move(world))
    {
    }

    void load_fbx(const std::string& filename, SceneNode* scene_node);

private:
    void attach_assimp_node_to_scene(const aiNode* assimp_node, SceneNode* scene_node, std::vector<MeshID>& mesh_ids, std::vector<TextureID>& texture_ids);
    std::vector<MeshID> build_meshes(const aiScene* assimp_scene);
    std::vector<TextureID> build_textures(const aiScene* assimp_scene);

private:
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<World> world;

    Assimp::Importer assimp_importer;
};

#endif //DEMO_FBX_IMPORTER_H
