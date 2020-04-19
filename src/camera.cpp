#include <demo/camera.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : 
    position(position), forward(glm::vec3(0.0f, 0.0f, -1.0f)),  world_up(up), yaw(yaw), 
    pitch(pitch), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
{
    update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position, position + forward, up);
}

void Camera::update(Time time, InputState* input)
{
    process_keyboard(time, input);
    process_mouse_movement(time, input);

    update_camera_vectors();
}

void Camera::process_keyboard(Time time, InputState* input)
{
    float velocity = movement_speed * time.delta_time;
    if (input->is_key_pressed(Key::Up))
    {
        position += forward * velocity;
    }
    if (input->is_key_pressed(Key::Down))
    {
        position -= forward * velocity;
    }
    if (input->is_key_pressed(Key::Left))
    {
        yaw -= LOOK_SPEED * velocity;
    }
    if (input->is_key_pressed(Key::Right))
    {
        yaw += LOOK_SPEED * velocity;
    }

    if (is_fps_camera)
    {
        position.y = 0;
    }
}


void Camera::process_mouse_movement(Time time, InputState* input)
{
    if (!input->is_key_pressed(Key::LeftMouseButton))
    {
        return;
    }

    float2 mouse_offset = input->get_mouse_offset() * mouse_sensitivity;

    yaw   += mouse_offset.x;
    pitch -= mouse_offset.y;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
}

void Camera::process_mouse_scroll(float yoffset)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
    {
        zoom -= yoffset;
    }
    if (zoom <= 1.0f)
    {
        zoom = 1.0f;
    }
    if (zoom >= 45.0f)
    {
        zoom = 45.0f;
    }
}

void Camera::update_camera_vectors()
{
    yaw = glm::mod(yaw, 360.0f);

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    forward = glm::normalize(front);

    right = glm::normalize(glm::cross(forward, world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, forward));
}
