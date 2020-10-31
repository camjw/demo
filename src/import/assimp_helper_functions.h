#ifndef DEMO_ASSIMP_HELPER_FUNCTIONS_H
#define DEMO_ASSIMP_HELPER_FUNCTIONS_H

#include <assimp/color4.h>
#include <assimp/matrix4x4.h>
#include <assimp/postprocess.h>
#include <assimp/quaternion.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>
#include <maths/float3.h>
#include <maths/quaternion.h>
#include <maths/transform.h>

namespace AssimpHelperFunctions
{
    float3 to_float3(aiVector3D v);
    float3 to_float3(aiColor3D c);
    float3 to_float3(aiColor4D c);

    quaternion to_quaternion(aiQuaternion y);
    Transform to_transform(aiMatrix4x4 m);
}

#endif // DEMO_ASSIMP_HELPER_FUNCTIONS_H
