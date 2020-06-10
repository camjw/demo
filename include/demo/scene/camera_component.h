#ifndef DEMO_CAMERA_HPP
#define DEMO_CAMERA_HPP

#include <vector>

#include <demo/ecs/system.h>
#include <demo/input_processor.h>
#include <demo/maths/float3.h>
#include <demo/timer.h>

const float SPEED = 0.01f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 45.0f;
const float LOOK_SPEED = 0.5f;

struct CameraComponent
{
    float3 up;
    float3 forward;
    float3 right;

    // Camera options
    float movement_speed = SPEED;
    float mouse_sensitivity = SENSITIVITY;
    float zoom = ZOOM;
    float look_speed = LOOK_SPEED;
};

const float3 WORLD_UP = float3(0, 1, 0);

#endif
