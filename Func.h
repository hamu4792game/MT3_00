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

//	直線
struct Line
{
	Vector3 origin; // 始点
	Vector3 diff;	// 終点への差分ベクトル
};
//	半直線
struct Ray
{
	Vector3 origin; // 始点
	Vector3 diff;	// 終点への差分ベクトル
};
//	線分
struct Segment
{
	Vector3 origin; // 始点
	Vector3 diff;	// 終点への差分ベクトル
};

Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);