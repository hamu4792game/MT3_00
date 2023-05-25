#include "Func.h"
#include <Novice.h>

void DrawGrid(const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix)
{
	//	Gridの半分の幅
	const float kGridHalfWidth = 2.0f;
	//	分割数
	const unsigned int kSubdivision = 10;
	//	1つ分の長さ
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);
	Vector3 start{ 0.0f,0.0f,10.0f };
	Vector3 translate{};

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++)
	{
		translate.z = start.z - (xIndex * kGridHalfWidth);
		Vector3 screen = Transform(translate, viewProjectionMatrix);
		screen = Transform(screen, viewportMatrix);

		Novice::DrawLine(static_cast<int>(screen.x), static_cast<int>(screen.z),
			static_cast<int>(screen.x + kGridEvery), static_cast<int>(screen.z + kGridEvery), 0xaaaaaaff);
	}

}
