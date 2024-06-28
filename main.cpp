#include <Novice.h>
#include <MyMath.h>

const char kWindowTitle[] = "LE2B_04_オザワ_ユウト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	
	Vector3 controlPoint[3] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f}
	};

	Sphere sphere[3] = {
		{controlPoint[0],0.01f},
		{controlPoint[1],0.01f},
		{controlPoint[2],0.01f}
	};

	Vector3 rotate = {};
	Vector3 translate = {};

	Matrix4x4 rotateMatrix = {};
	Matrix4x4 rotateOBBMatrix = {};
	Matrix4x4 obbWorldMatrix = {};

	int color = BLUE;

	int kWindowWidth = 1280;
	int kWindowHeight = 720;

	//おすすめ初期数値
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		sphere[0].center = controlPoint[0];
		sphere[1].center = controlPoint[1];
		sphere[2].center = controlPoint[2];

		//各種行列の計算
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//WVPMatrixを作る
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		//ViewportMatrixを作る
		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		//OBBの軸を作る
		rotateMatrix = Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z))); 


		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		
		ImGui::SliderFloat3("controlPoint[0]", &controlPoint[0].x, -10.f, 10.f);
		ImGui::SliderFloat3("controlPoint[1]", &controlPoint[1].x, -10.f, 10.f);
		ImGui::SliderFloat3("controlPoint[2]", &controlPoint[2].x, -10.f, 10.f);

	
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewPortMatrix);
		DrawBezier(controlPoint[0], controlPoint[1], controlPoint[2], worldViewProjectionMatrix, viewPortMatrix, color);
		DrawSphere(sphere[0], worldViewProjectionMatrix, viewPortMatrix,BLACK);
		DrawSphere(sphere[1], worldViewProjectionMatrix, viewPortMatrix,BLACK);
		DrawSphere(sphere[2], worldViewProjectionMatrix, viewPortMatrix,BLACK);


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