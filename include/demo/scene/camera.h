#ifndef DEMO_CAMERA_HPP
#define DEMO_CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include <demo/ecs/system.h>
#include <demo/input_processor.h>
#include <demo/maths/float3.h>
#include <demo/timer.h>

// Default camera values
const float SPEED = 0.01f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 45.0f;
const float LOOK_SPEED = 0.5f;

struct CameraComponent
{
    // Camera attributes
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 forward;
    glm::vec3 right;

    // Euler angles (should replace with quaternion)
    float yaw;
    float pitch;

    // Camera options
    float movement_speed;
    float mouse_sensitivity;
    float zoom;
    bool is_fps_camera;

    inline glm::mat4 get_view_matrix()
    {
        return glm::lookAt(position, position + forward, up);
    }
};

const glm::vec3 WORLD_UP = glm::vec3(0, 1, 0);

class CameraSystem: public System
{
public:
    void update(Time time, InputState* input) override;

private:
    void update_camera_vectors(CameraComponent* camera);
    void process_keyboard(Time time, InputState* input, CameraComponent* camera);
    void process_mouse_movement(Time time, InputState* input, CameraComponent* camera);

    std::shared_ptr<Coordinator> coordinator;
};

#endif
