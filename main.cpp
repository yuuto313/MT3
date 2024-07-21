#include <Novice.h>
#include "MyMath.h"

const char kWindowTitle[] = "LE2B_04_オザワ_ユウト";

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Plane plane{};
	plane.normal = Normalize({ -0.2f,0.9f,-0.3f });
	plane.distance = 0.0f;

	Ball ball{};
	ball.position = { 0.8f,1.2f,0.3f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	Segment segment{};
	segment.origin = {};
	segment.diff = {};

	Capsule capsule{};
	capsule.segment = segment;
	capsule.radius = ball.radius;

	bool start = false;
	float deltaTime = 1.0f / 60.f;
	//反発係数
	float e = 0.8f;
	//前フレームの位置を保持
	Vector3 newPosition = ball.position;
	
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


		//加速度も速度もどちらも秒を基準とした値である
		//それが、1/60秒間(deltaTime)適用されたと考える
		ball.velocity += ball.acceleration * deltaTime;
		ball.position += ball.velocity * deltaTime;
		newPosition = ball.position + ball.velocity * deltaTime;

		capsule.segment.origin = ball.position;
		capsule.segment.diff = newPosition - ball.position;

		if (start) {
			ball.acceleration = { 0.0f,-100.8f,0.0f };
			if (IsCollisionCapsuleAndPlane(capsule, plane)) {
				Vector3 reflected = Reflect(ball.velocity, plane.normal);
				Vector3 projectToNormal = Project(reflected, plane.normal);
				Vector3 movingDirection = reflected - projectToNormal;
				ball.velocity = projectToNormal * e + movingDirection;

				//位置を修正する
				float penetrationDepth = ball.radius - Dot(ball.position, plane.normal) - plane.distance;
				ball.position += plane.normal * penetrationDepth;
			}
			newPosition = ball.position;
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
		DrawPlane(plane, worldViewProjectionMatrix, viewPortMatrix, WHITE);
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