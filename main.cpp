#include <Novice.h>
#include "MyMatrix4x4/MyMatrix4x4.h"

#include <numbers>

const char* kWindowTitle = "LE2A_17_マツイユウセイ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR /*lpCmdLine*/, _In_ int /*nShowCmd*/) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	MyMatrix4x4 matrix;
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };
	Vector3 cameraPosition = { 0.0f,0.0f,-500.0f };

	Matrix4x4 worldMatrix{};
	Matrix4x4 cameraMatrix{};
	Matrix4x4 viewMatrix{};
	Matrix4x4 projectionMatrix{};
	Matrix4x4 worldViewProjectionMatrix{};
	Matrix4x4 viewportMatrix{};

	Vector3 screenVertices[3]{};
	Vector3 kLocalVertices[3] = {
		{0.0f,50.0f,0.0f},
		{-50.0f,-50.0f,0.0f},
		{50.0f,-50.0f,0.0f}
	};

	Vector3 cross{};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		rotate.y += 2.0f * std::numbers::pi_v<float> / 90.0f;

		if (rotate.y >= 2.0f * std::numbers::pi_v<float>)
		{
			rotate.y = 0.0f;
		}

		if (keys[DIK_W])
		{
			translate.z -= 5.0f;
		}
		if (keys[DIK_S])
		{
			translate.z += 5.0f;
		}

		if (keys[DIK_A])
		{
			translate.x -= 5.0f;
		}
		if (keys[DIK_D])
		{
			translate.x += 5.0f;
		}

		//	行列の計算
		worldMatrix = matrix.MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		cameraMatrix = matrix.MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);

		viewMatrix = matrix.Inverse(cameraMatrix);
		projectionMatrix = matrix.MakePerspectiveFovMatrix(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);
		worldViewProjectionMatrix = matrix.Multiply(worldMatrix, matrix.Multiply(viewMatrix, projectionMatrix));

		viewportMatrix = matrix.MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight), 0.0f, 1.0f);

		
		for (UINT32 i = 0; i < 3; i++)
		{
			Vector3 ndcVertex = matrix.Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = matrix.Transform(ndcVertex, viewportMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		

		cross = matrix.Cross(screenVertices[0], screenVertices[1]);
		Vector3 backCulling = matrix.Cross(cameraPosition, cross);
		if (backCulling.x <= 0.0f)
		{
			Novice::DrawTriangle(static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
				static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y), 0xff0000ff, kFillModeSolid);
		}


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
