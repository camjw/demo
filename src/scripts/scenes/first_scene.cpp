#include "first_scene.h"
#include <maths/transform.h>
#include <rendering/point_light.h>
#include <utils/opengl_helpers.h>

#include <ecs/components/wren_script_component.h>
#include <utility>

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, const std::shared_ptr<World>& world, SceneID scene_id)
    : Scene(std::move(context), world, scene_id)
{
    clear_colour = float3(1.0, 1.0, 1.0);
}

void FirstScene::on_create()
{
    build_camera();
    build_skybox();

    context->get_model_importer()->load_fbx("../assets/models/crytek_sponza.fbx", graph->root().get());
    float3 sunlight_colour = float3(240.0f / 255, 240.0f / 255, 188.0f / 255);
    float light_intensity = 0.75f;
    graph->add_child(world->create_entity()
                         ->with(Transform {
                             .position = float3(0, 10, 0),
                         })
                         ->with(DirectionalLight {
                             .direction = float3(-2, -5, -1).normalise(),
                             .ambient = light_intensity * sunlight_colour,
                             .diffuse = light_intensity * sunlight_colour,
                             .specular = light_intensity * sunlight_colour,
                         })
                         ->build());
}

void FirstScene::on_destroy()
{
    printf("Exiting scene\n");
}

void FirstScene::build_camera()
{
    camera = world->create_entity()
                 ->with(CameraComponent {
                     .up = float3(0.0, 1.0, 0.0),
                     .forward = float3(1.0, 0.0, 0.0).normalise(),
                 })
                 ->with(Transform {
                     .position = float3(-1.0, 1.0, 0.0),
                 })
                 ->with(WrenScriptComponent {})
                 ->build();
}

void FirstScene::build_skybox()
{
    CubeMapID cloudy_sky_id = context->get_cube_map_repository()->create_cube_map("cloudy_sky", "../assets/skyboxes/cloudy_sky");
    skybox = world->create_entity()
                 ->with(CubeMapComponent(cloudy_sky_id))
                 ->build();
}
