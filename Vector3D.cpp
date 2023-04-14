#include "Vector3D.h"
#include <Novice.h>
#include <math.h>

Vector3D Add(const Vector3D& v1, const Vector3D& v2) {
    Vector3D result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

Vector3D Subtract(const Vector3D& v1, const Vector3D& v2) {
    Vector3D result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

Vector3D Multiply(float scalar, const Vector3D& v) {
    Vector3D result;
    result.x = scalar * v.x;
    result.y = scalar * v.y;
    result.z = scalar * v.z;
    return result;
}

float Dot(const Vector3D& v1, const Vector3D& v2) {
    float result;
    result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return result;
}

float Length(const Vector3D& v) {
    float result;
    result = sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));
    return result;
}

Vector3D Normalize(const Vector3D& v) {
    Vector3D result;
    result.x = v.x / Length(v);
    result.y = v.y / Length(v);
    result.z = v.z / Length(v);
    return result;
}


void VectorScreenPrintf(int x, int y, const Vector3D& vector, const char* label) {
    Novice::ScreenPrintf(x, y, "%.02f", vector.x);
    Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
    Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
    Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}