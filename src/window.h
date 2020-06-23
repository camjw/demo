#ifndef DEMO_WINDOW_HPP
#define DEMO_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <string>

#include <maths/float2.h>
#include <timer.h>

class InputState;

class Window {
public:
    Window(const std::string &window_name);

    ~Window();

    inline GLFWwindow *get_glfw_window() {
        return glfw_window;
    }

    inline bool should_close() {
        return glfwWindowShouldClose(glfw_window) || close_window;
    }

    inline glm::mat4x4 get_projection_matrix() {
        return glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
    }

    inline void set_window_dimensions(float width, float height) {
        this->width = width;
        this->height = height;
    }

    void update(Time time, InputState *input);

private:
    GLFWwindow *glfw_window = nullptr;
    bool close_window = false;
    float width, height;

    void setup_callbacks();

    static void keyboard_callback(GLFWwindow *window, int key, int scan_code, int action, int mods);

    static void mouse_position_callback(GLFWwindow *window, double x_pos, double y_pos);

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void error_callback(int code, const char *description);
};

#endif
