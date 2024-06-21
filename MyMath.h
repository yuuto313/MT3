#include <Novice.h>
#include <Vector3.h>
#include <Matrix4x4.h>
#include <cmath>
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <imgui.h>
#include <Vector2.h>
#include <cmath>
#include <algorithm>
#pragma once


//球
struct Sphere {
	Vector3 center;//中心点
	float radius;//半径
};

//平面
struct Plane {
	Vector3 normal;//法線
	float distance;//距離
};

//直線
struct Line {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};

//半直線
struct  Ray
{
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル

};

//線分
struct  Segment
{
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};

//三角形
struct Triangle {
	Vector3 vertices[3];//頂点
};

//直方体
//Axis Aligned Bounding Box（軸平行境界箱）
struct AABB {
	Vector3 min;//最小点
	Vector3 max;//最大点
};

//Oriented Bounding Box（有向境界箱）
struct OBB
{
	Vector3 center;//中心点
	Vector3 orientations[3];//座標軸。正規化、直交必須
	Vector3 size;//座標軸方向の長さの半分。中心から面までの距離
};

//クロス積（ベクトル積）
Vector3 Cross(const Vector3& v1, const Vector3& v2);

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2);
//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);

//内積
float Dot(const Vector3& v1, const Vector3& v2);
//長さ
float Length(const Vector3& v);
//正規化
Vector3 Normalize(const Vector3& v);
//積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

//逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

//平行移動
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
//拡縮
Matrix4x4 MakeScaleMatrix(const Vector3& scale);


//X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
//Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);
//Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

//アフィン変換
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//cotangent(cot)、tanの逆数
float cot(float other);

//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

// 4x4行列の数値表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

//垂線
Vector3 Perpendicular(const Vector3& vector);

//平面を描画
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewMatrix, uint32_t color);

//線を描画
void DrawLine(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewMatrix, uint32_t color);

//三角形を描画
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewMatrix, uint32_t color);

//グリッドを描画
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

//スフィアを描画
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

//直方体を描画
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

//有効境界箱を描画
void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

//正射影ベクトル（ベクトル射影）
Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

//球と球の当たり判定
bool IsCollisionSphere(const Sphere& s1, const Sphere& s2);

//球と平面の当たり判定
bool IsCollisionPlane(const Sphere& sphere, const Plane& plane);

//線と平面の当たり判定
bool isCollisionLine(const Segment& segment, const Plane& plane);

//三角形と線の当たり判定
bool IsCollisionTriangle(const Triangle& triangle, const Segment& segment);

//AABBとAABBの衝突判定
bool IsCollisionAABB(const AABB& aabb1, const AABB& aabb2);

//AABBと球の当たり判定
bool IsCollisionSphereAndAABB(const AABB& aabb, const Sphere& sphere);

//AABBと線分の当たり判定
bool IsCollisionSegmentAndAABB(const AABB& aabb, const Segment& segment);

//球とOBBの当たり判定
bool IsCollisionSphereAndOBB(const Sphere& sphere, const OBB& obb);
