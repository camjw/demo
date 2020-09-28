#ifndef DEMO_MODEL_IMPORTER_H
#define DEMO_MODEL_IMPORTER_H

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <ecs/world.h>
#include <memory>
#include <resources/material_repository.h>
#include <resources/mesh_repository.h>
#include <resources/shader_repository.h>
#include <resources/texture_repository.h>
#include <scene/scene.h>
#include <scene/scene_node.h>
#include <string>
#include <unordered_set>
#include <utility>

struct ModelImportOptions
{
    bool import_camera;

    static ModelImportOptions Default()
    {
        return ModelImportOptions {
            .import_camera = false,
        };
    }
};

class ModelImporter
{
public:
    ModelImporter(std::shared_ptr<MeshRepository> mesh_repository, std::shared_ptr<TextureRepository> texture_repository,
        std::shared_ptr<MaterialRepository> material_repository, std::shared_ptr<ShaderRepository> shader_repository,
        std::shared_ptr<World> world)
        : mesh_repository(std::move(mesh_repository))
        , texture_repository(std::move(texture_repository))
        , material_repository(std::move(material_repository))
        , shader_repository(std::move(shader_repository))
        , world(std::move(world))
    {
    }

    void load_fbx(const std::string& filename, SceneNode* scene_node, ModelImportOptions import_options);
    inline void load_fbx(const std::string& filename, SceneNode* scene_node)
    {
        load_fbx(filename, scene_node, ModelImportOptions::Default());
    };

private:
    void attach_assimp_node_to_scene(const aiNode* assimp_node, SceneNode* scene_node, const std::vector<MeshID>& mesh_ids,
        const std::unordered_map<MeshID, MaterialID>& meshes_to_materials_map) const;
    void update_scene_camera(const aiScene* assimp_scene, SceneNode* scene_node);
    std::vector<MeshID> build_meshes(const aiScene* assimp_scene);
    std::unordered_map<MeshID, MaterialID> build_materials(const aiScene* assimp_scene, const std::vector<MeshID>& mesh_ids);

    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<MaterialRepository> material_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
    std::shared_ptr<World> world;

    Assimp::Importer assimp_importer;
    void populate_node(const aiNode* assimp_node, SceneNode* scene_node, const std::vector<MeshID>& mesh_ids,
        const std::unordered_map<MeshID, MaterialID>& meshes_to_materials_map) const;
};

#endif //DEMO_MODEL_IMPORTER_H
