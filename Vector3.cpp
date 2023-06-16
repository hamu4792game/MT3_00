#include "Vector3.h"
#include <cmath>
#include <cassert>

Vector3 Normalize(Vector3 vec3)
{
	Vector3 result;
	float w = sqrtf((vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z));
	assert(w != 0);
	result.x = vec3.x / w;
	result.y = vec3.y / w;
	result.z = vec3.z / w;
	return result;
}

float Dot(const Vector3& vec1, const Vector3& vec2) {
	float result{};
	result = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return result;
}