#include <ecs/components/hierarchy_component.h>
#include <ecs/components/name_component.h>
#include <ecs/components/wren_script_component.h>
#include <ecs/systems/first_person_camera_system.h>
#include <ecs/systems/wren_scripting_system.h>
#include <engine.h>
#include <maths/transform.h>
#include <rendering/directional_light.h>
#include <rendering/material.h>
#include <rendering/point_light.h>
#include <rendering/spot_light.h>
#include <utils/opengl_helpers.h>

Engine::Engine()
{
    window = std::make_shared<Window>("Estuary King");
    #ifdef WINDOWS
    window->load_icon("./assets/icon.png");
    #endif

    IMGUI_CHECKVERSION();
    imgui_context = ImGui::CreateContext();
    assert(imgui_context != nullptr && "Failed to create ImGui context");

    input = std::make_unique<InputProcessor>(window);

    world = std::make_shared<World>();
    world->init(world);

    // Build context
    context = std::make_shared<DemoContext>(world);

    // Init shaders
    std::shared_ptr<ShaderRepository> shader_repository = context->get_shader_repository();
    shader_repository->create_shader("lamp");
    shader_repository->create_shader("lighting");
    shader_repository->create_shader("pixel");
    shader_repository->create_shader("simple");
    shader_repository->create_shader("skybox");
    shader_repository->create_shader("uv_test");
    ShaderID simple_lighting_shader_id = shader_repository->create_shader(
        "simple_lighting",
        DEMO_CONSTANTS_SHADERS_FOLDER + "lighting_shader.vert",
        DEMO_CONSTANTS_SHADERS_FOLDER + "lighting_shader_no_textures.frag");
    shader_repository->create_shader("deferred");
    shader_repository->create_shader("deferred_rendering");
    shader_repository->create_shader("deferred_lighting");

    // Init default materials
    std::shared_ptr<MaterialRepository> material_repository = context->get_material_repository();
    material_repository->insert_material(pewter_material(simple_lighting_shader_id), "pewter");
    material_repository->insert_material(ruby_material(simple_lighting_shader_id), "ruby");
    material_repository->insert_material(emerald_material(simple_lighting_shader_id), "emerald");
    material_repository->insert_material(turquoise_material(simple_lighting_shader_id), "turquoise");

    // Register components
    world->register_component<Transform>();
    world->register_component<TextureComponent>();
    world->register_component<MeshComponent>();
    world->register_component<ShaderComponent>();
    world->register_component<MaterialComponent>();
    world->register_component<CameraComponent>();
    world->register_component<HierarchyComponent>();
    world->register_component<NameComponent>();
    world->register_component<PointLight>();
    world->register_component<DirectionalLight>();
    world->register_component<CubeMapComponent>();
    world->register_component<WrenScriptComponent>();
    world->register_component<SpotLight>();

    // Register systems
    world->register_system<FirstPersonCameraSystem>();
    Signature camera_system_signature;
    camera_system_signature.set(world->get_component_type<CameraComponent>());
    camera_system_signature.set(world->get_component_type<Transform>());
    world->set_system_signature<FirstPersonCameraSystem>(camera_system_signature);

    world->register_system<WrenScriptingSystem>();
    Signature wren_scripting_system_signature;
    wren_scripting_system_signature.set(world->get_component_type<WrenScriptComponent>());
    world->set_system_signature<WrenScriptingSystem>(wren_scripting_system_signature);

    // Init scene manager
    scene_manager = std::make_shared<SceneManager>(context, world);

    ui_root = std::make_shared<UIRoot>(world, window, context, scene_manager, imgui_context);

    // Init renderer
    renderer = std::make_unique<OpenGLRenderer>(context, window, world, ui_root);
}

Engine::~Engine()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Engine::run()
{
    const int UPDATE_FREQUENCY = 60;
    const float CYCLE_TIME = 1000.0f / UPDATE_FREQUENCY;

    static Timer system_timer;
    static Timer physics_timer;

    float accumulated_milliseconds = 0.0f;

    while (is_running())
    {
        system_timer.tick();
        process_input();
        accumulated_milliseconds += system_timer.get_time().delta_time;

        if (accumulated_milliseconds >= CYCLE_TIME)
        {
            accumulated_milliseconds -= CYCLE_TIME;

            physics_timer.tick();

            Time time = physics_timer.get_time();
            update(time);

            late_update(time);

            draw(time);
        }
    }
}

void Engine::update(Time time)
{
    window->update(time, input.get());
    scene_manager->update(time, input.get());
    world->update_systems(time, input.get());
    ui_root->update();
}

void Engine::late_update(Time time)
{
    scene_manager->late_update(time, input.get());
    world->late_update_systems(time, input.get());
    ui_root->late_update();
}

void Engine::draw(Time time)
{
    renderer->draw_scene(time, scene_manager->get_current_scene());
}

void Engine::process_input()
{
    input->process_input();
}

bool Engine::is_running() { return !window->should_close(); }
