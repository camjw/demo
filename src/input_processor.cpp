#include <input_processor.h>

InputProcessor::InputProcessor(Window* window)
    : this_frame_mouse(0.0f, 0.0f)
    , last_frame_mouse(0.0f, 0.0f)
{
    glfwSetWindowUserPointer(window->get_glfw_window(), this);
}

void InputProcessor::process_input()
{
    glfwPollEvents();

    last_frame_keys.set_mask(this_frame_keys);

    // parse keyboard
    bool left_key_pressed = read_keyboard_state(GLFW_KEY_LEFT) || read_keyboard_state(GLFW_KEY_A);
    this_frame_keys.set_bit((int)Key::Left, left_key_pressed);

    bool right_key_pressed = read_keyboard_state(GLFW_KEY_RIGHT) || read_keyboard_state(GLFW_KEY_D);
    this_frame_keys.set_bit((int)Key::Right, right_key_pressed);

    bool up_key_pressed = read_keyboard_state(GLFW_KEY_UP) || read_keyboard_state(GLFW_KEY_W);
    this_frame_keys.set_bit((int)Key::Up, up_key_pressed);

    bool down_key_pressed = read_keyboard_state(GLFW_KEY_DOWN) || read_keyboard_state(GLFW_KEY_S);
    this_frame_keys.set_bit((int)Key::Down, down_key_pressed);

    bool esc_key_pressed = read_keyboard_state(GLFW_KEY_ESCAPE) || read_keyboard_state(GLFW_KEY_Q);
    this_frame_keys.set_bit((int)Key::Esc, esc_key_pressed);

    bool left_shift_key_pressed = read_keyboard_state(GLFW_KEY_LEFT_SHIFT);
    this_frame_keys.set_bit((int)Key::LeftShift, left_shift_key_pressed);

    bool right_shift_key_pressed = read_keyboard_state(GLFW_KEY_RIGHT_SHIFT);
    this_frame_keys.set_bit((int)Key::RightShift, right_shift_key_pressed);

    bool space_key_pressed = read_keyboard_state(GLFW_KEY_SPACE);
    this_frame_keys.set_bit((int)Key::Space, space_key_pressed);

    // parse mouse buttons
    bool left_mouse_button_pressed = read_mouse_state(GLFW_MOUSE_BUTTON_LEFT);
    this_frame_keys.set_bit((int)Key::LeftMouseButton, left_mouse_button_pressed);

    bool right_mouse_button_pressed = read_mouse_state(GLFW_MOUSE_BUTTON_RIGHT);
    this_frame_keys.set_bit((int)Key::RightMouseButton, right_mouse_button_pressed);

    // update mouse position
    last_frame_mouse = this_frame_mouse;
    this_frame_mouse = mouse_position;
}

bool InputProcessor::is_key_pressed(Key keycode)
{
    return this_frame_keys.get_bit((int)keycode);
}

bool InputProcessor::is_key_up(Key keycode)
{
    return !this_frame_keys.get_bit((int)keycode) && last_frame_keys.get_bit((int)keycode);
}

bool InputProcessor::is_key_down(Key keycode)
{
    return this_frame_keys.get_bit((int)keycode) && !last_frame_keys.get_bit((int)keycode);
}

void InputProcessor::process_keyboard_event(int key, int scancode, int action, int mods)
{
    switch (action)
    {
    case GLFW_PRESS:
        keyboard_state[key] = true;
        break;
    case GLFW_RELEASE:
        keyboard_state[key] = false;
        break;
    }
}

void InputProcessor::process_mouse_position_event(double xpos, double ypos)
{
    mouse_position.x = (float)xpos;
    mouse_position.y = (float)ypos;
}

void InputProcessor::process_mouse_button_event(int button, int action, int mods)
{
    switch (action)
    {
    case GLFW_PRESS:
        mouse_state[button] = true;
        break;
    case GLFW_RELEASE:
        mouse_state[button] = false;
        break;
    }
}

void InputProcessor::process_framebuffer_size_event(float width, float height)
{
    framebuffer_size = float2(width, height);
}
