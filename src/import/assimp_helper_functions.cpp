#include "assimp_helper_functions.h"

float3 AssimpHelperFunctions::to_float3(aiVector3D v)
{
    return float3(v.x, v.y, v.z);
}

colour AssimpHelperFunctions::to_colour(aiColor3D c)
{
    return colour(c.r, c.g, c.b);
}

colour AssimpHelperFunctions::to_colour(aiColor4D c)
{
    return colour(c.r, c.g, c.b, c.a);
}

quaternion AssimpHelperFunctions::to_quaternion(aiQuaternion q)
{
    return quaternion(q.w, q.x, q.y, q.z);
}

Transform AssimpHelperFunctions::to_transform(aiMatrix4x4 m)
{
    aiVector3D position;
    aiQuaternion rotation;
    aiVector3D scale;

    m.Decompose(scale, rotation, position);

    return Transform {
        .position = AssimpHelperFunctions::to_float3(position),
        .rotation = AssimpHelperFunctions::to_quaternion(rotation),
        .scale = AssimpHelperFunctions::to_float3(scale)
    };
}

