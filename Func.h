#pragma once
#include "MyMatrix4x4/MyMatrix4x4.h"

void DrawGrid(const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix);

struct Sphere
{
	Vector3 center;
	Vector3 rotate;
	float radius;
};

void DrawSphere(const Sphere& sphere, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);