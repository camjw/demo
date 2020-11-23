#ifndef DEMO_MODEL_IMPORTER_H
#define DEMO_MODEL_IMPORTER_H

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <ecs/world.h>
#include <memory>
#include <resources/resource_manager.h>
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
    ModelImporter(std::shared_ptr<ResourceManager> resource_manager, std::shared_ptr<World> world)
        : resource_manager(std::move(resource_manager))
        , world(std::move(world))
    {
    }

    void load_fbx(const std::string& filename, SceneNode* scene_node, ModelImportOptions import_options);
    inline void load_file(const std::string& filename, SceneNode* scene_node)
    {
        load_fbx(filename, scene_node, ModelImportOptions::Default());
    };

private:
    void attach_assimp_node_to_scene(const aiNode* assimp_node, SceneNode* scene_node, const std::vector<ResourceHandle>& mesh_ids,
        const std::unordered_map<ResourceHandle, ResourceHandle>& meshes_to_materials_map) const;
    void update_scene_camera(const aiScene* assimp_scene, SceneNode* scene_node);
    std::vector<ResourceHandle> build_meshes(const aiScene* assimp_scene);
    std::unordered_map<ResourceHandle, ResourceHandle> build_materials(const aiScene* assimp_scene, const std::vector<ResourceHandle>& mesh_ids);

    std::shared_ptr<ResourceManager> resource_manager;
    std::shared_ptr<World> world;

    Assimp::Importer assimp_importer;
    void populate_node(const aiNode* assimp_node, SceneNode* scene_node, const std::vector<ResourceHandle>& mesh_ids,
        const std::unordered_map<ResourceHandle, ResourceHandle>& meshes_to_materials_map) const;
    void build_lights(const aiScene* assimp_scene, SceneNode* scene_node);
    void add_point_light(const aiLight* light, const Entity entity) const;
    void add_directional_light(const aiLight* light, const Entity entity) const;
    void add_spot_light(const aiLight* pLight, const Entity entity) const;
};

#endif //DEMO_MODEL_IMPORTER_H
