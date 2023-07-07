#pragma once
#include "MyMatrix4x4/MyMatrix4x4.h"
#include "Vector3.h"

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

float Length(const Vector3& vec);

bool IsCollision(const Sphere& s1, const Sphere& s2);

//	平面
struct Plane {
	Vector3 normal;	//	法線
	float distance;	//	距離
};

//	おーばーろーど
bool IsCollision(const Sphere& sphere, const Plane& plane);

Vector3 Perpendicular(const Vector3& vector);
void DrawPlane(const Plane& plane, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);

bool IsCollision(const Segment& line, const Plane& plane);

//	三角形
struct Triangle {
	Vector3 vertices[3]; // 頂点
};

bool IsCollision(const Triangle& triangle, const Segment& segment);

void DrawTriangle(const Triangle& triangle, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);