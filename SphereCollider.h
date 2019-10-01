#pragma once


#include "Collider.h"


// 球
class SphereCollider : public Collider
{
public: // 基本

	// コンストラクタ
	SphereCollider(GameObject* owner, float radius = 1.0f);
	// デストラクタ
	~SphereCollider() = default;

public: // 関数

	bool IsCollided(const Collider*       collider) const override;
	bool IsCollided(const SphereCollider* collider) const override;

	// 半径取得
	float GetRadius() const;
	// 半径設定
	void  SetRadius(float radius);

private: // 変数

	// 半径
	float m_radius;
};