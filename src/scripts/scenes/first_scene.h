#ifndef DEMO_FIRST_SCENE_H
#define DEMO_FIRST_SCENE_H

#include <context/demo_context.h>
#include <ecs/world.h>
#include <memory>
#include <scene/scene.h>

class FirstScene : public Scene
{
public:
    FirstScene(std::shared_ptr<DemoContext> context, std::shared_ptr<World> world, SceneID scene_id);

    virtual void on_create() override;
    virtual void on_destroy() override;

private:
    void load_textures();
    void load_shaders();
    void load_meshes();
    void build_camera();

    void build_entities();
    void CreateLightEntityWithPosition(float3 position, MeshID mesh_id);
};

#endif // DEMO_FIRST_SCENE_H
