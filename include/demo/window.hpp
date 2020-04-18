#ifndef DEMO_WINDOW_HPP
#define DEMO_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <string>

class Window
{
  public:
	Window(const std::string &window_name);
	~Window();

	inline GLFWwindow *get_glfw_window() { return glfw_window; }

	inline bool should_close() { return glfwWindowShouldClose(glfw_window); }

    void setup_callbacks();

  private:
	  GLFWwindow *glfw_window = nullptr;

    static void error_callback(int code, const char* description);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif
