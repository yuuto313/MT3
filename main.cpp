#include <Novice.h>
#include <MyMath.h>

const char kWindowTitle[] = "LE2B_04_オザワ_ユウト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//肘と手のwordMatrixを求める
	//資料6~8辺り

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	
	//各配列の値は[0]:肩,[1]:肘,[2]:手を表す

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f}
	};
	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f}
	};
	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f}
	};


	Sphere sphere[3] = {
		{translates[0],0.05f},
		{translates[1],0.05f},
		{translates[2],0.05f}
	};

	Vector3 rotate = {};
	Vector3 translate = {};

	Matrix4x4 rotateMatrix = {};
	Matrix4x4 rotateOBBMatrix = {};
	Matrix4x4 obbWorldMatrix = {};

	//int color = BLUE;

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

		sphere[0].center = translates[0];
		sphere[1].center = translates[1];
		sphere[2].center = translates[2];

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

		ImGui::SliderFloat3("translates[0]", &translates[0].x, -3.f, 3.f);
		ImGui::SliderFloat3("translates[1]", &translates[1].x, -3.f, 3.f);
		ImGui::SliderFloat3("translates[2]", &translates[2].x, -3.f, 3.f);
		ImGui::SliderFloat3("scales[0]", &scales[0].x, -3.f, 3.f);
		ImGui::SliderFloat3("scales[1]", &scales[1].x, -3.f, 3.f);
		ImGui::SliderFloat3("scales[2]", &scales[2].x, -3.f, 3.f);
		ImGui::SliderFloat3("rotates[0]", &rotates[0].x, -3.f, 3.f);
		ImGui::SliderFloat3("rotates[1]", &rotates[1].x, -3.f, 3.f);
		ImGui::SliderFloat3("rotates[2]", &rotates[2].x, -3.f, 3.f);

	
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewPortMatrix);
		DrawSphere(sphere[0], worldViewProjectionMatrix, viewPortMatrix,RED);
		DrawSphere(sphere[1], worldViewProjectionMatrix, viewPortMatrix,GREEN);
		DrawSphere(sphere[2], worldViewProjectionMatrix, viewPortMatrix,BLUE);
		//肩から肘への線
		DrawLine(translates[0], translates[1], worldViewProjectionMatrix, viewPortMatrix, WHITE);
		//肘から手への線
		DrawLine(translates[1], translates[2], worldViewProjectionMatrix, viewPortMatrix, WHITE);
		


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