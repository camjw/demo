#ifndef DEMO_RENDERING_RENDERING_SYSTEM_HPP
#define DEMO_RENDERING_RENDERING_SYSTEM_HPP

#include <demo/ecs/system.h>
#include <demo/ecs/coordinator.h>
#include <demo/ecs/ecs.h>

#include <demo/window.h>
#include <demo/camera.h>

#include <demo/rendering/shader.h>
#include <demo/rendering/texture.h>
#include <demo/rendering/cube_map.h>
#include <demo/rendering/mesh_repository.h>
#include <demo/rendering/texture_repository.h>
#include <demo/rendering/shader_repository.h>

#include <demo/rendering/shader_commands/shader_commands.h>
#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

class RenderingSystem : public System
{
    public:
        RenderingSystem();
        ~RenderingSystem();
        void init(Window* window, Camera* camera, Coordinator* coordinator);
        void destroy();
        void draw(Time time);

        void begin_draw(Time time);
        void draw_entities();
        void end_draw();

    private:
        Camera* camera{};
        Window* window{};
        Coordinator* coordinator{};

        MeshRepository* mesh_repository;
        TextureRepository* texture_repository;
        ShaderRepository* shader_repository;

        Shader simple_shader{};
        Shader light_shader{};
        Shader lamp_shader{};
        Shader skybox_shader{};
        unsigned int cube_VBO{}, cube_VAO{}, cube_EBO{}, light_VAO{}, skybox_VAO{}, skybox_EBO{};
        Texture texture1, texture2;

        std::vector<glm::vec3> cubes;
        std::vector<glm::vec3> lights;

        CubeMap skybox;
};

#endif
