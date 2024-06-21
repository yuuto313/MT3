#include "MyMath.h"
#include <array>

//クロス積（ベクトル積）
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
};
//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
//長さ
float Length(const Vector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
//正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result;
	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);
	return Vector3(result);
}
//積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result{};
	float detA = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
	if (detA != 0) {
		result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]) / detA;
		result.m[0][1] = (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]) / detA;
		result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]) / detA;
		result.m[0][3] = (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]) / detA;

		result.m[1][0] = (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]) / detA;
		result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]) / detA;
		result.m[1][2] = (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]) / detA;
		result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]) / detA;

		result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]) / detA;
		result.m[2][1] = (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]) / detA;
		result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]) / detA;
		result.m[2][3] = (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]) / detA;

		result.m[3][0] = (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]) / detA;
		result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]) / detA;
		result.m[3][2] = (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]) / detA;
		result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]) / detA;
	}
	return result;
}

//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;

}

//平行移動
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{};
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1;
	return result;
}
//拡縮
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1;
	return result;
}


//X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};

	result.m[0][0] = 1;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[3][3] = 1;
	return result;
}
//Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};
	result.m[0][0] = std::cos(radian);
	result.m[0][2] = -std::sin(radian);
	result.m[1][1] = 1;
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[3][3] = 1;
	return result;
}
//Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[2][2] = 1;
	result.m[3][3] = 1;
	return result;
}

//アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	Matrix4x4 worldMatrix = Multiply(scaleMatrix, Multiply(rotateXYZMatrix, translateMatrix));
	return worldMatrix;
}

//cotangent(cot)、tanの逆数
float cot(float other) {
	return 1 / tan(other);
}

//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{};
	result.m[0][0] = 1 / aspectRatio * cot(fovY / 2);
	result.m[1][1] = cot(fovY / 2);
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	return result;
}
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result{};
	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1;
	return result;
}
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{};
	result.m[0][0] = width / 2;
	result.m[1][1] = -height / 2;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + width / 2;
	result.m[3][1] = top + height / 2;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;
	return result;
}


// 4x4行列の数値表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x + kColumnWidth * 5, y, "%s", label);
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

//垂線
Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

//平面を描画
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewMatrix, uint32_t color) {
	Vector3 center = Multiply(plane.distance, plane.normal);//1.中心点を決める
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));//2.法線と垂直なベクトルを一つ決める
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };//3.２の逆ベクトルを求める
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);//4.２と法線とのクロス積を求める
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };//5.４の逆ベクトルを求める
	//6.２～５のベクトルを中心点にそれぞれ定数倍して足すと４頂点が出来上がる
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewMatrix);
	}
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[0].x), int(points[0].y), color);
}

//線を描画
void DrawLine(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewMatrix, uint32_t color) {

	Vector3 origin = Transform(Transform(segment.origin, viewProjectionMatrix), viewMatrix);
	Vector3 diff = Transform(Transform(segment.diff, viewProjectionMatrix), viewMatrix);

	Novice::DrawLine(int(origin.x), int(origin.y), int(diff.x), int(diff.y), color);

}

//三角形を描画
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewMatrix, uint32_t color) {
	Vector3 a = Transform(Transform(triangle.vertices[0], viewProjectionMatrix), viewMatrix);
	Vector3 b = Transform(Transform(triangle.vertices[1], viewProjectionMatrix), viewMatrix);
	Vector3 c = Transform(Transform(triangle.vertices[2], viewProjectionMatrix), viewMatrix);

	Novice::DrawTriangle(int(a.x), int(a.y), int(b.x), int(b.y), int(c.x), int(c.y), color, kFillModeWireFrame);
}

//グリッドを描画
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {

	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 16;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);//一つ分の長さ
	//奥から手前への線を徐々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		//上の情報を使ってワールド座標系上の始点と終点を求める
		Vector3 start(-kGridHalfWidth + xIndex * kGridEvery, 0.0f, -kGridHalfWidth);
		Vector3 end(-kGridHalfWidth + xIndex * kGridEvery, 0.0f, kGridHalfWidth);

		// スクリーン座標系まで変換
		Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, start);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, end);

		Matrix4x4 startWvpMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Matrix4x4 endWvpMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);

		Vector3 startLocal = Transform(start, startWvpMatrix);
		Vector3 endLocal = Transform(end, endWvpMatrix);

		Vector3 startScreen = Transform(startLocal, viewportMatrix);
		Vector3 endScreen = Transform(endLocal, viewportMatrix);

		//変換した座標を使って表示。色は薄い灰色。（0xAAAAAAFF）、原点は黒ぐらい
		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), 0xAAAAAAFF);
	}

	//左から右もおなじように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		//奥から手前が左右に変わるだけ

		Vector3 start(-kGridHalfWidth, 0.0f, -kGridHalfWidth + zIndex * kGridEvery);
		Vector3 end(kGridHalfWidth, 0.0f, -kGridHalfWidth + zIndex * kGridEvery);

		// スクリーン座標系まで変換
		Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, start);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, end);

		Matrix4x4 startWvpMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Matrix4x4 endWvpMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);

		Vector3 startLocal = Transform(start, startWvpMatrix);
		Vector3 endLocal = Transform(end, endWvpMatrix);

		Vector3 startScreen = Transform(startLocal, viewportMatrix);
		Vector3 endScreen = Transform(endLocal, viewportMatrix);

		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), 0xAAAAAAFF);
	}

}

//スフィアを描画
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	//分割数
	const uint32_t kSubdivision = 16;
	//経度分割一つ分の角度
	const float kLonEvery = (2 * (static_cast<float>(M_PI))) / kSubdivision;
	//緯度分割一つ分の角度
	const float kLatEvery = (static_cast<float>(M_PI)) / kSubdivision;



	//緯度の方向に分割　-π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -(static_cast<float>(M_PI)) / 2.0f + kLatEvery * latIndex;//現在の緯度

		//経度の方向に分割　0~2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度

			//world座標系でのa,b,cを求める
			Vector3 a = { (sphere.radius) * cosf(lat) * cosf(lon), (sphere.radius) * sinf(lat), (sphere.radius) * cosf(lat) * sin(lon) };
			Vector3 b = { (sphere.radius) * cosf(lat + kLatEvery) * cosf(lon), (sphere.radius) * sinf(lat + kLatEvery), (sphere.radius) * cos(lat + kLatEvery) * sinf(lon) };
			Vector3 c = { (sphere.radius) * cosf(lat) * cosf(lon + kLonEvery), (sphere.radius) * sinf(lat), (sphere.radius) * cosf(lat) * sinf(lon + kLonEvery) };

			Matrix4x4 worldMatrixA = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 worldMatrixB = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 worldMatrixC = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);

			Matrix4x4 wvpMatrixA = Multiply(worldMatrixA, viewProjectionMatrix);
			Matrix4x4 wvpMatrixB = Multiply(worldMatrixB, viewProjectionMatrix);
			Matrix4x4 wvpMatrixC = Multiply(worldMatrixC, viewProjectionMatrix);

			Vector3 localA = Transform(a, wvpMatrixA);
			Vector3 localB = Transform(b, wvpMatrixB);
			Vector3 localC = Transform(c, wvpMatrixC);

			Vector3 screenA = Transform(localA, viewportMatrix);
			Vector3 screenB = Transform(localB, viewportMatrix);
			Vector3 screenC = Transform(localC, viewportMatrix);

			// ab, bcで線を引く
			Novice::DrawLine(static_cast<int>(screenA.x), static_cast<int>(screenA.y), static_cast<int>(screenB.x), static_cast<int>(screenB.y), color);
			Novice::DrawLine(static_cast<int>(screenA.x), static_cast<int>(screenA.y), static_cast<int>(screenC.x), static_cast<int>(screenC.y), color);
		}
	}
}

//直方体を描画
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	//手前側
	//左下
	Vector3 leftBottom = { aabb.min.x,aabb.min.y,aabb.min.z };
	leftBottom = Transform(Transform(leftBottom, viewProjectionMatrix), viewportMatrix);

	//左上
	Vector3 leftTop = { aabb.min.x,aabb.max.y,aabb.min.z };
	leftTop = Transform(Transform(leftTop, viewProjectionMatrix), viewportMatrix);

	//右上
	Vector3 rightTop = { aabb.max.x,aabb.max.y,aabb.min.z };
	rightTop = Transform(Transform(rightTop, viewProjectionMatrix), viewportMatrix);

	//右下
	Vector3 rightBottom = { aabb.max.x,aabb.min.y,aabb.min.z };
	rightBottom = Transform(Transform(rightBottom, viewProjectionMatrix), viewportMatrix);

	//奥側
	//左下
	Vector3 backLeftBottom = { aabb.min.x,aabb.min.y,aabb.max.z };
	backLeftBottom = Transform(Transform(backLeftBottom, viewProjectionMatrix), viewportMatrix);

	//左上
	Vector3 backLeftTop = { aabb.min.x,aabb.max.y,aabb.max.z };
	backLeftTop = Transform(Transform(backLeftTop, viewProjectionMatrix), viewportMatrix);

	//右上
	Vector3 backRightTop = { aabb.max.x,aabb.max.y,aabb.max.z };
	backRightTop = Transform(Transform(backRightTop, viewProjectionMatrix), viewportMatrix);

	//右下
	Vector3 backRightBottom = { aabb.max.x,aabb.min.y,aabb.max.z };
	backRightBottom = Transform(Transform(backRightBottom, viewProjectionMatrix), viewportMatrix);

	//手前側
	//左下から左上
	Novice::DrawLine(int(leftBottom.x), int(leftBottom.y), int(leftTop.x), int(leftTop.y), color);
	//左上から右上
	Novice::DrawLine(int(leftTop.x), int(leftTop.y), int(rightTop.x), int(rightTop.y), color);
	//右上から右下
	Novice::DrawLine(int(rightTop.x), int(rightTop.y), int(rightBottom.x), int(rightBottom.y), color);
	//右下から左下
	Novice::DrawLine(int(rightBottom.x), int(rightBottom.y), int(leftBottom.x), int(leftBottom.y), color);

	//手前から奥に
	//左下から奥の左下
	Novice::DrawLine(int(leftBottom.x), int(leftBottom.y), int(backLeftBottom.x), int(backLeftBottom.y), color);
	//左上から奥の左上
	Novice::DrawLine(int(leftTop.x), int(leftTop.y), int(backLeftTop.x), int(backLeftTop.y), color);
	//右上から奥の右上
	Novice::DrawLine(int(rightTop.x), int(rightTop.y), int(backRightTop.x), int(backRightTop.y), color);
	//右下から奥の右下
	Novice::DrawLine(int(rightBottom.x), int(rightBottom.y), int(backRightBottom.x), int(backRightBottom.y), color);

	//奥側
	//左下から左上
	Novice::DrawLine(int(backLeftBottom.x), int(backLeftBottom.y), int(backLeftTop.x), int(backLeftTop.y), color);
	//左上から右上
	Novice::DrawLine(int(backLeftTop.x), int(backLeftTop.y), int(backRightTop.x), int(backRightTop.y), color);
	//右上から右下
	Novice::DrawLine(int(backRightTop.x), int(backRightTop.y), int(backRightBottom.x), int(backRightBottom.y), color);
	//右下から左下
	Novice::DrawLine(int(backRightBottom.x), int(backRightBottom.y), int(backLeftBottom.x), int(backLeftBottom.y), color);

}

//void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
//{
//	// OBBの8頂点を計算
//	std::array<Vector3, 8> vertices;
//	Vector3 axis[3] = { obb.orientations[0] * obb.size.x, obb.orientations[1] * obb.size.y, obb.orientations[2] * obb.size.z };
//
//	vertices[0] = obb.center - axis[0] - axis[1] - axis[2];
//	vertices[1] = obb.center + axis[0] - axis[1] - axis[2];
//	vertices[2] = obb.center - axis[0] + axis[1] - axis[2];
//	vertices[3] = obb.center + axis[0] + axis[1] - axis[2];
//	vertices[4] = obb.center - axis[0] - axis[1] + axis[2];
//	vertices[5] = obb.center + axis[0] - axis[1] + axis[2];
//	vertices[6] = obb.center - axis[0] + axis[1] + axis[2];
//	vertices[7] = obb.center + axis[0] + axis[1] + axis[2];
//
//	
//}

//正射影ベクトル（ベクトル射影）
Vector3 Project(const Vector3& v1, const Vector3& v2) {
	//v1とv2の内積
	float dotProduct = Dot(v1, v2);

	//v2の長さ
	float v2Length = Length(v2);

	float scaleFactor = dotProduct / v2Length;
	Vector3 projection = { v2.x * scaleFactor, v2.y * scaleFactor, v2.z * scaleFactor };

	return projection;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	// 始点から点へのベクトル
	Vector3 toPoint = Subtract(point, segment.origin);

	// 線分の方向ベクトル
	Vector3 segmentDir = segment.diff;

	// 線分の方向ベクトルの長さの二乗
	float segmentDirLengthSquared = segmentDir.x * segmentDir.x + segmentDir.y * segmentDir.y + segmentDir.z * segmentDir.z;

	// 線分の方向ベクトルが0ベクトルである場合、始点が最近接点となる
	if (segmentDirLengthSquared == 0) {
		return segment.origin;
	}

	// 線分の方向ベクトルと点から始点へのベクトルの内積を計算
	float t = Dot(toPoint, segmentDir) / segmentDirLengthSquared;

	// tが0未満の場合、最近接点は始点側の延長上にある
	if (t < 0) {
		return segment.origin;
	}

	// tが1より大きい場合、最近接点は終点側の延長上にある
	if (t > 1) {
		return Vector3{ segment.origin.x + segment.diff.x, segment.origin.y + segment.diff.y, segment.origin.z + segment.diff.z };
	}
	// 最近接点を計算して返す
	return { segment.origin.x + segment.diff.x * t, segment.origin.y + segment.diff.y * t, segment.origin.z + segment.diff.z * t };
}

//球と球の当たり判定
bool IsCollisionSphere(const Sphere& s1, const Sphere& s2) {
	//2つの球の中心点関の距離を求める
	float distance = Length(s2.center - s1.center);
	//半径の合計よりも短ければ衝突
	if (distance <= s1.radius + s2.radius) {
		return true;
	} else {
		return false;
	}
}

//球と平面の当たり判定
bool IsCollisionPlane(const Sphere& sphere, const Plane& plane) {

	float distance = std::abs(Dot(plane.normal, sphere.center) - plane.distance);
	if (distance <= sphere.radius) {
		return true;
	} else {
		return false;
	}
}

//線と平面の当たり判定
bool isCollisionLine(const Segment& segment, const Plane& plane) {
	//法線と線の内積を求める
	float dot = Dot(plane.normal, segment.diff);

	//垂線＝平行であるので、衝突してるはずがない
	if (dot == 0.f) {
		return false;
	}

	//tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
	//tの値と線の種類によって衝突してるか判定する

	// tが線分の範囲内にあるかどうかをチェック
	if (t >= 0 && t <= 1) {
		// 線と平面が交差する
		return true;
	}

	// 線分の範囲外で交差しない
	return false;
}

//三角形と線の当たり判定
bool IsCollisionTriangle(const Triangle& triangle, const Segment& segment) {

	Vector3 v01 = triangle.vertices[1] - triangle.vertices[0];
	Vector3 v12 = triangle.vertices[2] - triangle.vertices[1];
	Vector3 v20 = triangle.vertices[2] - triangle.vertices[0];

	Vector3 p = segment.origin - segment.diff;

	Vector3 v1p = p - triangle.vertices[1];
	Vector3 v2p = p - triangle.vertices[2];
	Vector3 v0p = p - triangle.vertices[0];

	//各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積をとる
	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);


	// 法線ベクトル
	Vector3 normal = Cross(v01, v12);

	//すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross12, normal) >= 0.0f &&
		Dot(cross20, normal) >= 0.0f) {
		return true;
	} else {
		return false;
	}
}

//AABBとAABBの衝突判定
bool IsCollisionAABB(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && //x軸
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&//y軸
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	} else {
		return false;
	}
}

//AABBと球の当たり判定
bool IsCollisionSphereAndAABB(const AABB& aabb, const Sphere& sphere) {
	//最近接点を求める
	Vector3 closestPoint{ std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
						  std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
						  std::clamp(sphere.center.z,aabb.min.z,aabb.max.z) };

	//最近接点と球の中心との距離を求める
	float distance = Length(closestPoint - sphere.center);
	//距離が半径よりも小さければ衝突判定
	if (distance <= sphere.radius) {
		return true;
	} else {
		return false;
	}
}

//AABBと線分の当たり判定
bool IsCollisionSegmentAndAABB(const AABB& aabb, const Segment& segment) {
	float tXmin = (aabb.min.x - segment.origin.x) / segment.diff.x;
	float tXmax = (aabb.max.x - segment.origin.x) / segment.diff.x;

	float tYmin = (aabb.min.y - segment.origin.y) / segment.diff.y;
	float tYmax = (aabb.max.y - segment.origin.y) / segment.diff.y;

	float tZmin = (aabb.min.z - segment.origin.z) / segment.diff.z;
	float tZmax = (aabb.max.z - segment.origin.z) / segment.diff.z;

	float tNearX = min(tXmin, tXmax);
	float tFarX = max(tXmin, tXmax);

	float tNearY = min(tYmin, tYmax);
	float tFarY = max(tYmin, tYmax);

	float tNearZ = min(tZmin, tZmax);
	float tFarZ = max(tZmin, tZmax);

	//AABBとの衝突点（貫通点）のtが小さい方
	float tmin = max(max(tNearX, tNearY), tNearZ);
	//AABBとの衝突点（貫通点）のtが大きい方
	float tmax = min(min(tFarX, tFarY), tFarZ);
	if (tmin <= tmax && tmax >= 0.0f && tmin <= 1.0f) {
		return true;
	} else {
		return false;
	}
}

bool IsCollisionSphereAndOBB(const Sphere& sphere, const OBB& obb)
{
	//OBBのワールド行列を作る
	Matrix4x4 obbRotateMatrix = {};
	obbRotateMatrix.m[0][0] = obb.orientations[0].x;
	obbRotateMatrix.m[1][0] = obb.orientations[1].x;
	obbRotateMatrix.m[2][0] = obb.orientations[2].x;

	
	Matrix4x4 obbWorldMatrix = obbRotateMatrix;
	obbWorldMatrix.m[3][0] = obb.center.x;
	obbWorldMatrix.m[3][1] = obb.center.y;
	obbWorldMatrix.m[3][2] = obb.center.z;

	//OBBのワールド行列の逆行列を求める
	Matrix4x4 obbWorldMatrixInverse = Inverse(obbWorldMatrix);

	//中心点を逆行列でOBBのローカル空間上の点にする
	Vector3 centerInOBBLocalSpace = Transform(sphere.center, obbWorldMatrixInverse);

	//OBBからABBを作る
	AABB aabbLocal;
	aabbLocal.min = obb.size;
	aabbLocal.min *= -1;
	aabbLocal.max = obb.size;

	Sphere sphereOBBLocal{ centerInOBBLocalSpace,sphere.radius };

	//AABBと球の衝突判定をおこなう
	if (IsCollisionSphereAndAABB(aabbLocal, sphereOBBLocal)) {
		return true;
	} else {
		return false;
	}
	
}
