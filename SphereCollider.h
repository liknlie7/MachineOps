#pragma once

#include "Collider.h"

// 球
class SphereCollider : public Collider
{

public: // 基本

	// コンストラクタ
	SphereCollider(GameObject* _owner, float _radius = 1.0f);
	// デストラクタ
	~SphereCollider() = default;

public: // アクセサ

	// 半径取得
	float GetRadius() const
	{
		return m_radius;
	}

	// 半径設定
	void  SetRadius(float _radius)
	{
		m_radius = _radius;
	}

public: // 関数

	bool IsCollided(const Collider*       _collider) const override;
	bool IsCollided(const SphereCollider* _collider) const override;
	bool IsCollided(const BoxCollider*    _collider) const override;

private: // 変数

	// 半径
	float m_radius;
};