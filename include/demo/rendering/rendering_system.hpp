#ifndef DEMO_RENDERING_RENDERING_SYSTEM_HPP
#define DEMO_RENDERING_RENDERING_SYSTEM_HPP

#include <demo/ecs/system.hpp>
#include <demo/ecs/coordinator.hpp>
#include <demo/ecs/ecs.hpp>

#include <demo/window.hpp>
#include <demo/camera.hpp>

#include <demo/rendering/shader.hpp>
#include <demo/rendering/texture.hpp>
#include <demo/rendering/cube_map.hpp>

#include <imgui/imgui.h>
#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>

class RenderingSystem : public System
{
    public:
        void init(Window* window, Camera* camera, Coordinator* coordinator);
        void destroy();
        void draw();

    private:
        Camera* camera;
        Window* window;
        Coordinator* coordinator;

        Shader simple_shader;
        Shader light_shader;
        Shader lamp_shader;
        Shader skybox_shader;
        unsigned int cube_VBO, cube_VAO, light_VAO, skybox_VAO, skybox_VBO;
        Texture texture1, texture2;

        std::vector<glm::vec3> cubes;
        std::vector<glm::vec3> lights;

        CubeMap skybox;
};

#endif
