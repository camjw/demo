#include <demo/ecs/coordinator.h>
#include <demo/scene/camera.h>

void CameraSystem::update(Time time, InputState* input)
{
    for (Entity const& entity : entities)
    {
        CameraComponent camera = coordinator->get_component<CameraComponent>(entity);

        process_keyboard(time, input, &camera);
        process_mouse_movement(time, input, &camera);

        update_camera_vectors(&camera);
    }
}

void CameraSystem::process_keyboard(Time time, InputState* input, CameraComponent* camera)
{
    float velocity = camera->movement_speed * time.delta_time;
    if (input->is_key_pressed(Key::Up))
    {
        camera->position += camera->forward * velocity;
    }
    if (input->is_key_pressed(Key::Down))
    {
        camera->position -= camera->forward * velocity;
    }

    if (input->is_key_pressed(Key::LeftShift) || input->is_key_pressed(Key::RightShift))
    {
        if (input->is_key_pressed(Key::Left))
        {
            camera->position -= camera->right * velocity;
        }
        if (input->is_key_pressed(Key::Right))
        {
            camera->position += camera->right * velocity;
        }
    }
    else
    {
        if (input->is_key_pressed(Key::Left))
        {
            camera->yaw -= LOOK_SPEED * velocity;
        }
        if (input->is_key_pressed(Key::Right))
        {
            camera->yaw += LOOK_SPEED * velocity;
        }
    }

    if (camera->is_fps_camera)
    {
        camera->position.y = 0;
    }
}

void CameraSystem::process_mouse_movement(Time time, InputState* input, CameraComponent* camera)
{
    if (!(input->is_key_pressed(Key::LeftMouseButton) && input->is_key_pressed(Key::LeftShift)))
    {
        return;
    }

    float2 mouse_offset = input->get_mouse_offset() * camera->mouse_sensitivity;

    camera->yaw += mouse_offset.x;
    camera->pitch -= mouse_offset.y;

    if (camera->pitch > 89.0f)
    {
        camera->pitch = 89.0f;
    }

    if (camera->pitch < -89.0f)
    {
        camera->pitch = -89.0f;
    }
}

void CameraSystem::update_camera_vectors(CameraComponent* camera)
{
    camera->yaw = glm::mod(camera->yaw, 360.0f);

    glm::vec3 front;
    front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
    front.y = sin(glm::radians(camera->pitch));
    front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));

    camera->forward = glm::normalize(front);

    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    camera->right = glm::normalize(glm::cross(camera->forward, WORLD_UP));
    camera->up = glm::normalize(glm::cross(camera->right, camera->forward));
}