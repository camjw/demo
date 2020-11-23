#include "first_scene.h"
#include <ecs/components/cube_map_renderer.h>
#include <maths/transform.h>
#include <rendering/lighting/point_light.h>
#include <utility>
#include <utils/opengl_helpers.h>

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, const std::shared_ptr<World>& world, SceneID scene_id)
    : Scene(std::move(context), world, scene_id)
{
    clear_colour = float3(1.0, 1.0, 1.0);
}

void FirstScene::on_create()
{
    build_camera();
    build_skybox();

    context->get_model_importer()->load_file("../assets/models/Sponza/sponza.gltf", graph->root().get());
}

void FirstScene::on_destroy()
{
    printf("Exiting scene\n");
}

void FirstScene::build_camera()
{
    camera = world->create_entity()
                 ->with(Camera {
                     .up = float3(0.0, 1.0, 0.0),
                     .forward = float3(1.0, 0.0, 0.0).normalise(),
                 })
                 ->with(Transform {
                     .position = float3(-1.0, 0.0, 0.0),
                 })
                 ->build();

    world->create_entity()
        ->with(DirectionalLight {
            .direction = float3(0.0, -5.0, 1.333).normalise(),
            .ambient = colour(1.0, 1.0, 1.0),
        })
        ->build();

    world->create_entity()
        ->with(PointLight {
            .main_colour = colour(1.0, 0.0, 0.0),
            .constant = 0,
            .linear = 1,
            .quadratic = 0,
            .ambient = colour(1.0, 0.0, 0.0),
            .diffuse = colour(1.0, 0.0, 0.0),
            .specular = colour(1.0, 0.0, 0.0),
        })
        ->with (Transform {
            .position = float3(-110.0, 14.0, -41.0),
        })
        ->build();

    world->create_entity()
        ->with(PointLight {
            .main_colour = colour(0.0, 1.0, 0.0),
            .constant = 0,
            .linear = 1,
            .quadratic = 0,
            .ambient = colour(0.0, 1.0, 0.0),
            .diffuse = colour(0.0, 1.0, 0.0),
            .specular = colour(0.0, 1.0, 0.0),
        })
        ->with (Transform {
            .position = float3(-110.0, 14.0, -41.0),
        })
        ->build();

    world->create_entity()
        ->with(PointLight {
            .main_colour = colour(0.0, 0.0, 1.0),
            .constant = 0,
            .linear = 1,
            .quadratic = 0,
            .ambient = colour(0.0, 0.0, 1.0),
            .diffuse = colour(0.0, 0.0, 1.0),
            .specular = colour(0.0, 0.0, 1.0),
        })
        ->with (Transform {
            .position = float3(110, 16.0, 41.0),
        })
        ->build();

    world->create_entity()
        ->with(PointLight {
            .main_colour = colour(1.0, 0.0, 1.0),
            .constant = 0,
            .linear = 1,
            .quadratic = 0,
            .ambient = colour(1.0, 0.0, 1.0),
            .diffuse = colour(1.0, 0.0, 1.0),
            .specular = colour(1.0, 0.0, 1.0),
        })
        ->with (Transform {
            .position = float3(-110.0, 16.0, 41.0),
        })
        ->build();
}

void FirstScene::build_skybox()
{
    ResourceHandle cloudy_sky = context->get_resource_manager()->load<CubeMap>("cloudy_sky");
    skybox = world->create_entity()
                 ->with(CubeMapRenderer {
                     .cube_map = cloudy_sky,
                 })
                 ->build();
}
