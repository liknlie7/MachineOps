#pragma once

#include "SimpleMath.h"

class Collision
{
public: // 構造体

	// 球
	struct Sphere
	{
		DirectX::SimpleMath::Vector3		center;
		float								radius;
	};

	// 線分
	struct Segment
	{
		DirectX::SimpleMath::Vector3 start;
		DirectX::SimpleMath::Vector3 end;
	};

	// カプセル
	struct Capsule
	{
		Segment segment;
		float radius;
	};

	// ボックス(正方形)
	struct Box
	{
		DirectX::SimpleMath::Vector3 center;		// 中心座標
		DirectX::SimpleMath::Vector3 radius;		// 幅の半分(xyz各要素)
	};

	// 三角形の構造体（線分と三角形の交差判定用）
	struct Triangle
	{
		// 三角形の平面方程式
		DirectX::SimpleMath::Plane p;
		// 辺BCの平面方程式（重心座標の頂点aに対する重みuを与える）
		DirectX::SimpleMath::Plane edgePlaneBC;
		// 辺CAの平面方程式（重心座標の頂点bに対する重みvを与える）
		DirectX::SimpleMath::Plane edgePlaneCA;

		// コンストラクタ内で衝突判定を軽くするために前処理で計算しておく
		Triangle(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
		{
			DirectX::SimpleMath::Vector3 n = (c - a).Cross(b - a);
			p = DirectX::SimpleMath::Plane(a, n);
			DirectX::SimpleMath::Plane pp = DirectX::SimpleMath::Plane(b, n);
			edgePlaneBC = DirectX::SimpleMath::Plane(b, n.Cross(b - c));
			edgePlaneCA = DirectX::SimpleMath::Plane(c, n.Cross(c - a));
			p.Normalize(); edgePlaneBC.Normalize(); edgePlaneCA.Normalize();
			float bc_scale = 1.0f / (a.Dot(edgePlaneBC.Normal()) + edgePlaneBC.D());
			float ca_scale = 1.0f / (b.Dot(edgePlaneCA.Normal()) + edgePlaneCA.D());
			edgePlaneBC.x *= bc_scale; edgePlaneBC.y *= bc_scale; edgePlaneBC.z *= bc_scale; edgePlaneBC.w *= bc_scale;
			edgePlaneCA.x *= ca_scale; edgePlaneCA.y *= ca_scale; edgePlaneCA.z *= ca_scale; edgePlaneCA.w *= ca_scale;
		}
	};
	// 浮動小数点の誤差で当たりぬけするので少し余裕をもつ
#define EPSILON 1.0e-06F


public: // 基本

	Collision() {}
	~Collision() {}

public: // 関数

	// 球と球の衝突判定
	static bool HitCheckSphereToSphere(const Sphere& _sphereA, const Sphere& _sphereB);

	// 球とカプセルの衝突判定
	static bool HitCheckSphereToCapsule(const Sphere& _sphere, const Capsule& _capsule);

	// カプセルとカプセルの衝突判定
	static bool HitCheckCapsuleToCapsule(const Capsule& _capsuleA, const Capsule& _capsuleB);

	// ボックスとボックスの衝突判定
	static bool HitCheckAABB(const Box& _boxA, const Box& _boxB);

	// 球とボックスの衝突判定
	static bool HitCheckSphereToBox(const Sphere& _sphere, const Box& _box);

	// 線分と三角形の交差判定
	static bool IntersectSegmentTriangle(const DirectX::SimpleMath::Vector3& _start, const DirectX::SimpleMath::Vector3& _end, const Triangle& _tri, DirectX::SimpleMath::Vector3* _crossPoint);

private: // サブ関数

	// 点と線分の間の距離の平方を返す関数
	static float SqDistPointSegment(const DirectX::SimpleMath::Vector3& _start, const DirectX::SimpleMath::Vector3& _end, const DirectX::SimpleMath::Vector3& _point);

	// クランプ関数
	static float Clamp(float _n, float _min, float _max);

	// ２つの線分の最短距離の平方を返す関数
	static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 _start1, DirectX::SimpleMath::Vector3 _end1
		, DirectX::SimpleMath::Vector3 _start2, DirectX::SimpleMath::Vector3 _end2
		, float &s, float &t
		, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);

	// 点とボックスの間の最短距離の平方を計算する関数
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& _point, const Box& _box);
};