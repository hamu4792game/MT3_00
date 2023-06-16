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
	if (Length(s2.center - s1.center) <= s1.radius + s2.radius)
	{
		return true;
	}
	return false;
}

bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	Vector3 n = Normalize(plane.normal - sphere.center);
	float num = (Dot(n, sphere.center) - plane.distance);

	if (fabsf(num) <= sphere.radius)
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
