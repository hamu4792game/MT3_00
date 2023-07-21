#include "Func.h"
#include <Novice.h>
#include <numbers>
#include <cmath>
#include <algorithm>

void DrawGrid(const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix)
{
	//	Gridの半分の幅
	const float kGridHalfWidth = 2.0f;
	//	分割数
	const unsigned int kSubdivision = 10;
	//	1つ分の長さ
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	MyMatrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
	MyMatrix4x4 worldViewProjectionMatrix = worldMatrix * viewProjectionMatrix;

	//	奥から手前へ
	Vector3 translate{ 0.0f,0.0f,0.0f };
	Vector3 startLocal{ kGridHalfWidth,0.0f,translate.z };
	Vector3 endLocal{ -kGridHalfWidth,0.0f,translate.z };

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++)
	{
		//	Local座標を求める
		if (xIndex <= kSubdivision / 2) {
			//	奥に足していく
			startLocal.z = translate.z + (xIndex * kGridEvery);
			endLocal.z = translate.z + (xIndex * kGridEvery);
		}
		else {
			//	手前に引いていく
			startLocal.z = translate.z - ((xIndex - (kSubdivision / 2)) * kGridEvery);
			endLocal.z = translate.z - ((xIndex - (kSubdivision / 2)) * kGridEvery);
		}
		//	座標変換
		Vector3 startScreen = Transform(startLocal, worldViewProjectionMatrix);
		startScreen = Transform(startScreen, viewportMatrix);
		Vector3 endScreen = Transform(endLocal, worldViewProjectionMatrix);
		endScreen = Transform(endScreen, viewportMatrix);


		if (startLocal.z == 0.0f && endLocal.z == 0.0f) {
			Novice::DrawLine(static_cast<int>(startScreen.x), static_cast<int>(startScreen.y),
				static_cast<int>(endScreen.x), static_cast<int>(endScreen.y), 0xff);
		}
		else {
			Novice::DrawLine(static_cast<int>(startScreen.x), static_cast<int>(startScreen.y),
				static_cast<int>(endScreen.x), static_cast<int>(endScreen.y), 0xaaaaaaff);
		}
	}

	//	左から右へ
	startLocal = { translate.x,0.0f,-kGridHalfWidth };
	endLocal = { translate.x,0.0f,kGridHalfWidth };

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++)
	{
		//	Local座標を求める
		if (zIndex <= kSubdivision / 2) {
			//	右に足していく
			startLocal.x = translate.x + (zIndex * kGridEvery);
			endLocal.x = translate.x + (zIndex * kGridEvery);
		}
		else {
			//	左に引いていく
			startLocal.x = translate.x - ((zIndex - (kSubdivision / 2)) * kGridEvery);
			endLocal.x = translate.x - ((zIndex - (kSubdivision / 2)) * kGridEvery);
		}

		//	座標変換
		Vector3 startScreen = Transform(startLocal, worldViewProjectionMatrix);
		startScreen = Transform(startScreen, viewportMatrix);
		Vector3 endScreen = Transform(endLocal, worldViewProjectionMatrix);
		endScreen = Transform(endScreen, viewportMatrix);

		if (startLocal.x == 0.0f)
		{
			Novice::DrawLine(static_cast<int>(startScreen.x), static_cast<int>(startScreen.y),
				static_cast<int>(endScreen.x), static_cast<int>(endScreen.y), 0xff);
		}
		else
		{
			Novice::DrawLine(static_cast<int>(startScreen.x), static_cast<int>(startScreen.y),
				static_cast<int>(endScreen.x), static_cast<int>(endScreen.y), 0xaaaaaaff);
		}
	}
}

void DrawSphere(const Sphere& sphere, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivision = 16;
	//	経度分割1つ分の角度
	const float kLonEvery = std::numbers::pi_v<float> * 2.0f / static_cast<float>(kSubdivision);
	//	緯度分割1つ分の角度
	const float kLatEvery = std::numbers::pi_v<float> / static_cast<float>(kSubdivision);

	MyMatrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, sphere.rotate, sphere.center);
	MyMatrix4x4 worldViewProjectionMatrix = worldMatrix * viewProjectionMatrix;

	//	緯度の方向に分割
	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++)
	{
		//	現在の緯度
		float lat = -std::numbers::pi_v<float> / 2.0f + kLatEvery * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; lonIndex++)
		{
			//	現在の経度
			float lon = lonIndex * kLonEvery;

			//	world座標系でのabcを求める
			Vector3 a, b, c;
			a = { (cosf(lat) * cosf(lon)) * sphere.radius ,sinf(lat) * sphere.radius,(cosf(lat) * sinf(lon)) * sphere.radius };
			b = { cosf(lat + kLatEvery) * cosf(lon) * sphere.radius ,sinf(lat + kLatEvery) * sphere.radius ,cosf(lat + kLatEvery) * sinf(lon) * sphere.radius };
			c = { cosf(lat) * cosf(lon + kLonEvery) * sphere.radius ,sinf(lat) * sphere.radius ,cosf(lat) * sinf(lon + kLonEvery) * sphere.radius };

			//	abcをScreen座標系まで変換
			Vector3 aScreen = Transform(a, worldViewProjectionMatrix * viewportMatrix);
			Vector3 bScreen = Transform(b, worldViewProjectionMatrix * viewportMatrix);
			Vector3 cScreen = Transform(c, worldViewProjectionMatrix * viewportMatrix);
			//	abで縦、acで横の線を引く
			Novice::DrawLine(static_cast<int>(aScreen.x), static_cast<int>(aScreen.y),
				static_cast<int>(bScreen.x), static_cast<int>(bScreen.y), color);
			Novice::DrawLine(static_cast<int>(aScreen.x), static_cast<int>(aScreen.y),
				static_cast<int>(cScreen.x), static_cast<int>(cScreen.y), color);
		}
	}

}

void DrawSegment(const Segment& segment, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color)
{
	//	座標変換処理
	Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 finish = Transform(Transform(segment.diff + segment.origin, viewProjectionMatrix), viewportMatrix);
	Novice::DrawLine(static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(finish.x), static_cast<int>(finish.y), color);
}

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	float dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	float nor = sqrtf((v2.x * v2.x) + (v2.y * v2.y) + (v2.z * v2.z));
	float t = dot / (nor * nor);
	t = std::clamp(t, 0.0f, 1.0f);
	result.x = t * v2.x;
	result.y = t * v2.y;
	result.z = t * v2.z;
	
	return result;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 proj = Project(point - segment.origin, segment.diff);
	Vector3 result = segment.origin + proj;
	return result;
}

float Length(const Vector3& vec)
{
	float distance = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return distance;
}

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	if (Length(s2.center - s1.center) <= fabs(s1.radius + s2.radius))
	{
		return true;
	}
	return false;
}

bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	Vector3 n = Normalize(plane.normal - sphere.center);
	float num = (Dot(n, sphere.center) - plane.distance);

	if (fabsf(num) <= fabsf(sphere.radius))
	{
		return true;
	}
	return false;
}

Vector3 Perpendicular(const Vector3& vector) 
{
	if (vector.x != 0.0f || vector.y != 0.0f)
	{
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

void DrawPlane(const Plane& plane, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color) 
{
	//	中心点を決める
	Vector3 center{};
	center = plane.normal * plane.distance;
	Vector3 perpendiculars[4]{};
	//	法線と垂直なベクトルを一つ求める
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	//	[0]の逆ベクトルを求める
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	//	[0]と法線とのクロス積を求める
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	//	[2]の逆ベクトルを求める
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	//	中心点にそれぞれ定数倍して足すと4頂点が出来上がる
	Vector3 points[4]{};
	for (int32_t i = 0; i < 4; i++)
	{
		Vector3 extend = perpendiculars[i] * 2.0f;
		Vector3 point = center + extend;
		points[i] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	//	描画
	Novice::DrawLine(static_cast<int>(points[0].x), static_cast<int>(points[0].y), static_cast<int>(points[3].x), static_cast<int>(points[3].y), color);
	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y), static_cast<int>(points[3].x), static_cast<int>(points[3].y), color);
	Novice::DrawLine(static_cast<int>(points[1].x), static_cast<int>(points[1].y), static_cast<int>(points[2].x), static_cast<int>(points[2].y), color);
	Novice::DrawLine(static_cast<int>(points[2].x), static_cast<int>(points[2].y), static_cast<int>(points[0].x), static_cast<int>(points[0].y), color);

}

bool IsCollision(const Segment& line, const Plane& plane)
{
	//	法線と線の内積を求める
	float dot = Dot(plane.normal, line.diff);
	//	平行時、早期リターン
	if (dot == 0.0f)
	{
		return false;
	}
	//	媒介変数を求める
	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;
	/*Vector3 tb = line.diff * t;
	Vector3 a = line.origin + tb;*/
	Novice::ScreenPrintf(10, 10, "%f", t);
	if (0.0f <= t && t <= 1.0f)
	{
		return true;
	}
	return false;
}

bool IsCollision(const Triangle& triangle, const Segment& segment)
{
	//	法線作る
	Vector3 normal = Normalize(Cross(triangle.vertices[1] - triangle.vertices[0], triangle.vertices[2] - triangle.vertices[1]));
	float distance = Dot(normal, triangle.vertices[0]);
	float t = 0;
	//	媒介変数を求める
	if (Dot(normal, segment.diff) != 0.0f)
	{
		t = (distance - Dot(segment.origin, normal)) / Dot(normal, segment.diff);
	}
	else
	{
		return false;
	}

	//	各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
	Vector3 p = segment.origin + (segment.diff * t);
	Vector3 cross01 = Cross((triangle.vertices[1] - triangle.vertices[0]), (p - triangle.vertices[1]));
	Vector3 cross12 = Cross((triangle.vertices[2] - triangle.vertices[1]), (p - triangle.vertices[2]));
	Vector3 cross20 = Cross((triangle.vertices[0] - triangle.vertices[2]), (p - triangle.vertices[0]));

	float dot01 = Dot(cross01, normal);
	float dot12 = Dot(cross12, normal);
	float dot20 = Dot(cross20, normal);

	if (0.0f <= t && t <= 1.0f)
	{
		//	すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
		if (dot01 >= 0.0f && dot12 >= 0.0f && dot20 >= 0.0f)
		{
			return true;
		}
	}
		
	return false;
}

void DrawTriangle(const Triangle& triangle, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 ver[3]{};
	for (int32_t i = 0; i < 3; i++)
	{
		ver[i] = Transform(Transform(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}

	//	描画
	Novice::DrawLine(static_cast<int>(ver[0].x), static_cast<int>(ver[0].y), static_cast<int>(ver[1].x), static_cast<int>(ver[1].y), color);
	Novice::DrawLine(static_cast<int>(ver[1].x), static_cast<int>(ver[1].y), static_cast<int>(ver[2].x), static_cast<int>(ver[2].y), color);
	Novice::DrawLine(static_cast<int>(ver[2].x), static_cast<int>(ver[2].y), static_cast<int>(ver[0].x), static_cast<int>(ver[0].y), color);
}

bool IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	AABB a{};
	AABB b{};
	a.min.x = (std::min)(aabb1.min.x, aabb1.max.x);	a.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
	a.min.y = (std::min)(aabb1.min.y, aabb1.max.y);	a.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
	a.min.z = (std::min)(aabb1.min.z, aabb1.max.z);	a.max.z = (std::max)(aabb1.min.z, aabb1.max.z);
	b.min.x = (std::min)(aabb2.min.x, aabb2.max.x);	b.max.x = (std::max)(aabb2.min.x, aabb2.max.x);
	b.min.y = (std::min)(aabb2.min.y, aabb2.max.y);	b.max.y = (std::max)(aabb2.min.y, aabb2.max.y);
	b.min.z = (std::min)(aabb2.min.z, aabb2.max.z);	b.max.z = (std::max)(aabb2.min.z, aabb2.max.z);

	if ((a.min.x <= b.max.x && a.max.x >= b.min.x) &&
		(a.min.y <= b.max.y && a.max.y >= b.min.y) &&
		(a.min.z <= b.max.z && a.max.z >= b.min.z))
	{
		return true;
	}
	return false;
}

void DrawAABB(const AABB& aabb, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 ver[8]{};
	//	左下手前
	ver[0] = { aabb.min.x,aabb.min.y,aabb.min.z };
	//	右下手前
	ver[1] = { aabb.max.x,aabb.min.y,aabb.min.z };
	//	左上手前
	ver[2] = { aabb.min.x,aabb.max.y,aabb.min.z };
	//	右上手前
	ver[3] = { aabb.max.x,aabb.max.y,aabb.min.z };
	//	左下奥
	ver[4] = { aabb.min.x,aabb.min.y,aabb.max.z };
	//	右下奥
	ver[5] = { aabb.max.x,aabb.min.y,aabb.max.z };
	//	左上奥
	ver[6] = { aabb.min.x,aabb.max.y,aabb.max.z };
	//	右上奥
	ver[7] = { aabb.max.x,aabb.max.y,aabb.max.z };

	//	座標変換
	for (int32_t i = 0; i < 8; i++)
	{
		ver[i] = Transform(Transform(ver[i], viewProjectionMatrix), viewportMatrix);
	}

	//	描画
	//	下手前
	Novice::DrawLine(static_cast<int>(ver[0].x), static_cast<int>(ver[0].y), static_cast<int>(ver[1].x), static_cast<int>(ver[1].y), color);
	//	上手前
	Novice::DrawLine(static_cast<int>(ver[2].x), static_cast<int>(ver[2].y), static_cast<int>(ver[3].x), static_cast<int>(ver[3].y), color);
	//	下奥
	Novice::DrawLine(static_cast<int>(ver[4].x), static_cast<int>(ver[4].y), static_cast<int>(ver[5].x), static_cast<int>(ver[5].y), color);
	//	上奥
	Novice::DrawLine(static_cast<int>(ver[6].x), static_cast<int>(ver[6].y), static_cast<int>(ver[7].x), static_cast<int>(ver[7].y), color);
	//	左手前
	Novice::DrawLine(static_cast<int>(ver[0].x), static_cast<int>(ver[0].y), static_cast<int>(ver[2].x), static_cast<int>(ver[2].y), color);
	//	左奥
	Novice::DrawLine(static_cast<int>(ver[4].x), static_cast<int>(ver[4].y), static_cast<int>(ver[6].x), static_cast<int>(ver[6].y), color);
	//	右手前
	Novice::DrawLine(static_cast<int>(ver[1].x), static_cast<int>(ver[1].y), static_cast<int>(ver[3].x), static_cast<int>(ver[3].y), color);
	//	右奥
	Novice::DrawLine(static_cast<int>(ver[5].x), static_cast<int>(ver[5].y), static_cast<int>(ver[7].x), static_cast<int>(ver[7].y), color);
	//	左下
	Novice::DrawLine(static_cast<int>(ver[0].x), static_cast<int>(ver[0].y), static_cast<int>(ver[4].x), static_cast<int>(ver[4].y), color);
	//	左上
	Novice::DrawLine(static_cast<int>(ver[2].x), static_cast<int>(ver[2].y), static_cast<int>(ver[6].x), static_cast<int>(ver[6].y), color);
	//	右下
	Novice::DrawLine(static_cast<int>(ver[1].x), static_cast<int>(ver[1].y), static_cast<int>(ver[5].x), static_cast<int>(ver[5].y), color);
	//	右上
	Novice::DrawLine(static_cast<int>(ver[3].x), static_cast<int>(ver[3].y), static_cast<int>(ver[7].x), static_cast<int>(ver[7].y), color);

}

bool IsCollision(const AABB& aabb, const Sphere& sphere)
{
	//	比較
	AABB a{};
	a.min.x = (std::min)(aabb.min.x, aabb.max.x);a.max.x = (std::max)(aabb.min.x, aabb.max.x);
	a.min.y = (std::min)(aabb.min.y, aabb.max.y);a.max.y = (std::max)(aabb.min.y, aabb.max.y);
	a.min.z = (std::min)(aabb.min.z, aabb.max.z);a.max.z = (std::max)(aabb.min.z, aabb.max.z);
	//	最近接点を求める
	Vector3 closestPoint{ std::clamp(sphere.center.x,a.min.x,a.max.x),
		std::clamp(sphere.center.y,a.min.y,a.max.y),
		std::clamp(sphere.center.z,a.min.z,a.max.z) };
	//	最近接点と球の中心との距離を求める
	float distance = Length(closestPoint - sphere.center);
	//	距離が半径よりも小さければ衝突
	if (distance <= std::fabs(sphere.radius))
	{
		return true;
	}
	return false;
}

bool IsCollision(const AABB& aabb, const Segment& segment)
{
	//	媒介変数を求める
	Vector3 tmin{};Vector3 tmax{};
	tmin = (aabb.min - segment.origin) / segment.diff;
	tmax = (aabb.max - segment.origin) / segment.diff;
	//	衝突点の近い方と遠い方(tの大きさ)を求める
	Vector3 tNear{}; Vector3 tFar{};
	tNear.x = (std::min)(tmin.x, tmax.x);tNear.y = (std::min)(tmin.y, tmax.y);tNear.z = (std::min)(tmin.z, tmax.z);
	tFar.x = (std::max)(tmin.x, tmax.x);tFar.y = (std::max)(tmin.y, tmax.y);tFar.z = (std::max)(tmin.z, tmax.z);

	float tmin_ = (std::max)((std::max)(tNear.x, tNear.y), tNear.z);
	float tmax_ = (std::min)((std::min)(tFar.x, tFar.y), tFar.z);

	//	衝突
	if (0.0f <= tmax_ && tmin_ <= tmax_ && tmin_ <= 1.0f)
	{
		return true;
	}

	return false;
}

bool IsCollision(const OBB& obb, const Sphere& sphere)
{
	//	WorldMatrixの生成
	MyMatrix4x4 worldMat;
	worldMat.m[0][0] = obb.orientations[0].x;worldMat.m[0][1] = obb.orientations[1].x;worldMat.m[0][2] = obb.orientations[2].x;
	worldMat.m[1][0] = obb.orientations[0].y;worldMat.m[1][1] = obb.orientations[1].y;worldMat.m[1][2] = obb.orientations[2].y;
	worldMat.m[2][0] = obb.orientations[0].z;worldMat.m[2][1] = obb.orientations[1].z;worldMat.m[2][2] = obb.orientations[2].z;
	worldMat.m[3][0] = obb.center.x; worldMat.m[3][1] = obb.center.y; worldMat.m[3][2] = obb.center.z; worldMat.m[3][3] = 1.0f;

	Vector3 centerInOBBLocalSpace = Transform(sphere.center, Inverse(worldMat));
	
	AABB obbLocal{ {-obb.size.x,-obb.size.y,-obb.size.z},obb.size };

	Sphere sphereLocal{ centerInOBBLocalSpace,sphere.rotate,sphere.radius };
	if (IsCollision(obbLocal, sphereLocal))
	{
		return true;
	}
	return false;
}

void DrawOBB(const OBB& obb, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color)
{
	MyMatrix4x4 worldMat;
	worldMat.m[0][0] = obb.orientations[0].x; worldMat.m[0][1] = obb.orientations[1].x; worldMat.m[0][2] = obb.orientations[2].x;
	worldMat.m[1][0] = obb.orientations[0].y; worldMat.m[1][1] = obb.orientations[1].y; worldMat.m[1][2] = obb.orientations[2].y;
	worldMat.m[2][0] = obb.orientations[0].z; worldMat.m[2][1] = obb.orientations[1].z; worldMat.m[2][2] = obb.orientations[2].z;
	worldMat.m[3][0] = obb.center.x; worldMat.m[3][1] = obb.center.y; worldMat.m[3][2] = obb.center.z; worldMat.m[3][3] = 1.0f;

	AABB obbLocal{ {-obb.size.x,-obb.size.y,-obb.size.z},obb.size };
	DrawAABB(obbLocal, worldMat * viewProjectionMatrix, viewportMatrix, color);
}

OBB SetOBB(const OBB& obb, const MyMatrix4x4& rotateMatrix)
{
	OBB result = obb;
	result.orientations[0].x = rotateMatrix.m[0][0];
	result.orientations[0].y = rotateMatrix.m[0][1];
	result.orientations[0].z = rotateMatrix.m[0][2];

	result.orientations[1].x = rotateMatrix.m[1][0];
	result.orientations[1].y = rotateMatrix.m[1][1];
	result.orientations[1].z = rotateMatrix.m[1][2];

	result.orientations[2].x = rotateMatrix.m[2][0];
	result.orientations[2].y = rotateMatrix.m[2][1];
	result.orientations[2].z = rotateMatrix.m[2][2];

	return result;
}
