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
public:
	//	‰ÁZ
	Matrix4x4 Add(const Matrix4x4& m1,const Matrix4x4& m2);
	//	Œ¸Z
	Matrix4x4 Subtract(const Matrix4x4& m1,const Matrix4x4& m2);
	//	s—ñ‚ÌÏ
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	//	‹ts—ñ
	Matrix4x4 Inverse(const Matrix4x4& m);
	//	“]’us—ñ
	Matrix4x4 Transpose(const Matrix4x4& m);
	//	’PˆÊs—ñ‚Ìì¬
	Matrix4x4 MakeIdentity4x4();

};

