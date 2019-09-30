#pragma once


#include <SimpleMath.h>


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

public: // 関数

	virtual bool IsCollided(const Collider*       collider) const = 0;
	virtual bool IsCollided(const SphereCollider* collider) const;
	virtual bool IsCollided(const BoxCollider*    collider) const;


	void OnCollision(const Collider* object) const;

	const DirectX::SimpleMath::Vector3 GetPosition() const;
	const DirectX::SimpleMath::Vector3 GetOffset() const;

	void  SetOffset(const DirectX::SimpleMath::Vector3& offset);

protected: // 変数

	// 持ち主
	GameObject*                  m_owner;
	// 補正値
	DirectX::SimpleMath::Vector3 m_offset;
};