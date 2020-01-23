#pragma once

#include <SimpleMath.h>
#include "GameObject.h"

class SphereCollider;
class BoxCollider;

// 形状
class Collider
{
public: // 基本

	// コンストラクタ
	Collider(GameObject* _owner);
	// デストラクタ
	virtual ~Collider() = default;

public: // アクセサ

	// 座標取得
	const DirectX::SimpleMath::Vector3 Collider::GetPosition() const
	{
		return m_owner->GetPosition() + m_offset;
	}

	// オフセット取得
	const DirectX::SimpleMath::Vector3 GetOffset() const
	{
		return m_offset;
	}

	// オフセット設定
	void  SetOffset(const DirectX::SimpleMath::Vector3& _offset)
	{
		m_offset = _offset;
	}

public: // 関数

	virtual bool IsCollided(const Collider*       _collider) const = 0;
	virtual bool IsCollided(const SphereCollider* _collider) const;
	virtual bool IsCollided(const BoxCollider*    _collider) const;

	// 衝突
	void OnCollision(const Collider* _object) const;


protected: // 変数

	// 持ち主
	GameObject*                  m_owner;

	// オフセット
	DirectX::SimpleMath::Vector3 m_offset;
};
