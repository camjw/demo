#include "first_scene.h"
#include <maths/transform.h>
#include <rendering/point_light.h>
#include <utils/opengl_helpers.h>

#include <utility>

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, const std::shared_ptr<World>& world, SceneID scene_id)
    : Scene(std::move(context), world, scene_id)
{
    clear_colour = float3(1.0, 1.0, 1.0);
}

void FirstScene::on_create()
{
    build_camera();

    context->get_model_importer()->load_fbx("../assets/models/sponza.glb", graph->root().get());
    graph->add_child(world->create_entity()
                         .with(Transform {
                             .position = float3(0, 10, 0),
                         })
                         .with(DirectionalLight {
                             .direction = float3(-1, -1, 0).normalise(),
                             .ambient = float3(1, 1, 1),
                             .diffuse = float3(1, 1, 1),
                             .specular = float3(1, 1, 1),
                         })
                         .build());
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
                     .forward = float3(1.0, 0.0, 0.0).normalise(),
                 })
                 .with(Transform {
                     .position = float3(-7.0, 1.0, 0.0),
                 })
                 .build();
}
