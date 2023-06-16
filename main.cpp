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

	Plane plane{ 0.0f,1.0f,0.0f };
	UINT32 plameColor = 0xffffffff;

	Segment line{ 0.0f };
	line.origin = { 0.0f,1.0f,0.0f };
	line.diff = { 0.0f,-1.0f,0.0f };

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

		//	計算処理
		
		if (IsCollision(line, plane))
		{
			color = 0xff0000ff;
		}
		else
		{
			color = 0xffffffff;
		}
		
		//	ImGui
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SegmentOrogin", &line.origin.x, 0.01f);
		ImGui::DragFloat3("SegmentDiff", &line.diff.x, 0.01f);
		ImGui::DragFloat3("Plane.Normal", &plane.normal.x, 0.01f);
		plane.normal = Normalize(plane.normal);
		ImGui::DragFloat("PlaneDistance", &plane.distance, 0.01f);
		ImGui::End();

		//	行列の計算
		cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);

		viewMatrix = Inverse(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);
		viewProjectionMatrix = viewMatrix * projectionMatrix;
		viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight), 0.0f, 1.0f);

		//	座標変換処理

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		Vector3 start = Transform(Transform(line.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 finish = Transform(Transform(line.diff + line.origin, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(finish.x), static_cast<int>(finish.y), color);

		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, plameColor);

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
