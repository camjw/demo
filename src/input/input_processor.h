#ifndef DEMO_INPUT_PROCESSOR_HPP
#define DEMO_INPUT_PROCESSOR_HPP

#include <input/keys.h>
#include <maths/float2.h>
#include <utils/bitmask.h>
#include <window.h>

#include <imgui/imgui.h>
#include <unordered_map>

class InputState
{
public:
    virtual ~InputState() {};
    virtual bool is_key_pressed(Key keycode) = 0;
    virtual bool is_key_up(Key keycode) = 0;
    virtual bool is_key_down(Key keycode) = 0;
    virtual float2 get_mouse_position() = 0;
    virtual float2 get_mouse_offset() = 0;
    virtual float2 get_framebuffer_size() = 0;
};

class InputProcessor : public InputState
{
public:
    InputProcessor(std::shared_ptr<Window> window);

    void process_input();

    bool is_key_pressed(Key keycode);
    bool is_key_up(Key keycode);
    bool is_key_down(Key keycode);
    inline float2 get_mouse_position()
    {
        return mouse_position;
    }
    inline float2 get_mouse_offset()
    {
        return this_frame_mouse - last_frame_mouse;
    }
    inline float2 get_framebuffer_size()
    {
        return framebuffer_size;
    }

    void process_keyboard_event(int key, int scancode, int action, int mods);
    void process_mouse_position_event(double xpos, double ypos);
    void process_mouse_button_event(int button, int action, int mods);
    void process_framebuffer_size_event(float width, float height);

private:
    inline bool read_keyboard_state(int keycode)
    {
        auto result = keyboard_state.find(keycode);

        if (result == keyboard_state.end())
        {
            return false;
        }

        return keyboard_state[keycode];
    }

    inline bool read_mouse_state(int keycode)
    {
        auto result = mouse_state.find(keycode);

        if (result == mouse_state.end())
        {
            return false;
        }

        return mouse_state[keycode];
    }

    Bitmask this_frame_keys;
    Bitmask last_frame_keys;

    float2 this_frame_mouse;
    float2 last_frame_mouse;

    std::unordered_map<int, bool> keyboard_state;
    std::unordered_map<int, bool> mouse_state;
    float2 mouse_position;

    float2 framebuffer_size = float2(800, 600);

    std::shared_ptr<Window> window;

    ImGuiIO& imgui_io;
};

#endif
