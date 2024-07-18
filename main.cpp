#include <Novice.h>
#include "MyMath.h"

const char kWindowTitle[] = "LE2B_04_オザワ_ユウト";

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	
	Spring spring{};
	spring.anchor = { 0.0f,0.0f,0.0f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	Ball ball{};
	ball.position = { 1.2f,0.0f,0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	float deltaTime;

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

		deltaTime = 1.0f / 60.f;

		Vector3 diff = ball.position - spring.anchor;
		float length = Length(diff);
		if (length != 0.0f) {
			Vector3 direction = Normalize(diff);
			Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
			Vector3 displacement = length * (ball.position - restPosition);
			Vector3 restoringForce = -spring.stiffness * displacement;
			//減衰抵抗を計算する
			Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
			//減衰抵抗も加味して、物体にかかる力を計算する
			Vector3 force = restoringForce + dampingForce;
			ball.acceleration = force / ball.mass;
		}

		//加速度も速度もどちらも秒を基準とした値である
		//それが、1/60秒間(deltaTime)適用されたと考える
		ball.velocity += ball.acceleration * deltaTime;
		ball.position += ball.velocity * deltaTime;



		ImGui::Begin("Window");
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewPortMatrix);
		DrawLine(spring.anchor, ball.position, worldViewProjectionMatrix, viewPortMatrix,WHITE);
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