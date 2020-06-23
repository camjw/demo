#ifndef DEMO_ORBIT_CAMERA_SYSTEM_H
#define DEMO_ORBIT_CAMERA_SYSTEM_H

#include <ecs/system.h>

class OrbitCameraSystem: public System
{
public:
    OrbitCameraSystem(World* world) : System(world) {}

    void update(Time time, InputState* input) override;
    virtual ~OrbitCameraSystem() { }

private:
    void process_keyboard(Time time, InputState* input, CameraComponent& camera, Transform& transform);
    void process_mouse_movement(Time time, InputState* input, CameraComponent& camera, Transform& transform);
    void update_camera_vectors(CameraComponent& camera, Transform& transform);
};

#endif // DEMO_ORBIT_CAMERA_SYSTEM_H
