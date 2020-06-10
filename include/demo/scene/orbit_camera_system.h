#ifndef DEMO_ORBIT_CAMERA_SYSTEM_H
#define DEMO_ORBIT_CAMERA_SYSTEM_H

#include <demo/ecs/system.h>

class OrbitCameraSystem: public System
{
public:
    OrbitCameraSystem(World* coordinator) : System(coordinator) {}

    void update(Time time, InputState* input) override;
    virtual ~OrbitCameraSystem() { }

private:
    void process_keyboard(Time time, InputState* input, CameraComponent& camera, TransformComponent& transform);
    void process_mouse_movement(Time time, InputState* input, CameraComponent& camera, TransformComponent& transform);
    void update_camera_vectors(CameraComponent& camera, TransformComponent& transform);
};

#endif // DEMO_ORBIT_CAMERA_SYSTEM_H
