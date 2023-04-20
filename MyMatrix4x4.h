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
	//	���Z
	Matrix4x4 Add(const Matrix4x4& m1,const Matrix4x4& m2);
	//	���Z
	Matrix4x4 Subtract(const Matrix4x4& m1,const Matrix4x4& m2);
	//	�s��̐�
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	//	�t�s��
	Matrix4x4 Inverse(const Matrix4x4& m);
	//	�]�u�s��
	Matrix4x4 Transpose(const Matrix4x4& m);
	//	�P�ʍs��̍쐬
	Matrix4x4 MakeIdentity4x4();

};

