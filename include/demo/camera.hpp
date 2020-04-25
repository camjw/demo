#ifndef DEMO_CAMERA_HPP
#define DEMO_CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include <demo/input_processor.hpp>
#include <demo/timer.hpp>

// Default camera values
const float SPEED = 0.025f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float LOOK_SPEED = 2.0f;

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    glm::mat4 get_view_matrix();
    void update(Time time, InputState* input);

    inline glm::vec3 get_position()
    {
        return position;
    }

    inline glm::vec3 get_forward_direction()
    {
        return forward;
    }

private:
    void update_camera_vectors();
    void process_keyboard(Time time, InputState* input);
    void process_mouse_movement(Time time, InputState* input);
    void process_mouse_scroll(float yoffset);

    // Camera Attributes
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    // Euler Angles
    float yaw;
    float pitch;

    // Camera options
    float movement_speed;
    float mouse_sensitivity;
    float zoom;
    bool is_fps_camera = true;
};

#endif
