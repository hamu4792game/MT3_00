#pragma once

struct Vector3D {
    float x, y, z;
};

//  加算
Vector3D Add(const Vector3D& v1, const Vector3D& v2);
//  減算
Vector3D Subtract(const Vector3D& v1, const Vector3D& v2);
//  スカラー倍
Vector3D Multiply(float scalar, const Vector3D& v);
//  内積
float Dot(const Vector3D& v1, const Vector3D& v2);
//  長さ（ノルム）
float Length(const Vector3D& v);
//  正規化
Vector3D Normalize(const Vector3D& v);

static const int kColumnWidth = 60;
//  描画関数
void VectorScreenPrintf(int x, int y, const Vector3D& vector, const char* label);