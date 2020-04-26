#ifndef DEMO_ENGINE_HPP
#define DEMO_ENGINE_HPP

#include <demo/camera.hpp>
#include <demo/rendering/cube_map.hpp>
#include <demo/input_processor.hpp>
#include <demo/rendering/shader.hpp>
#include <demo/rendering/texture.hpp>
#include <demo/timer.hpp>
#include <demo/window.hpp>

#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <vector>

class Engine
{

public:
    Engine();
    ~Engine();

    void process_input();

    void update(Time time);
    void late_update(Time time);
    void draw();

    bool is_running();

private:
    float random_float(float low = -5, float high = 15);

    Window* window = nullptr;
    InputProcessor* input = nullptr;
    Camera* camera = nullptr;

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
