#include "Func.h"
#include <Novice.h>

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;
	const unsigned int kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);
	MyMatrix4x4 matrix;
	Vector3 start{ 0.0f,0.0f,10.0f };
	Vector3 translate{};

	for (unsigned int i = 0; i < kSubdivision; i++)
	{
		translate.z = start.z - (i * kGridHalfWidth);
		Matrix4x4 worldMatrix = matrix.MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, translate);
		Matrix4x4 cameraMatrix = matrix.MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, {0.0f,0.0f,-50.0f});
		Matrix4x4 viewMatrix = matrix.Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = matrix.MakePerspectiveFovMatrix(0.45f, static_cast<float>(1280) / static_cast<float>(720), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = matrix.Multiply(worldMatrix, matrix.Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = matrix.MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(1280), static_cast<float>(720), 0.0f, 1.0f);

	}

}
