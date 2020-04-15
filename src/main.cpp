#include <cstdio>
#include <demo/window.hpp>

int main()
{
    printf("Hello, world!\n");
    Window* window = new Window("Demo");

    while (!window->should_close())
    {
        glfwPollEvents();
    }

    return 0;
}
