#ifndef DEMO_WINDOW_HPP
#define DEMO_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <cstdio>
#include <string>

#include <maths/float2.h>
#include <maths/int2.h>
#include <timer.h>

class InputState;

class Window
{
public:
    Window(const std::string& window_name);

    ~Window();

    inline GLFWwindow* get_glfw_window()
    {
        return glfw_window;
    }

    inline bool should_close()
    {
        return glfwWindowShouldClose(glfw_window) || close_window;
    }

    inline glm::mat4x4 get_projection_matrix()
    {
        return glm::perspective(glm::radians(45.0f), (float)width_ / height_, 0.1f, 100.0f);
    }

    inline void set_window_dimensions(int width, int height)
    {
        this->width_ = width;
        this->height_ = height;
    }

    void update(Time time, InputState* input);

    void load_icon(const std::string& icon_path);

    inline int width() const
    {
        return width_;
    }

    inline int height() const
    {
        return height_;
    }

    inline int2 get_viewport_dimensions() const
    {
        int viewportWidth, viewportHeight;
        glfwGetFramebufferSize(glfw_window, &viewportWidth, &viewportHeight);
        return int2(viewportWidth, viewportHeight);
    }

private:
    GLFWwindow* glfw_window = nullptr;
    bool close_window = false;
    int width_, height_;

    void setup_callbacks();

    static void keyboard_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);
    static void mouse_position_callback(GLFWwindow* window, double x_pos, double y_pos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void error_callback(int code, const char* description);
};

#endif
