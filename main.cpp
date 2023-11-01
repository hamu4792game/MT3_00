#include <Novice.h>
#include "MyMatrix4x4/MyMatrix4x4.h"
#include "Func.h"
#include <numbers>
#include <imgui.h>


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

	//	カメラ座標
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };
	//	行列の生成
	MyMatrix4x4 worldMatrix{};
	MyMatrix4x4 cameraMatrix{};
	MyMatrix4x4 viewMatrix{};
	MyMatrix4x4 projectionMatrix{};
	MyMatrix4x4 viewProjectionMatrix{};
	MyMatrix4x4 viewportMatrix{};

	UINT32 color = 0xffffffff;

	Vector3 rotate{ 0.0f,0.0f,0.0f };
	//Vector3 rotate2{ -0.05f,-2.49f,0.15f };
	Vector3 rotate2{ 0.0f,0.0f,0.0f };

	OBB obb{
		.center{0.0f,0.0f,0.0f},
		.orientations{{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}},
		.size{0.83f,0.26f,0.24f},
	};
	OBB obb2{
		//.center{0.9f,0.66f,0.78f},
		.center{0.9f,0.66f,0.0f},
		.orientations{{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}},
		.size{0.5f,0.37f,0.5f},
	};

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

		//	ImGui
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("rotate", &rotate.x, 0.01f);
		ImGui::DragFloat3("obb", &obb.center.x, 0.01f);
		ImGui::End();

		MyMatrix4x4 rotateMatrix = MakeRotateXMatrix(rotate.x) * MakeRotateYMatrix(rotate.y) * MakeRotateZMatrix(rotate.z);
		obb = SetOBB(obb, rotateMatrix);
		MyMatrix4x4 rotateMatrix2 = MakeRotateXMatrix(rotate2.x) * MakeRotateYMatrix(rotate2.y) * MakeRotateZMatrix(rotate2.z);
		obb2 = SetOBB(obb2, rotateMatrix2);
		
		//	計算処理
		if (IsCollision(obb, obb2))
		{
			color = 0xff0000ff;
		}
		else
		{
			color = 0xffffffff;
		}

		//	行列の計算
		cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);

		viewMatrix = Inverse(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);
		viewProjectionMatrix = viewMatrix * projectionMatrix;
		viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight), 0.0f, 1.0f);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawOBB(obb, viewProjectionMatrix, viewportMatrix, color);
		DrawOBB(obb2, viewProjectionMatrix, viewportMatrix, color);


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
