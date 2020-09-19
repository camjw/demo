#include "first_scene.h"
#include <maths/transform.h>
#include <rendering/point_light.h>
#include <utils/opengl_helpers.h>

#include <utility>

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, const std::shared_ptr<World>& world, SceneID scene_id)
    : Scene(std::move(context), world, scene_id)
{
}

void FirstScene::on_create()
{
    build_camera();

    context->get_fbx_importer()->load_fbx("../assets/models/sponza.fbx", graph->root().get());
}

void FirstScene::on_destroy()
{
    printf("Exiting scene\n");
}

void FirstScene::build_camera()
{
    camera = world->create_entity()
                 .with(CameraComponent {
                     .up = float3(0.0, 1.0, 0.0),
                     .forward = float3(0.0, 0.0, -1.0),
                 })
                 .with(Transform {
                     .position = float3(0.0, 0.0, 10.0),
                     .rotation = quaternion(0, 1, 0, 0),
                 })
                 .build();
}
