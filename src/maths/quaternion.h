#ifndef DEMO_MATHS_QUATERNION_HPP
#define DEMO_MATHS_QUATERNION_HPP

#include <cstdio>
#include <math.h>

#include <cmath>
#include <demo/maths/float3.h>

struct EulerAngles
{
    float roll;
    float yaw;
    float pitch;
};

struct quaternion
{
public:
    quaternion()
        : w(1.0f)
        , x(0.0f)
        , y(0.0f)
        , z(0.0f) {};
    quaternion(float w, float x, float y, float z)
        : w(w)
        , x(x)
        , y(y)
        , z(z) {};

    quaternion normalise()
    {
        float l = length();

        w /= l;
        x /= l;
        y /= l;
        z /= l;

        return *this;
    }

    float length_squared()
    {
        return w * w - x * x - y * y - z * z;
    }

    float length()
    {
        return sqrt(length_squared());
    }

    quaternion operator*(quaternion const& other)
    {
        return quaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.z,
            w * other.z + x * other.y - y * other.x + z * other.x);
    }

    quaternion operator*=(quaternion const& other)
    {
        w = w * other.w - x * other.x - y * other.y - z * other.z;
        x = w * other.x + x * other.w + y * other.z - z * other.y;
        y = w * other.y - x * other.z + y * other.w + z * other.z;
        z = w * other.z + x * other.y - y * other.x + z * other.x;

        return *this;
    }

    static quaternion angle_axis(float angle, float3 axis)
    {
        axis.normalise();
        float s = sin(angle / 2);
        float c = cos(angle / 2);

        return quaternion(c, s * axis.x, s * axis.y, s * axis.z);
    }

    static quaternion from_euler_angles(float roll, float pitch, float yaw)
    {
        double cr = cos(roll * 0.5);
        double sr = sin(roll * 0.5);
        double cy = cos(yaw * 0.5);
        double sy = sin(yaw * 0.5);
        double cp = cos(pitch * 0.5);
        double sp = sin(pitch * 0.5);

        quaternion q;
        q.w = cr * cp * cy + sr * sp * sy;
        q.x = sr * cp * cy - cr * sp * sy;
        q.y = cr * sp * cy + sr * cp * sy;
        q.z = cr * cp * sy - sr * sp * cy;

        return q;
    }

    static quaternion from_euler_angles(EulerAngles euler_angles)
    {
        return from_euler_angles(euler_angles.roll, euler_angles.pitch, euler_angles.yaw);
    }

    EulerAngles to_euler_angles()
    {
        EulerAngles angles;

        // roll (x-axis rotation)
        float sinr_cosp = 2 * (w * x + y * z);
        float cosr_cosp = 1 - 2 * (x * x + y * y);
        angles.roll = atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        float sinp = 2 * (w * y - z * x);
        if (abs(sinp) >= 1)
        {
            angles.pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        }
        else
        {
            angles.pitch = std::asin(sinp);
        }

        // yaw (z-axis rotation)
        float siny_cosp = 2 * (w * z + x * y);
        float cosy_cosp = 1 - 2 * (y * y + z * z);
        angles.yaw = std::atan2(siny_cosp, cosy_cosp);

        return angles;
    }


    quaternion inverse()
    {
        return quaternion(w, -x, -y, -z);
    }

    void print()
    {
        printf("(%f, %f, %f, %f)\n", w, x, y, z);
    }

    float w, x, y, z;
};

#endif
