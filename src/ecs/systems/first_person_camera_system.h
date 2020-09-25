#ifndef DEMO_FIRST_PERSON_CAMERA_SYSTEM_H
#define DEMO_FIRST_PERSON_CAMERA_SYSTEM_H

#include <cmath>
#include <ecs/components/camera_component.h>
#include <ecs/system.h>
#include <ecs/world.h>
#include <maths/maths.h>
#include <maths/transform.h>

class FirstPersonCameraSystem : public System
{
public:
    FirstPersonCameraSystem(World* world)
        : System(world)
    {
    }

    void update(Time time, InputState* input) override;
    virtual ~FirstPersonCameraSystem() { }

private:
    bool process_keyboard(Time time, InputState* input, CameraComponent& camera, Transform& transform);
    bool process_mouse_movement(Time time, InputState* input, CameraComponent& camera, Transform& transform);
    void update_camera_vectors(CameraComponent& camera, Transform& transform);
};

#endif // DEMO_FIRST_PERSON_CAMERA_SYSTEM_H
