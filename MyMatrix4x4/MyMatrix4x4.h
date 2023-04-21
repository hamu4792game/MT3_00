#pragma once
#include "Matrix4x4.h"

class MyMatrix4x4
{
public:
	MyMatrix4x4();
	~MyMatrix4x4();
private:
	Matrix4x4 result;
	const int num;
	//	値の初期化
	void Reset();

public:
	//	加算
	Matrix4x4 Add(const Matrix4x4& m1,const Matrix4x4& m2);
	//	減算
	Matrix4x4 Subtract(const Matrix4x4& m1,const Matrix4x4& m2);
	//	行列の積
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	//	逆行列
	Matrix4x4 Inverse(const Matrix4x4& m);
	//	転置行列
	Matrix4x4 Transpose(const Matrix4x4& m);
	//	単位行列の作成
	Matrix4x4 MakeIdentity4x4();

};

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* text);
