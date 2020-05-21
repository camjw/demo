#include <demo/input_processor.h>
#include <demo/window.h>

Window::Window(const std::string& window_name)
    : width(800)
    , height(600)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfw_window = glfwCreateWindow(800, 600, window_name.c_str(), nullptr, nullptr);
    if (glfw_window == nullptr)
    {
        printf("Failed to intialise GLFW window!\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(glfw_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
    }

    glEnable(GL_DEPTH_TEST);

    setup_callbacks();
}

Window::~Window()
{
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
}

void Window::setup_callbacks()
{
    glfwSetKeyCallback(glfw_window, keyboard_callback);
    glfwSetCursorPosCallback(glfw_window, mouse_position_callback);
    glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);
    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
}

void Window::keyboard_callback(GLFWwindow* window, int key, int scan_code, int action, int mods)
{
    InputProcessor* input = reinterpret_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
    input->process_keyboard_event(key, scan_code, action, mods);
}

void Window::mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    InputProcessor* input = reinterpret_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
    input->process_mouse_position_event(xpos, ypos);
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    InputProcessor* input = reinterpret_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
    input->process_mouse_button_event(button, action, mods);
}

void Window::error_callback(int code, const char* description)
{
    printf("GLFW error occurred: %s\n", description);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    InputProcessor* input = reinterpret_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
    input->process_framebuffer_size_event(width, height);
    glViewport(0, 0, width, height);
}

void Window::update(Time time, InputState* input)
{
    float2 framebuffer_size = input->get_framebuffer_size();
    width = framebuffer_size.x;
    height = framebuffer_size.y;

    close_window = input->is_key_pressed(Key::Esc);
}
