#ifndef DEMO_CAMERA_HPP
#define DEMO_CAMERA_HPP

#include <ecs/world.h>
#include <input/input_processor.h>
#include <maths/float3.h>
#include <timer.h>
#include <vector>

const float SPEED = 0.001f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 45.0f;
const float LOOK_SPEED = 0.5f;

enum CameraType
{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

struct Camera
{
    float3 up;
    float3 forward;
    float3 right;

    // Camera options
    float movement_speed = SPEED;
    float mouse_sensitivity = SENSITIVITY;
    float zoom = ZOOM;
    float look_speed = LOOK_SPEED;

    // Real camera options
    float fov = 45.0f; // in degrees
    float near_plane = 0.01f;
    float far_plane = 100.0f;
    CameraType projection_type = PERSPECTIVE;
};

REGISTER_COMPONENT(Camera, Camera)

const float3 WORLD_UP = float3(0, 1, 0);

#endif
