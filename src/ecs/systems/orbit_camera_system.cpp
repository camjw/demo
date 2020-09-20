#include <ecs/components/camera_component.h>
#include <ecs/systems/orbit_camera_system.h>
#include <ecs/world.h>
#include <maths/maths.h>
#include <maths/transform.h>

void OrbitCameraSystem::update(Time time, InputState* input)
{
    for (Entity const& entity : entities)
    {
        CameraComponent& camera = world->get_component<CameraComponent>(entity);
        Transform& transform = world->get_component<Transform>(entity);

        bool camera_updated = process_keyboard(time, input, camera, transform);
        camera_updated |= process_mouse_movement(time, input, camera, transform);
        update_camera_vectors(camera, transform);

        if (camera_updated)
        {
            printf("Camera updated\n");
        }
    }
}


bool OrbitCameraSystem::process_keyboard(Time time, InputState* input,
    CameraComponent& camera, Transform& transform)
{
    bool has_updated = false;
    float velocity = camera.movement_speed * time.delta_time;
    if (input->is_key_pressed(Key::Up))
    {
        has_updated = true;
        transform.position += camera.forward * velocity;
    }
    if (input->is_key_pressed(Key::Down))
    {
        has_updated = true;
        transform.position -= camera.forward * velocity;
    }

    if (input->is_key_pressed(Key::LeftShift) || input->is_key_pressed(Key::RightShift))
    {
        if (input->is_key_pressed(Key::Left))
        {
            has_updated = true;
            transform.position -= camera.right * velocity;
        }
        if (input->is_key_pressed(Key::Right))
        {
            has_updated = true;
            transform.position += camera.right * velocity;
        }
    }
    else
    {
        EulerAngles camera_euler_angles = transform.rotation.to_euler_angles();

        if (input->is_key_pressed(Key::Left))
        {
            has_updated = true;
            camera_euler_angles.yaw -= camera.look_speed * velocity;
        }
        if (input->is_key_pressed(Key::Right))
        {
            has_updated = true;
            camera_euler_angles.yaw += camera.look_speed * velocity;
        }

        transform.rotation = quaternion::from_euler_angles(camera_euler_angles);
    }

    return has_updated;
}

bool OrbitCameraSystem::process_mouse_movement(Time time, InputState* input,
    CameraComponent& camera, Transform& transform)
{
    if (!(input->is_key_pressed(Key::LeftMouseButton) && input->is_key_pressed(Key::LeftShift)))
    {
        return false;
    }

    float2 mouse_offset = input->get_mouse_offset() * camera.mouse_sensitivity;

    EulerAngles camera_euler_angles = transform.rotation.to_euler_angles();
    camera_euler_angles.pitch += mouse_offset.x;
    camera_euler_angles.yaw -= mouse_offset.y;

    camera_euler_angles.pitch = maths::clamp(camera_euler_angles.pitch, -89.0f, 89.0f);

    transform.rotation = quaternion::from_euler_angles(camera_euler_angles);

    return true;
}

void OrbitCameraSystem::update_camera_vectors(CameraComponent& camera,
    Transform& transform)
{
    EulerAngles camera_euler_angles = transform.rotation.to_euler_angles();
    camera_euler_angles.pitch = maths::mod(camera_euler_angles.pitch, 360.0f);

    float3 front;
    front.x = cos(camera_euler_angles.yaw) * cos(camera_euler_angles.pitch);
    front.y = sin(camera_euler_angles.pitch);
    front.z = sin(camera_euler_angles.yaw) * cos(camera_euler_angles.pitch);

    camera.forward = front;

    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    camera.right = float3::cross(camera.forward, WORLD_UP).normalise();
    camera.up = float3::cross(camera.right, camera.forward).normalise();
}