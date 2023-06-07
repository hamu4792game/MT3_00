﻿#include "MyMatrix4x4/MyMatrix4x4.h"
#include <cassert>
#include <cmath>

MyMatrix4x4::MyMatrix4x4() : m({ 0.0f }) {}

MyMatrix4x4::~MyMatrix4x4() {}

//	加算
MyMatrix4x4 MyMatrix4x4::operator+(const MyMatrix4x4& mat)
{
	MyMatrix4x4 result;
	for (int y = 0; y < result.m.size(); y++)
	{
		for (int x = 0; x < result.m.size(); x++)
		{
			result.m[y][x] = this->m[y][x] + mat.m[y][x];
		}
	}
	return result;
}
//	減算
MyMatrix4x4 MyMatrix4x4::operator-(const MyMatrix4x4& mat)
{
	MyMatrix4x4 result;
	for (int y = 0; y < result.m.size(); y++)
	{
		for (int x = 0; x < result.m.size(); x++)
		{
			result.m[y][x] = this->m[y][x] - mat.m[y][x];
		}
	}
	return result;
}
//	行列の積
MyMatrix4x4 MyMatrix4x4::operator*(const MyMatrix4x4& mat)
{
	MyMatrix4x4 result;

	for (int y = 0; y < m.size(); y++){
		for (int x = 0; x < m.begin()->size(); x++)
		{
			for (int i = 0; i < 4; i++) {
				result.m[y][x] += m[y][i] * mat.m[i][x];
			}
		}
	}

	return result;
}

MyMatrix4x4& MyMatrix4x4::operator=(const MyMatrix4x4& mat)
{
	m = mat.m;
	return *this;
}
//	逆行列
MyMatrix4x4 Inverse(const MyMatrix4x4& m) {
	MyMatrix4x4 result;
	float A = 0.0f;
	A = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] -
		m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
		m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] -

		m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] +

		m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] -
		m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
		m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] -

		m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[1][2] * m.m[2][3] * m.m[3][1] +
		m.m[1][3] * m.m[2][1] * m.m[3][2] -
		m.m[1][3] * m.m[2][2] * m.m[3][1] -
		m.m[1][2] * m.m[2][1] * m.m[3][3] -
		m.m[1][1] * m.m[2][3] * m.m[3][2]) / A;
	result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] -
		m.m[0][2] * m.m[2][3] * m.m[3][1] -
		m.m[0][3] * m.m[2][1] * m.m[3][2] +
		m.m[0][3] * m.m[2][2] * m.m[3][1] +
		m.m[0][2] * m.m[2][1] * m.m[3][3] +
		m.m[0][1] * m.m[2][3] * m.m[3][2]) / A;
	result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] +
		m.m[0][2] * m.m[1][3] * m.m[3][1] +
		m.m[0][3] * m.m[1][1] * m.m[3][2] -
		m.m[0][3] * m.m[1][2] * m.m[3][1] -
		m.m[0][2] * m.m[1][1] * m.m[3][3] -
		m.m[0][1] * m.m[1][3] * m.m[3][2]) / A;
	result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] -
		m.m[0][2] * m.m[1][3] * m.m[2][1] -
		m.m[0][3] * m.m[1][1] * m.m[2][2] +
		m.m[0][3] * m.m[1][2] * m.m[2][1] +
		m.m[0][2] * m.m[1][1] * m.m[2][3] +
		m.m[0][1] * m.m[1][3] * m.m[2][2]) / A;

	result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] -
		m.m[1][2] * m.m[2][3] * m.m[3][0] -
		m.m[1][3] * m.m[2][0] * m.m[3][2] +
		m.m[1][3] * m.m[2][2] * m.m[3][0] +
		m.m[1][2] * m.m[2][0] * m.m[3][3] +
		m.m[1][0] * m.m[2][3] * m.m[3][2]) / A;
	result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] +
		m.m[0][2] * m.m[2][3] * m.m[3][0] +
		m.m[0][3] * m.m[2][0] * m.m[3][2] -
		m.m[0][3] * m.m[2][2] * m.m[3][0] -
		m.m[0][2] * m.m[2][0] * m.m[3][3] -
		m.m[0][0] * m.m[2][3] * m.m[3][2]) / A;
	result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] -
		m.m[0][2] * m.m[1][3] * m.m[3][0] -
		m.m[0][3] * m.m[1][0] * m.m[3][2] +
		m.m[0][3] * m.m[1][2] * m.m[3][0] +
		m.m[0][2] * m.m[1][0] * m.m[3][3] +
		m.m[0][0] * m.m[1][3] * m.m[3][2]) / A;
	result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] +
		m.m[0][2] * m.m[1][3] * m.m[2][0] +
		m.m[0][3] * m.m[1][0] * m.m[2][2] -
		m.m[0][3] * m.m[1][2] * m.m[2][0] -
		m.m[0][2] * m.m[1][0] * m.m[2][3] -
		m.m[0][0] * m.m[1][3] * m.m[2][2]) / A;

	result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] +
		m.m[1][1] * m.m[2][3] * m.m[3][0] +
		m.m[1][3] * m.m[2][0] * m.m[3][1] -
		m.m[1][3] * m.m[2][1] * m.m[3][0] -
		m.m[1][1] * m.m[2][0] * m.m[3][3] -
		m.m[1][0] * m.m[2][3] * m.m[3][1]) / A;
	result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] -
		m.m[0][1] * m.m[2][3] * m.m[3][0] -
		m.m[0][3] * m.m[2][0] * m.m[3][1] +
		m.m[0][3] * m.m[2][1] * m.m[3][0] +
		m.m[0][1] * m.m[2][0] * m.m[3][3] +
		m.m[0][0] * m.m[2][3] * m.m[3][1]) / A;
	result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] +
		m.m[0][1] * m.m[1][3] * m.m[3][0] +
		m.m[0][3] * m.m[1][0] * m.m[3][1] -
		m.m[0][3] * m.m[1][1] * m.m[3][0] -
		m.m[0][1] * m.m[1][0] * m.m[3][3] -
		m.m[0][0] * m.m[1][3] * m.m[3][1]) / A;
	result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] -
		m.m[0][1] * m.m[1][3] * m.m[2][0] -
		m.m[0][3] * m.m[1][0] * m.m[2][1] +
		m.m[0][3] * m.m[1][1] * m.m[2][0] +
		m.m[0][1] * m.m[1][0] * m.m[2][3] +
		m.m[0][0] * m.m[1][3] * m.m[2][1]) / A;

	result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] -
		m.m[1][1] * m.m[2][2] * m.m[3][0] -
		m.m[1][2] * m.m[2][0] * m.m[3][1] +
		m.m[1][2] * m.m[2][1] * m.m[3][0] +
		m.m[1][1] * m.m[2][0] * m.m[3][2] +
		m.m[1][0] * m.m[2][2] * m.m[3][1]) / A;
	result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] +
		m.m[0][1] * m.m[2][2] * m.m[3][0] +
		m.m[0][2] * m.m[2][0] * m.m[3][1] -
		m.m[0][2] * m.m[2][1] * m.m[3][0] -
		m.m[0][1] * m.m[2][0] * m.m[3][2] -
		m.m[0][0] * m.m[2][2] * m.m[3][1]) / A;

	result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] -
		m.m[0][1] * m.m[1][2] * m.m[3][0] -
		m.m[0][2] * m.m[1][0] * m.m[3][1] +
		m.m[0][2] * m.m[1][1] * m.m[3][0] +
		m.m[0][1] * m.m[1][0] * m.m[3][2] +
		m.m[0][0] * m.m[1][2] * m.m[3][1]) / A;

	result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] +
		m.m[0][1] * m.m[1][2] * m.m[2][0] +
		m.m[0][2] * m.m[1][0] * m.m[2][1] -
		m.m[0][2] * m.m[1][1] * m.m[2][0] -
		m.m[0][1] * m.m[1][0] * m.m[2][2] -
		m.m[0][0] * m.m[1][2] * m.m[2][1]) / A;

	return result;
}
//	転置行列
MyMatrix4x4 Transpose(const MyMatrix4x4& m) {
	MyMatrix4x4 result{};
	for (int y = 0; y < result.m.size(); y++) {
		for (int x = 0; x < result.m.size(); x++) {
			result.m[y][x] = m.m[x][y];
		}
	}

	return result;
}
//	単位行列の作成
MyMatrix4x4 MakeIdentity4x4() {
	MyMatrix4x4 result{};
	for (int y = 0; y < result.m.size(); y++) {
		result.m[y][y] = 1.0f;
	}

	return result;
}
//	平行移動行列
MyMatrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	MyMatrix4x4 result{};
	for (int y = 0; y < result.m.size(); y++)
	{
		for (int x = 0; x < result.m.size(); x++)
		{
			if (y == x)
			{
				result.m[y][x] = 1.0f;
			}
			else
			{
				result.m[y][x] = 0.0f;
			}
		}
	}
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}
//	拡大縮小行列
MyMatrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	MyMatrix4x4 result{};
	
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	return result;
}
//	座標変換
Vector3 Transform(const Vector3& vector, const MyMatrix4x4& matrix)
{
	Vector3 resultVec{0.0f,0.0f,0.0f};
	resultVec.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	resultVec.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	resultVec.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0);
	resultVec.x /= w;
	resultVec.y /= w;
	resultVec.z /= w;

	return resultVec;
}

MyMatrix4x4 MakeRotateXMatrix(float radian)
{
	MyMatrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[1][1] = std::cosf(radian);
	result.m[2][2] = std::cosf(radian);

	result.m[2][1] = -std::sinf(radian);
	result.m[1][2] = std::sinf(radian);

	return result;
}

MyMatrix4x4 MakeRotateYMatrix(float radian)
{
	MyMatrix4x4 result{};
	result.m[1][1] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[0][0] = std::cosf(radian);
	result.m[2][2] = std::cosf(radian);

	result.m[0][2] = -std::sinf(radian);
	result.m[2][0] = std::sinf(radian);

	return result;
}

MyMatrix4x4 MakeRotateZMatrix(float radian)
{
	MyMatrix4x4 result{};
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[0][0] = std::cosf(radian);
	result.m[1][1] = std::cosf(radian);

	result.m[1][0] = -std::sinf(radian);
	result.m[0][1] = std::sinf(radian);

	return result;
}

MyMatrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	MyMatrix4x4 result{};

	MyMatrix4x4 rotateMatrix;
	rotateMatrix = MakeRotateXMatrix(rotate.x) * MakeRotateYMatrix(rotate.y) * MakeRotateZMatrix(rotate.z);
	result = rotateMatrix;

	for (int i = 0; i < 3; i++)
	{
		result.m[0][i] = scale.x * rotateMatrix.m[0][i];
		result.m[1][i] = scale.y * rotateMatrix.m[1][i];
		result.m[2][i] = scale.z * rotateMatrix.m[2][i];
	}
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

MyMatrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	MyMatrix4x4 result;
	for (int y = 0; y < result.m.size(); y++)
	{
		for (int x = 0; x < result.m.size(); x++)
		{
			result.m[y][x] = 0.0f;
		}
	}
	result.m[0][0] = (1.0f / aspectRatio) * (1.0f / tanf(fovY / 2.0f));
	result.m[1][1] = 1.0f / tanf(fovY / 2.0f);
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

	return result;
}

MyMatrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	MyMatrix4x4 result;
	for (int y = 0; y < result.m.size(); y++)
	{
		for (int x = 0; x < result.m.size(); x++)
		{
			result.m[y][x] = 0.0f;
		}
	}
	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[3][3] = 1.0f;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);

	return result;
}

MyMatrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	MyMatrix4x4 result;
	for (int y = 0; y < result.m.size(); y++)
	{
		for (int x = 0; x < result.m.size(); x++)
		{
			result.m[y][x] = 0.0f;
		}
	}
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][3] = 1.0f;

	result.m[3][0] = left + (width / 2.0f);
	result.m[3][1] = top + (height / 2.0f);
	result.m[3][2] = minDepth;

	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 resultVec = { 0.0f,0.0f,0.0f };
	resultVec.x = (v1.y * v2.z) - (v1.z * v2.y);
	resultVec.y = (v1.z * v2.x) - (v1.x * v2.z);
	resultVec.z = (v1.x * v2.y) - (v1.y * v2.x);
	return resultVec;
}
