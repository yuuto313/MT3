#include <Novice.h>
#include "MyMath.h"

const char kWindowTitle[] = "LE2B_04_オザワ_ユウト";

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Ball ball{};
	ball.position = { 1.2f,0.0f,0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	Vector3 centor = { 0.f,0.f,0.f };
	bool start = false;
	float angle = 0.0f;
	float angularVelocity = 3.14f;
	float deltaTime = 1.0f / 60.f;
	float radius = 0.8f;
	
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

		//各種行列の計算
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//WVPMatrixを作る
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		//ViewportMatrixを作る
		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		if (start) {
			//角度を更新
			angle += angularVelocity * deltaTime;

			//ボールの位置を更新
			ball.position.x = std::cos(angle) + radius;
			ball.position.y = std::sin(angle) + radius;
			ball.position.z = centor.z;

		}

	
		ImGui::Begin("Window");
		ImGui::Checkbox("start", &start);
		ImGui::DragFloat3("ball.position", &ball.position.x);
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewPortMatrix);
		DrawSphere(ball, worldViewProjectionMatrix, viewPortMatrix,ball.color);


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