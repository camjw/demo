#ifndef DEMO_ORBIT_CAMERA_SYSTEM_H
#define DEMO_ORBIT_CAMERA_SYSTEM_H

#include <ecs/system.h>
#include <maths/transform.h>
#include <ecs/components/camera_component.h>

class OrbitCameraSystem: public System
{
public:
    OrbitCameraSystem(World* world) : System(world) {}

    void update(Time time, InputState* input) override;
    virtual ~OrbitCameraSystem() { }

private:
    bool process_keyboard(Time time, InputState* input, CameraComponent& camera, Transform& transform);
    bool process_mouse_movement(Time time, InputState* input, CameraComponent& camera, Transform& transform);
    void update_camera_vectors(CameraComponent& camera, Transform& transform);
};

#endif // DEMO_ORBIT_CAMERA_SYSTEM_H
