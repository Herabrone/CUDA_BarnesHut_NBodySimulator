#ifndef VEC3_H
#define VEC3_H

#include <cmath>

#if defined(__CUDACC__)
#define HD __host__ __device__
#else
#define HD
#endif

// 3D vector with double precision, host and device usable
struct Vec3 {
    double x, y, z; // 3D components

    // Constructors
    HD Vec3() : x(0.0), y(0.0), z(0.0) {}
    HD Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    // Vector addition
    HD Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
    // Vector subtraction
    HD Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
    // Scalar multiplication
    HD Vec3 operator*(double s) const { return Vec3(x * s, y * s, z * s); }
    // Scalar division
    HD Vec3 operator/(double s) const { return Vec3(x / s, y / s, z / s); }

    // Dot product
    HD double dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }
    // Squared norm
    HD double norm2() const { return dot(*this); }
    // Euclidean norm
    HD double norm() const { return sqrt(norm2()); }
};

#endif // VEC3_H
