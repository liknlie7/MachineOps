#include "pch.h"
#include "Collision.h"

// 球と球の衝突判定
// 衝突している時 true
bool Collision::HitCheckSphereToSphere(const Sphere& _sphereA, const Sphere& _sphereB)
{
	// 球の中心の差
	DirectX::SimpleMath::Vector3 sub = _sphereA.center - _sphereB.center;

	// ルート計算は処理が重いため Length で
	//float distance = sqrtf(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
	float distance = sub.Length();

	if (distance > _sphereA.radius + _sphereB.radius)
	{
		return false;
	}
	return true;
}

// 球とカプセルの衝突判定関数
bool Collision::HitCheckSphereToCapsule(const Sphere& _sphere, const Capsule& _capsule)
{
	// 球の中心とカプセルの中心の線分との距離の平方を計算
	float dist2 = SqDistPointSegment(_capsule.segment.start, _capsule.segment.end, _sphere.center);
	float radius = _sphere.radius + _capsule.radius;
	return dist2 <= radius * radius;
}

// カプセルとカプセルの衝突判定関数
bool Collision::HitCheckCapsuleToCapsule(const Capsule& _capsuleA, const Capsule& _capsuleB)
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	// カプセルの中心の線分間の距離の平方を計算
	float dist2 = ClosestPtSegmentSegment(_capsuleA.segment.start, _capsuleA.segment.end, _capsuleB.segment.start, _capsuleB.segment.end, s, t, c1, c2);
	float radius = _capsuleA.radius + _capsuleB.radius;
	return dist2 <= radius * radius;
}

// BOX同士の衝突判定関数
bool Collision::HitCheckAABB(const Box& _boxA, const Box& _boxB)
{
	if (fabsf(_boxA.center.x - _boxB.center.x) > (_boxA.radius.x + _boxB.radius.x)) return false;
	if (fabsf(_boxA.center.y - _boxB.center.y) > (_boxA.radius.y + _boxB.radius.y)) return false;
	if (fabsf(_boxA.center.z - _boxB.center.z) > (_boxA.radius.z + _boxB.radius.z)) return false;

	return true;
}

// 球とボックスの衝突判定関数
bool Collision::HitCheckSphereToBox(const Sphere& _sphere, const Box& _box)
{
	float sqDist = SqDistPointBox(_sphere.center, _box);
	return sqDist <= _sphere.radius * _sphere.radius;
}

// 点cと線分abの間の距離の平方を返す関数
// start = 線分の始点, end = 線分の終点, point = 点, return 点と線分の間の距離の平方
float Collision::SqDistPointSegment(const DirectX::SimpleMath::Vector3& _start, const DirectX::SimpleMath::Vector3& _end, const DirectX::SimpleMath::Vector3& _point)
{
	DirectX::SimpleMath::Vector3 ab = _end - _start;
	DirectX::SimpleMath::Vector3 ac = _point - _start;
	DirectX::SimpleMath::Vector3 bc = _point - _end;
	float e = ac.Dot(ab);
	if (e <= 0.0f) return ac.Dot(ac);
	float f = ab.Dot(ab);
	if (e >= f) return bc.Dot(bc);
	return ac.Dot(ac) - e * e / f;
}

// クランプ関数
float Collision::Clamp(float _n, float _min, float _max)
{
	if (_n < _min) return _min;
	if (_n > _max) return _max;
	return _n;
}

// ２つの線分の最短距離の平方を返す関数
// start1 = 線分1の始点, end1 = 線分1の終点, start2 = 線分2の始点, end2 = 線分２の終点
// s  = 線分1上の最短位置を表す係数, t = 線分2上の最短位置を表す係数
// c1 = 線分1上の最短距離の位置, c2 = 線分2上の最短位置の距離
float Collision::ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 _start1, DirectX::SimpleMath::Vector3 _end1
	, DirectX::SimpleMath::Vector3 _start2, DirectX::SimpleMath::Vector3 _end2
	, float &_s, float &_t
	, DirectX::SimpleMath::Vector3& _c1, DirectX::SimpleMath::Vector3& _c2)
{
	DirectX::SimpleMath::Vector3 d1 = _end1 - _start1;
	DirectX::SimpleMath::Vector3 d2 = _end2 - _start2;
	DirectX::SimpleMath::Vector3 r = _start1 - _start2;
	float a = d1.Dot(d1);
	float e = d2.Dot(d2);
	float f = d2.Dot(r);

	if (a <= FLT_EPSILON && e <= FLT_EPSILON)
	{
		_s = _t = 0.0f;
		_c1 = _start1;
		_c2 = _start2;
		return (_c1 - _c2).Dot(_c1 - _c2);
	}
	if (a <= FLT_EPSILON)
	{
		_s = 0.0f;
		_t = f / e;
		_t = Clamp(_t, 0.0f, 1.0f);
	}
	else
	{
		float c = d1.Dot(r);
		if (e <= FLT_EPSILON)
		{
			_t = 0.0f;
			_s = Clamp(-c / a, 0.0f, 1.0f);
		}
		else
		{
			float b = d1.Dot(d2);
			float denom = a * e - b * b;
			if (denom != 0.0f)
			{
				_s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			}
			else
			{
				_s = 0.0f;
			}
			float tnom = (b * _s + f);
			if (tnom < 0.0f)
			{
				_t = 0.0f;
				_s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else if (tnom > e)
			{
				_t = 1.0f;
				_s = Clamp((b - c) / a, 0.0f, 1.0f);
			}
			else
			{
				_t = tnom / e;
			}
		}
	}
	_c1 = _start1 + d1 * _s;
	_c2 = _start2 + d2 * _t;
	return (_c1 - _c2).Dot(_c1 - _c2);
}

// 点とボックスの間の最短距離の平方を計算する関数
float Collision::SqDistPointBox(const DirectX::SimpleMath::Vector3& _point, const Box& _box)
{
	float point[3] = { _point.x, _point.y, _point.z };
	float min[3] = { _box.center.x - _box.radius.x, _box.center.y - _box.radius.y, _box.center.z - _box.radius.z, };
	float max[3] = { _box.center.x + _box.radius.x, _box.center.y + _box.radius.y, _box.center.z + _box.radius.z, };

	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		float v = point[i];
		if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
	}
	return sqDist;
}

// 線分と三角形の交差判定
// p = 線分の始点, q = 線分の終点, tri = 三角形, crossPoint = 線分と三角形の交差点
bool Collision::IntersectSegmentTriangle(const DirectX::SimpleMath::Vector3& _start, const DirectX::SimpleMath::Vector3& _end
	, const Triangle& _tri, DirectX::SimpleMath::Vector3* _crossPoint)
{
	float distp = _start.Dot(_tri.p.Normal()) + _tri.p.D();
	if (distp < 0.0f) return false;
	float distq = _end.Dot(_tri.p.Normal()) + _tri.p.D();
	if (distq >= 0.0f) return false;
	float denom = distp - distq;
	float t = distp / denom;
	*_crossPoint = _start + t * (_end - _start);
	float u = _crossPoint->Dot(_tri.edgePlaneBC.Normal()) + _tri.edgePlaneBC.D();
	if (fabsf(u) < EPSILON) u = 0.0f;
	if (u < 0.0f || u > 1.0f) return false;
	float v = _crossPoint->Dot(_tri.edgePlaneCA.Normal()) + _tri.edgePlaneCA.D();
	if (fabsf(v) < EPSILON) v = 0.0f;
	if (v < 0.0f) return false;
	float w = 1.0f - u - v;
	if (fabsf(w) < EPSILON) w = 0.0f;
	if (w < 0.0f) return false;
	return true;
}
