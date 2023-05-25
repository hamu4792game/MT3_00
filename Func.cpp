#include "Func.h"
#include <Novice.h>
#include <numbers>

void DrawGrid(const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix)
{
	//	Gridの半分の幅
	const float kGridHalfWidth = 2.0f;
	//	分割数
	const unsigned int kSubdivision = 10;
	//	1つ分の長さ
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	Vector3 startLocal{ kGridHalfWidth / float(kSubdivision),0.0f,0.0f};
	Vector3 endLocal{ -kGridHalfWidth / float(kSubdivision),0.0f,0.0f };

	Vector3 translate{ 0.0f,0.0f,kGridEvery / 2.0f };

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++)
	{
		MyMatrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, translate);
		MyMatrix4x4 worldViewProjectionMatrix = worldMatrix * viewProjectionMatrix;

		Vector3 startScreen = Transform(startLocal, worldViewProjectionMatrix);
		startScreen = Transform(startScreen, viewportMatrix);
		Vector3 endScreen = Transform(endLocal, worldViewProjectionMatrix);
		endScreen = Transform(endScreen, viewportMatrix);

		if (translate.z == 0.0f)
		{
			Novice::DrawLine(static_cast<int>(startScreen.x), static_cast<int>(startScreen.y),
				static_cast<int>(endScreen.x), static_cast<int>(endScreen.y), 0xff);
		}
		else
		{
			Novice::DrawLine(static_cast<int>(startScreen.x), static_cast<int>(startScreen.y),
				static_cast<int>(endScreen.x), static_cast<int>(endScreen.y), 0xaaaaaaff);
		}
		

		translate.z -= kGridEvery / float(kSubdivision);
	}

	translate = { -kGridEvery / 2.0f,0.0f,0.0f };

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++)
	{
		MyMatrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,std::numbers::pi_v<float> / 2.0f,0.0f }, translate);
		MyMatrix4x4 worldViewProjectionMatrix = worldMatrix * viewProjectionMatrix;

		Vector3 startScreen = Transform(startLocal, worldViewProjectionMatrix);
		startScreen = Transform(startScreen, viewportMatrix);
		Vector3 endScreen = Transform(endLocal, worldViewProjectionMatrix);
		endScreen = Transform(endScreen, viewportMatrix);

		if (translate.x == 0.0f)
		{
			Novice::DrawLine(static_cast<int>(startScreen.x), static_cast<int>(startScreen.y),
				static_cast<int>(endScreen.x), static_cast<int>(endScreen.y), 0xff);
		}
		else
		{
			Novice::DrawLine(static_cast<int>(startScreen.x), static_cast<int>(startScreen.y),
				static_cast<int>(endScreen.x), static_cast<int>(endScreen.y), 0xaaaaaaff);
		}
		translate.x += kGridEvery / float(kSubdivision);
	}

}

void DrawSphere(const Sphere& sphere, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivision = 16;
	//	緯度分割1つ分の角度
	const float kLonEvery = std::numbers::pi_v<float> / 8.0f;
	//	経度分割1つ分の角度
	const float kLatEvery = std::numbers::pi_v<float> / 8.0f;

	MyMatrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,std::numbers::pi_v<float> / 2.0f,0.0f }, sphere.center);
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

			Vector3 a, b, c;
			a = { (cosf(lat) * cosf(lon)) ,sinf(lat) ,(cosf(lat) * sinf(lon))  };
			b = { cosf(lat + kLatEvery) * cosf(lon) ,sinf(lat + kLatEvery) ,cosf(lat + kLatEvery) * sinf(lon)  };
			c = { cosf(lat) * cosf(lon + kLonEvery) ,sinf(lat) ,cosf(lat) * sinf(lon + kLonEvery)  };

			Vector3 aScreen = Transform(a, worldViewProjectionMatrix);
			aScreen = Transform(aScreen, viewportMatrix);
			Vector3 bScreen = Transform(b, worldViewProjectionMatrix);
			bScreen = Transform(bScreen, viewportMatrix);
			Vector3 cScreen = Transform(c, worldViewProjectionMatrix);
			cScreen = Transform(cScreen, viewportMatrix);

			Novice::DrawLine(static_cast<int>(aScreen.x), static_cast<int>(aScreen.y),
				static_cast<int>(bScreen.x), static_cast<int>(bScreen.y), color);
			Novice::DrawLine(static_cast<int>(aScreen.x), static_cast<int>(aScreen.y),
				static_cast<int>(cScreen.x), static_cast<int>(cScreen.y), color);
		}
	}

}
