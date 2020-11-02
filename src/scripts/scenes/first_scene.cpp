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

    context->get_model_importer()->load_file("../assets/models/sponza_2.glb", graph->root().get());
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
                     .position = float3(-1.0, 0.0, 0.0),
                 })
                 ->with(WrenScriptComponent {
                     .script_filename = "assets/scripts/hello_world.wren",
                 })
                 ->build();
}

void FirstScene::build_skybox()
{
    CubeMapID cloudy_sky_id = context->get_cube_map_repository()->create_cube_map("cloudy_sky", "../assets/skyboxes/cloudy_sky");
    skybox = world->create_entity()
                 ->with(CubeMapComponent(cloudy_sky_id))
                 ->build();
}
