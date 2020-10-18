#include <input/input_processor.h>
#include <utils/opengl_helpers.h>
#include <window.h>

Window::Window(const std::string& window_name)
    : width_(800)
    , height_(600)
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
        printf("Failed to initialise GLFW window!\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(glfw_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
    }

    glCheckError();

    glEnable(GL_DEPTH_TEST);

    glCheckError();

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

    glCheckError();
}

void Window::keyboard_callback(GLFWwindow* window, int key, int scan_code, int action, int mods)
{
    InputProcessor* input = reinterpret_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
    input->process_keyboard_event(key, scan_code, action, mods);

    glCheckError();
}

void Window::mouse_position_callback(GLFWwindow* window, double x_pos, double y_pos)
{
    InputProcessor* input = reinterpret_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
    input->process_mouse_position_event(x_pos, y_pos);
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    InputProcessor* input = reinterpret_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
    input->process_mouse_button_event(button, action, mods);
}

void Window::error_callback(int code, const char* description)
{
    printf("GLFW error occurred: code %i, %s\n", code, description);
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
    width_ = framebuffer_size.x;
    height_ = framebuffer_size.y;

    close_window = input->is_key_pressed(Key::Esc);
}

void Window::load_icon(const std::string& icon_path) {
    GLFWimage images[1];
    images[0].pixels = stbi_load(icon_path.c_str(), &images[0].width, &images[0].height, 0, 4); //rgba channels
    glfwSetWindowIcon(glfw_window, 1, images);
    stbi_image_free(images[0].pixels);
}
