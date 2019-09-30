#pragma once


#include <SimpleMath.h>

#include "GameObject.h"
#include "Collider.h"

class GameObject;
class SphereCollider;
class BoxCollider;


class Collider
{
public: // 基本

	// コンストラクタ
	Collider(GameObject* owner);
	// デストラクタ
	virtual ~Collider() = default;

public: // アクセサ

	// 座標取得
	const DirectX::SimpleMath::Vector3 Collider::GetPosition() const
	{
		return m_owner->GetPosition() + m_offset;
	}

	// 補正値の取得
	const DirectX::SimpleMath::Vector3 Collider::GetOffset() const
	{
		return m_offset;
	}

	// 補正値の設定
	void Collider::SetOffset(const DirectX::SimpleMath::Vector3 & offset)
	{
		m_offset = offset;
	}

public: // 関数

	virtual bool IsCollided(const Collider*       collider) const = 0;
	virtual bool IsCollided(const SphereCollider* collider) const;
	virtual bool IsCollided(const BoxCollider*    collider) const;

	void OnCollision(const Collider* object) const;

protected: // 変数

	// 持ち主
	GameObject*                  m_owner;
	// 補正値
	DirectX::SimpleMath::Vector3 m_offset;

};