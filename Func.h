#pragma once
#include "MyMatrix4x4/MyMatrix4x4.h"
#include "Vector3.h"

//	格子の描画
void DrawGrid(const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix);

struct Sphere
{
	Vector3 center;
	Vector3 rotate;
	float radius;
};

//	球の描画
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

//	線分の描画
void DrawSegment(const Segment& segment, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);

Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

//	長さを求める
float Length(const Vector3& vec);

//	球と球の衝突判定
bool IsCollision(const Sphere& s1, const Sphere& s2);

//	平面
struct Plane {
	Vector3 normal;	//	法線
	float distance;	//	距離
};

//	球と平面の衝突判定
bool IsCollision(const Sphere& sphere, const Plane& plane);

Vector3 Perpendicular(const Vector3& vector);
void DrawPlane(const Plane& plane, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);

//	線分と平面の衝突判定
bool IsCollision(const Segment& line, const Plane& plane);

//	三角形
struct Triangle {
	Vector3 vertices[3]; // 頂点
};

bool IsCollision(const Triangle& triangle, const Segment& segment);

void DrawTriangle(const Triangle& triangle, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);

//	AABB
struct AABB {
	Vector3 min;	// 最小点
	Vector3 max;	// 最大点
};
//	AABB同士の衝突判定
bool IsCollision(const AABB& aabb1, const AABB& aabb2);
//	AABBの描画
void DrawAABB(const AABB& aabb, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);

//	AABBと球の衝突判定
bool IsCollision(const AABB& aabb, const Sphere& sphere);

//	AABBと線分の衝突判定
bool IsCollision(const AABB& aabb, const Segment& segment);

struct OBB {
	Vector3 center;	// 中心点
	Vector3 orientations[3]; // 座標軸。正規化・直交必須
	Vector3 size;	// 座標軸方向の長さの半分。中心から面までの距離
};
//	OBBと球の衝突判定
bool IsCollision(const OBB& obb, const Sphere& sphere);
//	OBBの描画
void DrawOBB(const OBB& obb, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);
//	回転のセット
OBB SetOBB(const OBB& obb, const MyMatrix4x4& rotateMatrix);

//	OBBとOBBの衝突判定
bool IsCollision(const OBB& obb, const OBB& obb2);