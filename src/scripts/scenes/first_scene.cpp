#include "first_scene.h"
#include <maths/transform.h>
#include <rendering/point_light.h>
#include <scripts/components/rotating_cube.h>
#include <utils/opengl_helpers.h>

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, std::shared_ptr<World> world, SceneID scene_id)
    : Scene(context, world, scene_id)
{
}

void FirstScene::on_create()
{
    load_textures();
    load_shaders();
    load_meshes();

    build_camera();

    MeshID cube_id = context->get_mesh_repository()->create_cube();
    TextureID texture_id = context->get_texture_repository()->get_texture_id("uv_test");

    world->register_component<RotatingCubeComponent>();
    world->register_system<RotatingCubeSystem>();

    Signature rotating_cube_signature;
    rotating_cube_signature.set(world->get_component_type<Transform>());
    rotating_cube_signature.set(world->get_component_type<RotatingCubeComponent>());
    world->set_system_signature<RotatingCubeSystem>(rotating_cube_signature);

    Entity grandparent_entity = world->create_entity()
                                    .with(Transform {
                                        .position = float3(0, 0, 0),
                                        .rotation = quaternion(1.0, 0.0, 1.0, 0.0).normalise(),
                                        .scale = float3(1.0f),
                                    })
                                    .with(TextureComponent { .id = texture_id })
                                    .with(TURQUOISE_MATERIAL)
                                    .with(MeshComponent { .id = cube_id })
                                    .with(context->get_shader_repository()->get_shader_component("lighting"))
                                    .build();

    world->add_component(grandparent_entity, RotatingCubeComponent {
                                                 .speed = 0.001f,
                                                 .axis = float3(1, 0, 0),
                                             });

    SceneNode* grandparent_node = graph->add_child(grandparent_entity);

    Entity parent_entity = world->create_entity()
                               .with(Transform {
                                   .position = float3(0, 5.0f, 0),
                                   .scale = float3(0.5f),
                               })
                               .with(TextureComponent { .id = texture_id })
                               .with(EMERALD_MATERIAL)
                               .with(MeshComponent { .id = cube_id })
                               .with(context->get_shader_repository()->get_shader_component("lighting"))
                               .with_parent(grandparent_entity)
                               .build();

    world->add_component(parent_entity, RotatingCubeComponent {
                                            .speed = 0.002f,
                                            .axis = float3(0, 1, 0),
                                        });

    SceneNode* parent_node = grandparent_node->add_child(parent_entity);

    Entity child_entity = world->create_entity()
                              .with(Transform {
                                  .position = float3(10.0f, 0.0f, 0.0f),
                                  .scale = float3(0.2f),
                              })
                              .with(TextureComponent { .id = texture_id })
                              .with(RUBY_MATERIAL)
                              .with(MeshComponent { .id = cube_id })
                              .with(context->get_shader_repository()->get_shader_component("lighting"))
                              .with_parent(parent_entity)
                              .build();

    parent_node->add_child(child_entity);

    create_light_entity_with_position(float3(20.0f, 0.0f, 20.0f), cube_id);
    create_light_entity_with_position(float3(20.0f, 0.0f, 0.0f), cube_id);
    create_light_entity_with_position(float3(20.0f, 0.0f, 20.0f), cube_id);
    create_light_entity_with_position(float3(40.0f, 0.0f, 00.0f), cube_id);
    create_directional_light_entity();
}

void FirstScene::load_textures()
{
    context->get_texture_repository()->create_texture("primal_scream", "../assets/textures/primal_scream.png");
    context->get_texture_repository()->create_texture("uv_test", "../assets/textures/uv_test.png");
}

void FirstScene::load_shaders()
{
    context->get_shader_repository()->create_shader(
        "simple",
        "../assets/shaders/simple_shader.vert",
        "../assets/shaders/simple_shader.frag");

    context->get_shader_repository()->create_shader(
        "lighting",
        "../assets/shaders/lighting_shader.vert",
        "../assets/shaders/lighting_shader.frag");

    context->get_shader_repository()->create_shader(
        "lamp",
        "../assets/shaders/lamp_shader.vert",
        "../assets/shaders/lamp_shader.frag");
}

void FirstScene::load_meshes()
{
    // Moved this back out just because CBA to add stupid functions now
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
                 })
                 .build();
}

void FirstScene::on_destroy()
{
    // Dump all of those here
}

void FirstScene::create_light_entity_with_position(float3 position, MeshID mesh_id)
{
    Entity light_entity = world->create_entity()
        .with(Transform {
            .position = position,
            .scale = float3(0.1f),
        })
        .with(MeshComponent { .id = mesh_id })
        .with(PEWTER_MATERIAL)
        .with(context->get_shader_repository()->get_shader_component("lamp"))
        .with(PointLight {
            .colour = float3(0.8, 0.8, 0.8),
            .constant = 0.001f,
            .linear = 0.009f,
            .quadratic = 0.00032f,
            .ambient = float3(0.05f, 0.05f, 0.05f),
            .diffuse = float3(0.8f, 0.8f, 0.8f),
            .specular = float3(1.0f, 1.0f, 1.0f),
        })
        .build();

    graph->add_child(light_entity);
}

void FirstScene::create_directional_light_entity()
{
    Entity directional_light_entity = world->create_entity()
        .with(DirectionalLight {
            .direction = float3(-0.2, -0.3, -0.4),
            .ambient = float3(0.1, 0.1, 0.1),
            .diffuse = float3(0.1, 0.1, 0.1),
            .specular = float3(0.1, 0.1, 0.1),
        })
        .build();

    graph->add_child(directional_light_entity);
}
